# #!/bin/bash

# rm analysis.txt

# echo >> analysis.txt
# echo FOR COLORED IMAGES: >> analysis.txt
# echo >> analysis.txt

# for colorPath in "img/noise-color"/*
# do
#     echo Doing stuff...
#     echo Applying $1 with strengh $2 on $(basename $colorPath) >> analysis.txt
#     out/./image-manipulator $1 $2 "$colorPath" "img/denoised-color/"$(basename $colorPath) >> analysis.txt
#     echo >> analysis.txt
#     echo Performing Mean Square Error Analysis  >> analysis.txt
#     out/./image-manipulator --mse "img/color/lena.bmp" "$colorPath" "img/denoised-color/"$(basename $colorPath) >> analysis.txt
#     echo  >> analysis.txt
#     echo Performing Peak Mean Square Error Analysis  >> analysis.txt
#     out/./image-manipulator --pmse "img/color/lena.bmp" "$colorPath" "img/denoised-color/"$(basename $colorPath) >> analysis.txt
#     echo  >> analysis.txt
#     echo Performing Signal To Noise Ratio Analysis  >> analysis.txt
#     out/./image-manipulator --snr "img/color/lena.bmp" "$colorPath" "img/denoised-color/"$(basename $colorPath) >> analysis.txt
#     echo  >> analysis.txt
#     echo Performing Peak Signal To Noise Ratio Analysis  >> analysis.txt
#     out/./image-manipulator --psnr "img/color/lena.bmp" "$colorPath" "img/denoised-color/"$(basename $colorPath) >> analysis.txt
#     echo  >> analysis.txt
#     echo Performing Maximum Difference Analysis  >> analysis.txt
#     out/./image-manipulator --md "img/color/lena.bmp" "$colorPath" "img/denoised-color/"$(basename $colorPath) >> analysis.txt
#     echo >> analysis.txt
#     echo >> analysis.txt
#     echo >> analysis.txt
# done

# echo >> analysis.txt
# echo >> analysis.txt
# echo >> analysis.txt
# echo >> analysis.txt
# echo >> analysis.txt
# echo >> analysis.txt
# echo FOR GREY IMAGES: >> analysis.txt
# echo >> analysis.txt
# for grey in "img/noise-grey"/*
# do
#     echo Doing stuff...
#     echo Applying Adaptive Filter with strengh $1 on $(basename $grey) >> analysis.txt
#     out/./image-manipulator --adaptive $2 "$grey" "img/denoised-grey/"$(basename $grey) >> analysis.txt
#     echo >> analysis.txt
#     echo Performing Mean Square Error Analysis  >> analysis.txt
#     out/./image-manipulator --mse "img/grey/lena.bmp" "$grey" "img/denoised-grey/"$(basename $grey) >> analysis.txt
#     echo  >> analysis.txt
#     echo Performing Peak Mean Square Error Analysis  >> analysis.txt
#     out/./image-manipulator --pmse "img/grey/lena.bmp" "$grey" "img/denoised-grey/"$(basename $grey) >> analysis.txt
#     echo  >> analysis.txt
#     echo Performing Signal To Noise Ratio Analysis  >> analysis.txt
#     out/./image-manipulator --snr "img/grey/lena.bmp" "$grey" "img/denoised-grey/"$(basename $grey) >> analysis.txt
#     echo  >> analysis.txt
#     echo Performing Peak Signal To Noise Ratio Analysis  >> analysis.txt
#     out/./image-manipulator --psnr "img/grey/lena.bmp" "$grey" "img/denoised-grey/"$(basename $grey) >> analysis.txt
#     echo  >> analysis.txt
#     echo Performing Maximum Difference Analysis  >> analysis.txt
#     out/./image-manipulator --md "img/grey/lena.bmp" "$grey" "img/denoised-grey/"$(basename $grey) >> analysis.txt
#     echo  >> analysis.txt
#     echo  >> analysis.txt
#     echo  >> analysis.txt
#     echo  >> analysis.txt
# done
#     echo Done!


