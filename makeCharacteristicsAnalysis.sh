#!/bin/bash

######
#
# HOW TO USE !!!!!!
#
# just run:
#./makeCharacteristicsAnalysis.sh img/color/lena.bmp 
#
#
######

if [ -f analysis.txt ]; then
	rm analysis.txt
fi

echo  >> analysis.txt
    echo "Mean: " >> analysis.txt
    out/./image-manipulator --cmean $1 >> analysis.txt
echo  >> analysis.txt

echo  >> analysis.txt
    echo "Variance: " >> analysis.txt
    out/./image-manipulator --cvariance $1 >> analysis.txt
echo  >> analysis.txt

echo  >> analysis.txt
    echo "Standard Deviation: " >> analysis.txt
    out/./image-manipulator --cstdev $1 >> analysis.txt
echo  >> analysis.txt

echo  >> analysis.txt
    echo "Variation Coefficient I: " >> analysis.txt
    out/./image-manipulator --cvarcoi $1 >> analysis.txt
echo  >> analysis.txt

echo  >> analysis.txt
    echo "Variation Coefficient II: " >> analysis.txt
    out/./image-manipulator --cvarcoii $1 >> analysis.txt
echo  >> analysis.txt

echo  >> analysis.txt
    echo "Asymmetry Coefficient: " >> analysis.txt
    out/./image-manipulator --casyco $1 >> analysis.txt
echo  >> analysis.txt

echo  >> analysis.txt
    echo "Flattening Coefficient: " >> analysis.txt
    out/./image-manipulator --cflaco $1 >> analysis.txt
echo  >> analysis.txt

echo  >> analysis.txt
    echo "Information Source Entropy: " >> analysis.txt
    out/./image-manipulator --centropy $1 >> analysis.txt
echo  >> analysis.txt

mv analysis.txt out/analysis.txt


# args=("$@") 
# ELEMENTS=${#args[@]} 
# for (( i=0;i<$ELEMENTS;i++)); do 
#     arg+=" "${args[${i}]}
# done

