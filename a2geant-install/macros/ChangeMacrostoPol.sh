#!/bin/bash


echo "Which macro do you wish to change? doppi0 or DGdoppi0 or doneta are currently supported"
read word
echo $word
if [ "${word}" == "doppi0" ]; then
	echo "Which Physics List do you wish to change the macros to? options are Pol or A2? 	You can change to QGSP_BIC by typing A2 " 
	read line
	echo $line
	if [ "${line}" == "Pol" ]; then
		sed -i -e 's:/A2/physics/Physics QGSP_BIC:/Pol/physics/Physics QGSP_BIC_POL:g' doppi0.mac
		sed -i -e 's:/A2/physics/SetRegion:/Pol/physics/SetRegion:g' doppi0.mac
		sed -i -e 's:/A2/physics/RegionCut:/Pol/physics/RegionCut:g' doppi0.mac
		echo "here Pol, you need to comment out all the lines containing setRegion not anymore"
	elif [ "${line}" == "A2" ]; then
		sed -i -e 's:/Pol/physics/Physics QGSP_BIC_POL:/A2/physics/Physics QGSP_BIC:g' doppi0.mac
		sed -i -e 's:/Pol/physics/SetRegion:/A2/physics/SetRegion:g' doppi0.mac
		sed -i -e 's:/Pol/physics/RegionCut:/A2/physics/RegionCut:g' doppi0.mac
		echo "here A2, you need to uncomment all the lines containing setRegion not anymore "	
	fi	

	 
elif [ "${word}" == "doneta" ]; then
	echo "Which Physics List do you wish to change the macros to? options are Pol or A2? 	You can change to QGSP_BIC by typing A2 " 
	read line
	if [ "${line}" == "Pol" ]; then
		sed -i -e 's:/A2/physics/Physics QGSP_BIC:/Pol/physics/Physics QGSP_BIC_POL:g' doneta.mac
	elif [ "${line}" == "A2" ]; then
		sed -i -e 's:/Pol/physics/Physics QGSP_BIC_POL:/A2/physics/Physics QGSP_BIC:g' doneta.mac		
	fi

	
elif [ "${word}" == "DGdoppi0" ]; then
	echo "Which Physics List do you wish to change the macros to? options are Pol or A2? 	You can change to QGSP_BIC by typing A2 " 
	read line
	if [ "${line}" == "Pol" ]; then
		sed -i -e 's:/A2/physics/Physics QGSP_BIC:/Pol/physics/Physics QGSP_BIC_POL:g' DGdoppi0.mac
	elif [ "${line}" == "A2" ]; then
		sed -i -e 's:/Pol/physics/Physics QGSP_BIC_POL:/A2/physics/Physics QGSP_BIC:g' DGdoppi0.mac
	fi
fi

exit 0 
