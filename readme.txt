build on ubuntu 18.10

1. sudo apt install gcc g++ gfortran make cmake bison flex libfl-dev libfftw3-dev libsuitesparse-dev libblas-dev liblapack-dev libtool libopenmpi-dev openmpi-bin
2. $ cd work && git clone https://github.com/trilinos/Trilinos.git
   $ mkdir build
   $ cd build

create `reconfigure.sh` (serial version) under `build/` and run it:

```
#!/bin/sh
SRCDIR=$HOME/work/Trilinos
ARCHDIR=$HOME/work/XyceLibs/Serial
FLAGS="-O3 -fPIC"
cmake \
-G "Unix Makefiles" \
-DCMAKE_C_COMPILER=gcc \
-DCMAKE_CXX_COMPILER=g++ \
-DCMAKE_Fortran_COMPILER=gfortran \
-DCMAKE_CXX_FLAGS="$FLAGS" \
-DCMAKE_C_FLAGS="$FLAGS" \
-DCMAKE_Fortran_FLAGS="$FLAGS" \
-DCMAKE_INSTALL_PREFIX=$ARCHDIR \
-DCMAKE_MAKE_PROGRAM="make" \
-DTrilinos_ENABLE_NOX=ON \
  -DNOX_ENABLE_LOCA=ON \
-DTrilinos_ENABLE_EpetraExt=ON \
  -DEpetraExt_BUILD_BTF=ON \
  -DEpetraExt_BUILD_EXPERIMENTAL=ON \
  -DEpetraExt_BUILD_GRAPH_REORDERINGS=ON \
-DTrilinos_ENABLE_TrilinosCouplings=ON \
-DTrilinos_ENABLE_Ifpack=ON \
-DTrilinos_ENABLE_Isorropia=ON \
-DTrilinos_ENABLE_AztecOO=ON \
-DTrilinos_ENABLE_Belos=ON \
-DTrilinos_ENABLE_Teuchos=ON \
  -DTeuchos_ENABLE_COMPLEX=ON \
-DTrilinos_ENABLE_Amesos=ON \
  -DAmesos_ENABLE_KLU=ON \
-DTrilinos_ENABLE_Sacado=ON \
-DTrilinos_ENABLE_Kokkos=OFF \
-DTrilinos_ENABLE_ALL_OPTIONAL_PACKAGES=OFF \
-DTrilinos_ENABLE_CXX11=ON \
-DTPL_ENABLE_AMD=ON \
-DAMD_LIBRARY_DIRS="/usr/lib" \
-DTPL_AMD_INCLUDE_DIRS="/usr/include/suitesparse" \
-DTPL_ENABLE_BLAS=ON \
-DTPL_ENABLE_LAPACK=ON \
$SRCDIR
```
    $ make -j
    $ make install


3. $ mkdir ~/work/xyce-6.11.1/build
   $ cd ~/work/xyce-6.11.1/build
   $ ../source/configure --prefix=/usr/local ARCHDIR=$HOME/work/XyceLibs/Serial
   $ make -j
   $ sudo make install
