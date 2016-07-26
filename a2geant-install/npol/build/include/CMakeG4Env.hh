#ifndef CMakeG4Env_hh
#define CMakeG4Env_hh 1
#include <stdlib.h>
#define SET_G4_ENV_BY_CMAKE() \
setenv("G4LEVELGAMMADATA","/scratch/chris/geant4.10.01.p02-build/data/PhotonEvaporation3.1",0); \
setenv("G4NEUTRONXSDATA","/scratch/chris/geant4.10.01.p02-build/data/G4NEUTRONXS1.4",0); \
setenv("G4LEDATA","/scratch/chris/geant4.10.01.p02-build/data/G4EMLOW6.41",0); \
setenv("G4NEUTRONHPDATA","/scratch/chris/geant4.10.01.p02-build/data/G4NDL4.5",0); \
setenv("G4RADIOACTIVEDATA","/scratch/chris/geant4.10.01.p02-build/data/RadioactiveDecay4.2",0); \
setenv("G4ABLADATA","/scratch/chris/geant4.10.01.p02-build/data/G4ABLA3.0",0); \
setenv("G4PIIDATA","/scratch/chris/geant4.10.01.p02-build/data/G4PII1.3",0); \
setenv("G4SAIDXSDATA","/scratch/chris/geant4.10.01.p02-build/data/G4SAIDDATA1.1",0); \
setenv("G4REALSURFACEDATA","/scratch/chris/geant4.10.01.p02-build/data/RealSurface1.0",0); \

#endif