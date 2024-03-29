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

//-----------------------------------------------------------------------------
// Purpose       : Functions for remeasure classes.
// Special Notes :
// Creator       : Pete Sholander, SNL, Electrical and Microsystem Modeling
// Creation Date : 2/15/2018
//
//-----------------------------------------------------------------------------

#include <Xyce_config.h>

// ---------- Standard Includes ----------

// ----------   Xyce Includes   ----------
#include <N_ANP_OutputMgrAdapter.h>
#include <N_ERH_ErrorMgr.h>
#include <N_IO_Remeasure.h>

namespace Xyce {
namespace IO {
namespace Measure{

//-----------------------------------------------------------------------------
// Function      : RemeasureBase::RemeasureBase
// Purpose       : Constructor
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
RemeasureBase::RemeasureBase(
  N_PDS_Comm &pds_comm, 
  Manager &measure_manager, 
  OutputMgr &output_manager,
  Analysis::AnalysisManager &analysis_manager,
  Analysis::AnalysisCreatorRegistry &analysis_registry) 
  : pds_comm(pds_comm),
    measure_manager(measure_manager),
    output_manager(output_manager),
    analysis_manager(analysis_manager),
    analysis_registry(analysis_registry),
    analysis_mode(Xyce::Analysis::ANP_MODE_INVALID),
    index(-1) 
{
}

//-----------------------------------------------------------------------------
// Function      : RemeasureBase::~RemeasureBase
// Purpose       : Destructor
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
RemeasureBase::~RemeasureBase()
{
}

//-----------------------------------------------------------------------------
// Function      : RemeasureAC::RemeasureAC
// Purpose       : Constructor
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
RemeasureAC::RemeasureAC(
  N_PDS_Comm &pds_comm, 
  Manager &measure_manager, 
  OutputMgr &output_manager,
  Analysis::AnalysisManager &analysis_manager,
  Analysis::AnalysisCreatorRegistry &analysis_registry) 
  : RemeasureBase(pds_comm, measure_manager, output_manager, analysis_manager, analysis_registry),
    frequency(0)  
{
  // this enum is used to set the file suffix (.ma) and also during checking of the
  // measure mode vs. the analysis mode.
  setAnalysisMode(Xyce::Analysis::ANP_MODE_AC);
}


//-----------------------------------------------------------------------------
// Function      : RemeasureAC::RemeasureAC
// Purpose       : Destructor
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
RemeasureAC::~RemeasureAC()
{
}


//-----------------------------------------------------------------------------
// Function      : RemeasureAC::setIndepVarCol
// Purpose       : Set the index variable in the base object.  This is the
//               : column index of the FREQ column in the remeasured data file.
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
void RemeasureAC::setIndepVarCol(int rank, int i, std::string colName)
{
  if ( (i<2) && (colName=="FREQ") )
  {
    (rank == 0) ? index = i : index = -1;
  }

  return;
}

//-----------------------------------------------------------------------------
// Function      : RemeasureDC::RemeasureDC
// Purpose       : Constructor
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
RemeasureDC::RemeasureDC(
  N_PDS_Comm &pds_comm, 
  Manager &measure_manager, 
  OutputMgr &output_manager,
  Analysis::AnalysisManager &analysis_manager,
  Analysis::AnalysisCreatorRegistry &analysis_registry) 
  : RemeasureBase(pds_comm, measure_manager, output_manager, analysis_manager, analysis_registry),
    SweepVecPtr(0),
    dcParamsVec(0),
    DCIndex(0),
    dcStepCount(0)  
{
  // this enum is used to set the file suffix (.ms) and also during checking of the
  // measure mode vs. the analysis mode.
  setAnalysisMode(Xyce::Analysis::ANP_MODE_DC_SWEEP);

  // If we are doing remeasure for .DC, then we need to initialize the primary analysis
  // object, so that the DC Sweep Vector can be made.  The first element in the 
  // DC Sweep Vector is used by the FROM-TO qualifiers for DC measures.  Note:
  // allocateAnalysisObject(*analysisRegistry_) will likely fail (segfault) for .TRAN
  // or .AC, since we don't have all of the TIA parameters at this point.  So, this
  // allocation is only done in the constructor for the RemeasureDC object.
  analysis_manager.allocateAnalysisObject(analysis_registry);
  Analysis::DCSweep *SweepVecPtr = dynamic_cast<Analysis::DCSweep*>(&(analysis_manager.getAnalysisObject()));
  if (SweepVecPtr == 0)
  {
    Report::DevelFatal0() << "Unknown Error making DC Sweep Vector for Remeasure" << std::endl;
  }
  else
  {
    SweepVecPtr->convertDataToSweepParams();
    analysis_manager.getOutputManagerAdapter().setDCSweepVector(SweepVecPtr->getDCSweepVec());
  }

  // Make a version of the DC Params Vector that is sufficient for doing remeasure
  // for .DC.  It may not have all of the fields filled out properly though.  Also, we
  // only update the values for the first element in that vector, which is the first variable
  // on the .DC line.  That first variable is used by the FROM-TO qualifiers for DC measures.
  dcParamsVec = analysis_manager.getOutputManagerAdapter().getDCSweepVector();
  if (dcParamsVec.size() == 0)
  {
    // DC sweep vector should have at least one element in it
    Report::DevelFatal0() << "Error making DC Sweep Vector for Remeasure";
  }
  setSweepLoopVals(dcParamsVec.begin(), dcParamsVec.end());
  dcParamsVec[0].updateCurrentVal(dcStepCount);
}


//-----------------------------------------------------------------------------
// Function      : RemeasureDC::~RemeasureDC
// Purpose       : Destructor
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
RemeasureDC::~RemeasureDC()
{
  //clean-up pointers
  delete SweepVecPtr;
  SweepVecPtr = 0;
}


//-----------------------------------------------------------------------------
// Function      : RemeasureDC::setIndepVarCol
// Purpose       : set the index variable in the base object.  This is the
//               : column index of the INDEX column in the remeasured data file.
// Special Notes : It is a fatal error if the remeasured data file does not
//               : have an INDEX column when re-measuring DC data.
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
void RemeasureDC::setIndepVarCol(int rank, int i, std::string colName)
{
  if (i==0) 
  {
    if (colName=="Index")
    {
      (rank == 0) ? index = 0 : index = -1;
    }
    else
    {
      // For DC mode, the comparison file must have INDEX as its first column.  It
      // will be used later to "sense" when a step, caused by a .STEP line, has occurred
      // in the data.
      Report::UserFatal0() << "First column of comparison file must be Index for DC-mode remeasure";
    }
  }

  return;
}


//-----------------------------------------------------------------------------
// Function      : RemeasureDC::resetSweepVars
// Purpose       : reset sweep variables specified on the .DC line
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
void RemeasureDC::resetSweepVars()
{
  dcStepCount=0;
  dcParamsVec[0].updateCurrentVal(dcStepCount);

  return;
}


//-----------------------------------------------------------------------------
// Function      : RemeasureDC::updateSweepVars
// Purpose       : update sweep variables specified on the .DC line
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
void RemeasureDC::updateSweepVars()
{
  // used to sense a "step" caused by multiple sweep variables on the .DC line
  ++dcStepCount;

  // calculate the value of first sweep variable (on the .DC line) that will
  // be used for the next iteration of this loop.  That variable is used as 
  // by the FROM-TO qualifiers for .DC measures.
  if (dcStepCount >= dcParamsVec[0].maxStep)
  {
    // Step (in .DC line) will occur on next line in the output file
    // for the 1st variable.  So, reset its value to its "start value" 
    dcStepCount=0;
    dcParamsVec[0].updateCurrentVal(dcStepCount);
  }
  else
  {
    // update value of 1st sweep variable (on .DC line) for use in 
    // next loop iteration
    dcParamsVec[0].updateCurrentVal(dcStepCount);
  }
}


//-----------------------------------------------------------------------------
// Function      : RemeasureTRAN::RemeasureTRAN
// Purpose       : Constructor
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
RemeasureTRAN::RemeasureTRAN(
  N_PDS_Comm &pds_comm, 
  Manager &measure_manager, 
  OutputMgr &output_manager,
  Analysis::AnalysisManager &analysis_manager,
  Analysis::AnalysisCreatorRegistry &analysis_registry)
  : RemeasureBase(pds_comm, measure_manager, output_manager, analysis_manager, analysis_registry) 
{
  // this enum is used to set the file suffix (.mt) and also during checking of the
  // measure mode vs. the analysis mode.
  setAnalysisMode(Xyce::Analysis::ANP_MODE_TRANSIENT);
}


//-----------------------------------------------------------------------------
// Function      : RemeasureTRAN::~RemeasureTRAN
// Purpose       : Destructor
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
RemeasureTRAN::~RemeasureTRAN()
{
  
}


//-----------------------------------------------------------------------------
// Function      : RemeasureTRAN::setIndepVarCol
// Purpose       : set the index variable in the base object.  This is the
//               : column index of the TIME column in the remeasured data file.
// Special Notes : 
// Scope         : public
// Creator       : Pete Sholander, Electrical and Microsystem Modeling
// Creation Date : 2/15/18
//-----------------------------------------------------------------------------
void RemeasureTRAN::setIndepVarCol(int rank, int i, std::string colName)
{
  if ( (i<2) && (colName=="TIME") )
  {
    (rank == 0) ? index = i : index = -1;
  }

  return;
}

} // namespace Measure
} // namespace IO
} // namespace Xyce
