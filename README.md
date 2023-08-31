# PYTHIA-ANGANTYR-UEGenerator
Using PYTHIA with ANGANTYR to generate underlying events in heavy-ion collisions
Built in pythia8309

#To configure:  
Find ```myAngantyrBkg.cc``` in ```src/```
```
g++ myAngantyrBkg.cc -o myAngantyrBkg -I../include -g -O -std=c++11 -pedantic -W -Wall -Wshadow -fPIC -pthread  -L../lib -Wl,-rpath,../lib -lpythia8 -ldl -I/cvmfs/sft.cern.ch/lcg/releases/HepMC/2.06.11-d5a39/x86_64-centos7-gcc10-opt/include -L/cvmfs/sft.cern.ch/lcg/releases/HepMC/2.06.11-d5a39/x
86_64-centos7-gcc10-opt/lib -Wl,-rpath,/cvmfs/sft.cern.ch/lcg/releases/HepMC/2.06.11-d5a39/x86_64-centos7-gcc10-opt/lib -lHepMC
```
#To run: 
```
./myAngantyrBkg myAngantyrBkg.cmnd ~/test.hepmc 1
```
