#!/bin/bash


echo "Which Physics List do you wish to change to? Pol or A2?" 
read line
if [ "${line}" == "Pol" ]; then
	sed -i -e 's/A2PhysicsList/PolPhysicsList/g' ./src/A2.cc
elif [ "${line}" == "A2" ]; then
	sed -i -e 's/PolPhysicsList/A2PhysicsList/g' ./src/A2.cc
fi
exit 0 
