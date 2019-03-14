#!/bin/bash

######
#
# HOW TO USE !!!!!!
#
# just run:
#./denoiseAndAnalyse.sh --median 2 img/noise-color/lena-impulse3.bmp img/color/lena.bmp 
#
#
######
if [ -f analysis.txt ]; then
	rm analysis.txt
fi

echo  >> analysis.txt
    echo Applying $1 with strengh $2 on $3 >> analysis.txt
    out/./image-manipulator $1 $2 $3 edited.bmp >> analysis.txt
echo  >> analysis.txt
    echo "Mean Square Error for the original image and the image with noise." >> analysis.txt
    out/./image-manipulator --mse $4 $3 >> analysis.txt
    echo "Mean Square Error for the original image and denoised image." >> analysis.txt
    out/./image-manipulator --mse $4 edited.bmp >> analysis.txt
echo  >> analysis.txt
    echo "Peak Mean Square Error for the original image and the image with noise." >> analysis.txt
    out/./image-manipulator --pmse $4 $3 >> analysis.txt
    echo "Peak Mean Square Error for the original image and denoised image." >> analysis.txt
    out/./image-manipulator --pmse $4 edited.bmp >> analysis.txt
echo  >> analysis.txt
    echo "Signal To Noise Ratio for the original image and the image with noise." >> analysis.txt
    out/./image-manipulator --snr $4 $3 >> analysis.txt
    echo "Signal To Noise Ratio for the original image and denoised image." >> analysis.txt
    out/./image-manipulator --snr $4 edited.bmp >> analysis.txt
echo  >> analysis.txt
    echo "Peak Signal To Noise Ratio for the original image and the image with noise." >> analysis.txt
    out/./image-manipulator --psnr $4 $3 >> analysis.txt
    echo "Peak Signal To Noise Ratio for the original image and denoised image."  >> analysis.txt
    out/./image-manipulator --psnr $4 edited.bmp >> analysis.txt
echo  >> analysis.txt
    echo "Maximum Difference for the original image and the image with noise." >> analysis.txt
    out/./image-manipulator --md $4 $3 >> analysis.txt
    echo "Maximum Difference for the original image and denoised image." >> analysis.txt
    out/./image-manipulator --md $4 edited.bmp >> analysis.txt


mv edited.bmp out/edited.bmp
mv original.bmp out/original.bmp
mv analysis.txt out/analysis.txt


# args=("$@") 
# ELEMENTS=${#args[@]} 
# for (( i=0;i<$ELEMENTS;i++)); do 
#     arg+=" "${args[${i}]}
# done

