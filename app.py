import os

os.system('''
module unload gcc/8.2.0
module load gcc/9.3
export CC=/cm/shared/apps/gcc/9.3/bin/gcc
export CCX=/cm/shared/apps/gcc/9.3/bin/g++
module load qt
module load cmake
. Software/geant4/geant4-v11.0.3/share/Geant4-11.0.3/geant4make/geant4make.sh
cd sim1
cmake ../sim1
make
./sim1
''')


