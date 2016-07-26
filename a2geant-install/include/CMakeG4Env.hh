#ifndef CMakeG4Env_hh
#define CMakeG4Env_hh 1
#include <stdlib.h>
#define SET_G4_ENV_BY_CMAKE() \
setenv("G4LEVELGAMMADATA","/home/chris/geant4.10.01.p02-install/share/Geant4-10.1.2/data/PhotonEvaporation3.1",0); \
setenv("G4NEUTRONXSDATA","/home/chris/geant4.10.01.p02-install/share/Geant4-10.1.2/data/G4NEUTRONXS1.4",0); \
setenv("G4LEDATA","/home/chris/geant4.10.01.p02-install/share/Geant4-10.1.2/data/G4EMLOW6.41",0); \
setenv("G4NEUTRONHPDATA","/home/chris/geant4.10.01.p02-install/share/Geant4-10.1.2/data/G4NDL4.5",0); \
setenv("G4RADIOACTIVEDATA","/home/chris/geant4.10.01.p02-install/share/Geant4-10.1.2/data/RadioactiveDecay4.2",0); \
setenv("G4ABLADATA","/home/chris/geant4.10.01.p02-install/share/Geant4-10.1.2/data/G4ABLA3.0",0); \
setenv("G4PIIDATA","/home/chris/geant4.10.01.p02-install/share/Geant4-10.1.2/data/G4PII1.3",0); \
setenv("G4SAIDXSDATA","/home/chris/geant4.10.01.p02-install/share/Geant4-10.1.2/data/G4SAIDDATA1.1",0); \
setenv("G4REALSURFACEDATA","/home/chris/geant4.10.01.p02-install/share/Geant4-10.1.2/data/RealSurface1.0",0); \

#endif