//-------------------------------------------------------------------------
//   Copyright 2002-2019 National Technology & Engineering Solutions of
//   Sandia, LLC (NTESS).  Under the terms of Contract DE-NA0003525 with
//   NTESS, the U.S. Government retains certain rights in this software.
//
//   This file is part of the Xyce(TM) Parallel Electrical Simulator.
//
//   Xyce(TM) is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   Xyce(TM) is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with Xyce(TM).
//   If not, see <http://www.gnu.org/licenses/>.
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//
// Purpose        : Manager for the parallel load-balance and distribution tools.
//
// Special Notes  :
//
// Creator        : Scott A. Hutchinson, SNL, Parallel Computational Sciences
//
// Creation Date  : 03/08/00
//
//
//
//
//-------------------------------------------------------------------------

#include <Xyce_config.h>

#include <N_ERH_ErrorMgr.h>
#include <N_LAS_LAFactory.h>
#include <N_PDS_Comm.h>
#include <N_PDS_GlobalAccessor.h>
#include <N_PDS_Manager.h>
#include <N_PDS_ParMap.h>

#include <Epetra_CrsGraph.h>

#undef HAVE_LIBPARMETIS
#include <EpetraExt_View_CrsGraph.h>

namespace Xyce {
namespace Parallel {

//-----------------------------------------------------------------------------
// Function      : Manager::Manager
// Purpose       : Default constructor.
// Special Notes :
// Scope         : Public
// Creator       : Scott A. Hutchinson, SNL, Parallel Computational Sciences
// Creation Date : 03/09/00
//-----------------------------------------------------------------------------
Manager::Manager(
  int           iargs,
  char **       cargs,
  Machine       comm)
  : pdsComm_(0),
    parMaps_(),
    globalAccessors_(),
    matrixGraphs_(),
    matrixGraphTransforms_()
{
  pdsComm_ = Xyce::Parallel::createPDSComm(iargs, cargs, comm);

  // std::fill(&parMaps_[0], &parMaps_[MAP_COUNT], (N_PDS_ParMap *) 0);
  // std::fill(&globalAccessors_[0], &globalAccessors_[MAP_COUNT], 0);
  // std::fill(&matrixGraphs_[0], &matrixGraphs_[MAP_COUNT], 0);
  // std::fill(&matrixGraphTransforms_[0], &matrixGraphTransforms_[MAP_COUNT], 0);
}

//-----------------------------------------------------------------------------
// Function      : Manager::~Manager
// Purpose       : Destructor - closes up the load balance list and shuts down
//                 MPI.
// Special Notes :
// Scope         : Public
// Creator       : Scott A. Hutchinson, SNL, Parallel Computational Sciences
// Creation Date : 03/09/00
//-----------------------------------------------------------------------------
Manager::~Manager()
{
  for (int i = 0; i < MAP_COUNT; ++i)
  {
    deleteParallelMap(i);
    deleteMatrixGraph(i);
  }

  delete pdsComm_;
}

//-----------------------------------------------------------------------------
// Function      : Manager::createParallelMap
// Purpose       :
// Special Notes :
// Scope         : Public
// Creator       : Robert J Hoekstra, SNL, Parallel Computational Sciences
// Creation Date : 01/31/01
//-----------------------------------------------------------------------------
N_PDS_ParMap *
Manager::createParallelMap(
  int &                         num_global,
  int                           num_local,
  const std::vector<int> &      gid_map,
  const int                     index_base)
{
  return new N_PDS_ParMap(num_global, num_local, gid_map, index_base, *pdsComm_);
}

//-----------------------------------------------------------------------------
// Method        : Manager::addParallelMap
// Purpose       : add N_PDS_ParMap obj to container, key{int}
// Scope         : public
// Special Notes :
// Creator       : Robert J Hoekstra, SNL, Parallel Compuational Sciences
// Creation Date : 01/31/01
//-----------------------------------------------------------------------------
bool
Manager::addParallelMap(
  int                   id,
  N_PDS_ParMap *        map )
{
  if (parMaps_[id])
  {
    Report::DevelFatal0().in("Manager::addParallelMap") << "Parallel Map " << id << " already exists";
    return false;
  }

  parMaps_[id] = map;

  return true;
}

//-----------------------------------------------------------------------------
// Method        : Manager::linkParallelMap
// Purpose       : link new key to existing key
// Scope         : public
// Special Notes :
// Creator       : Robert J Hoekstra, SNL, Parallel Compuational Sciences
// Creation Date : 01/31/01
//-----------------------------------------------------------------------------
bool
Manager::linkParallelMap(
  int                   new_id,
  int                   link_id )
{
  if (linkedMapsGraphs_.find( new_id ) != linkedMapsGraphs_.end())
  {
    Report::DevelFatal0().in("Manager::linkParallelMap") << "Parallel Map link for " << new_id << " already exists";
    return false;
  }
  if (!parMaps_[link_id])
  {
    Report::DevelFatal0().in("Manager::linkParallelMap") << "Parallel Map " << link_id << " does not exist, link cannot be completed.";
  }

  linkedMapsGraphs_[new_id] = link_id;
  parMaps_[new_id] = parMaps_[link_id];
   
  return true;
}

//-----------------------------------------------------------------------------
// Function      : Manager::deleteParallelMap
// Purpose       : delete parallel maps that are not linked to any others
// Special Notes :
// Scope         : Public
// Creator       : Robert J Hoekstra, SNL, Parallel Computational Sciences
// Creation Date : 01/31/01
//-----------------------------------------------------------------------------
bool
Manager::deleteParallelMap(
  int           id)
{
  deleteGlobalAccessor(id);

  // Make sure map with this id was not linked before deleting.
  if (linkedMapsGraphs_.find( id ) == linkedMapsGraphs_.end())
  {
    delete parMaps_[id];
    parMaps_[id] = 0;
  }
  return true;
}

//-----------------------------------------------------------------------------
// Function      : Manager::addGlobalAccessor
// Purpose       :
// Special Notes :
// Scope         : Public
// Creator       : Robert J Hoekstra, SNL, Parallel Computational Sciences
// Creation Date : 01/31/01
//-----------------------------------------------------------------------------
N_PDS_GlobalAccessor *
Manager::addGlobalAccessor(
  int           id )
{
  if (globalAccessors_[id])
  {
    Report::DevelFatal0().in("Manager::addGlobalAccessor") << "Global Accessor " << id << " already exists";
    return 0;
  }

  if (!parMaps_[id])
  {
    Report::DevelFatal0().in("Manager::addParallelMap") << "ParallelMap " << id << " has not been created";
    return 0;
  }

  return globalAccessors_[id] = new N_PDS_GlobalAccessor(parMaps_[id]->pdsComm());
}

//-----------------------------------------------------------------------------
// Function      : Manager::deleteGlobalAccessor
// Purpose       :
// Special Notes :
// Scope         : Public
// Creator       : Robert J Hoekstra, SNL, Parallel Computational Sciences
// Creation Date : 01/31/01
//-----------------------------------------------------------------------------
bool
Manager::deleteGlobalAccessor(
  int           id)
{
  delete globalAccessors_[id];
  globalAccessors_[id] = 0;

  return true;
}

//-----------------------------------------------------------------------------
// Function      : Manager::createGlobalAccessor
// Purpose       :
// Special Notes :
// Scope         : Public
// Creator       : Robert J Hoekstra, SNL, Parallel Computational Sciences
// Creation Date : 02/1/01
//-----------------------------------------------------------------------------
N_PDS_GlobalAccessor * Manager::createGlobalAccessor()
{
  return new N_PDS_GlobalAccessor( *pdsComm_ );
}

//-----------------------------------------------------------------------------
// Method        : Manager::addMatrixGraph
// Purpose       :
// Scope         : public
// Special Notes :
// Creator       : Robert J Hoekstra, SNL, Parallel Compuational Sciences
// Creation Date : 08/23/02
//-----------------------------------------------------------------------------
bool
Manager::addMatrixGraph(
  int                           id,
  Epetra_CrsGraph *             graph,
  EpetraExt::CrsGraph_View *    trans )
{
  if (matrixGraphs_[id])
  {
    Report::DevelFatal0().in("Manager::addMatrixGraph") << "Matrix Graph " << id << " already exists";
    return false;
  }

  matrixGraphs_[ id ] = graph;

  if (trans)
    matrixGraphTransforms_[ id ] = trans;

  return true;
}

//-----------------------------------------------------------------------------
// Method        : Manager::linkMatrixGraph
// Purpose       : link new key to existing key
// Scope         : public
// Special Notes :
// Creator       : Robert J Hoekstra, SNL, Parallel Compuational Sciences
// Creation Date : 01/31/01
//-----------------------------------------------------------------------------
bool
Manager::linkMatrixGraph(
  int                   new_id,
  int                   link_id )
{
  if (linkedMapsGraphs_.find( new_id ) != linkedMapsGraphs_.end())
  {
    Report::DevelFatal0().in("Manager::linkMatrixGraph") << "Matrix Graph link for " << new_id << " already exists";
    return false;
  }
  if (!matrixGraphs_[link_id])
  {
    Report::DevelFatal0().in("Manager::linkMatrixGraph") << "Matrix Graph " << link_id << " does not exist, link cannot be completed.";
  }

  linkedMapsGraphs_[new_id] = link_id;
  matrixGraphs_[new_id] = matrixGraphs_[link_id];

  if (matrixGraphTransforms_[link_id])
    matrixGraphTransforms_[new_id] = matrixGraphTransforms_[link_id];  
 
  return true;
}

//-----------------------------------------------------------------------------
// Function      : Manager::deleteMatrixGraph
// Purpose       : delete matrix graphs that are not linked to any others
// Special Notes :
// Scope         : Public
// Creator       : Robert J Hoekstra, SNL, Parallel Computational Sciences
// Creation Date : 03/31/03
//-----------------------------------------------------------------------------
bool Manager::deleteMatrixGraph( int id )
{
  if (linkedMapsGraphs_.find( id ) == linkedMapsGraphs_.end())
  {
    if (matrixGraphTransforms_[id]) {
      delete matrixGraphTransforms_[id];
      matrixGraphTransforms_[id] = 0;
      matrixGraphs_[id] = 0;
    }
    else {
      delete matrixGraphs_[id];
      matrixGraphs_[id] = 0;
    }
  }

  return true;
}

} // namespace Parallel
} // namespace Xyce
