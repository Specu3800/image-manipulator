#!/bin/bash

# args=("$@") 
# ELEMENTS=${#args[@]} 
# for (( i=0;i<$ELEMENTS;i++)); do 
#     arg+=" "${args[${i}]}
# done


# HOW TO USE !!!!!!

# just run:
#denoiseAndAnalyse.sh --midian 2 img/noise-color/lena-impulse3.bmp img/color/lena.bmp 

echo
    echo Applying $1 with strengh $2 on $3
    out/./image-manipulator $1 $2 $3 out/edited.bmp
echo 
    echo "Mean Square Error for the original image and the image with noise."
    out/./image-manipulator --mse $4 $3
    echo "Mean Square Error for the original image and denoised image."
    out/./image-manipulator --mse $4 out/edited.bmp
echo 
    echo "Peak Mean Square Error for the original image and the image with noise."
    out/./image-manipulator --pmse $4 $3
    echo "Peak Mean Square Error for the original image and denoised image."
    out/./image-manipulator --pmse $4 out/edited.bmp
echo 
    echo "Signal To Noise Ratio for the original image and the image with noise."
    out/./image-manipulator --snr $4 $3
    echo "Signal To Noise Ratio for the original image and denoised image."
    out/./image-manipulator --snr $4 out/edited.bmp
echo 
    echo "Peak Signal To Noise Ratio for the original image and the image with noise."
    out/./image-manipulator --psnr $4 $3
    echo "Peak Signal To Noise Ratio for the original image and denoised image."
    out/./image-manipulator --psnr $4 out/edited.bmp
echo 
    echo "Maximum Difference for the original image and the image with noise."
    out/./image-manipulator --md $4 $3
    echo "Maximum Difference for the original image and denoised image."
    out/./image-manipulator --md $4 out/edited.bmp


