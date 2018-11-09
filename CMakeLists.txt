cmake_minimum_required(VERSION 3.4)
project(image-manipulator)

set(CMAKE_CXX_STANDARD 11)


# To use PKG_CHECK_MODULES to find some optional packages
find_package(PkgConfig)

#    Tell CMake where to leave executables
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

#Path of CImg.h file relative to this file path
set(CIMG_H_PATH ${PROJECT_SOURCE_DIR}/lib/)
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${CIMG_H_PATH} )


# ### CIMG related stuff
# Flags to enable fast image display, using the XSHM library.
SET(CIMG_XSHM_CCFLAGS  -Dcimg_use_xshm)

# Flags to enable screen mode switching, using the XRandr library.
SET(CIMG_XRANDR_CCFLAGS  -Dcimg_use_xrandr)

# Flags to enable native support for JPEG image files, using the JPEG library.
# ( http://www.ijg.org/ )
SET(CIMG_JPEG_CCFLAGS  -Dcimg_use_jpeg)

# Flags to enable native support for TIFF image files, using the TIFF library.
# ( http://www.libtiff.org/ )
SET(CIMG_TIFF_CCFLAGS  -Dcimg_use_tiff)

# Flags to enable native support for PNG image files, using the PNG library.
# ( http://www.libpng.org/ )
SET(CIMG_PNG_CCFLAGS  -Dcimg_use_png)

#Flags to enable OPENCV support (Camera)
# ( http://www.opencv.org/ )
SET(CIMG_OPENCV_CCFLAGS-Dcimg_use_opencv)

# Flags to enable native support for EXR image files, using the OpenEXR library.
# ( http://www.openexr.com/ )
SET(CIMG_OPENEXR_CCFLAGS  -Dcimg_use_openexr)

# Flags to enable native support for various video files, using the FFMPEG library.
# ( http://www.ffmpeg.org/ )
SET(CIMG_FFMPEG_CCFLAGS  -Dcimg_use_ffmpeg)

# Flags to enable native support of most classical image file formats, using the Magick++ library.
# ( http://www.imagemagick.org/Magick++/ )
SET(CIMG_MAGICK_CCFLAGS -Dcimg_use_magick)

# Flags to enable faster Discrete Fourier Transform computation, using the FFTW3 library
# ( http://www.fftw.org/ )
SET(CIMG_FFTW3_CCFLAGS  -Dcimg_use_fftw3)


# ### Search Additional Libraries ##########
FIND_PACKAGE(JPEG)
FIND_PACKAGE(TIFF)
FIND_PACKAGE(PNG)
FIND_PACKAGE(ZLIB)
FIND_PACKAGE(LAPACK)
FIND_PACKAGE(BLAS)

PKG_CHECK_MODULES(FFTW3 fftw3)
PKG_CHECK_MODULES(OPENEXR OpenEXR)

if(NOT WIN32)
    FIND_PACKAGE(X11)
    FIND_PACKAGE(Threads REQUIRED)
endif()

### Configure Paths according to detected packages
if(TIFF_FOUND)
    get_filename_component(TIFF_LIB_DIRS ${TIFF_LIBRARIES} PATH)
    SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_TIFF_CCFLAGS}")
    link_directories(${TIFF_LIB_DIRS})
    include_directories(${TIFF_INCLUDE_DIR})
    SET(SYSTEM_LIBS ${SYSTEM_LIBS} ${TIFF_LIBRARIES})
endif()

if(JPEG_FOUND)
    get_filename_component(JPEG_LIB_DIRS ${JPEG_LIBRARIES} PATH)
    SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_JPEG_CCFLAGS}")
    link_directories(${JPEG_LIB_DIRS})
    include_directories(${JPEG_INCLUDE_DIR})
    SET(SYSTEM_LIBS ${SYSTEM_LIBS} ${JPEG_LIBRARIES})
endif()

if (ZLIB_FOUND)
    SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_ZLIB_CCFLAGS}")
    link_directories(${ZLIB_LIB_DIRS})
    include_directories(${ZLIB_INCLUDE_DIR})
    SET(SYSTEM_LIBS ${SYSTEM_LIBS} ${ZLIB_LIBRARIES})

    # PNG requires ZLIB
    if(PNG_FOUND)
        SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_PNG_CCFLAGS}")
        link_directories(${PNG_LIB_DIRS})
        include_directories(${PNG_INCLUDE_DIR} )
        SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${PNG_LIBRARIES} )
    endif()
endif()

if(FFTW3_FOUND)
    SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_FFTW3_CCFLAGS}")
    link_directories( ${FFTW3_LIBRARY_DIRS} )
    include_directories( ${FFTW3_INCLUDE_DIRS} )
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${FFTW3_LIBRARIES} )
endif()

if(OPENEXR_FOUND)
    SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_OPENEXR_CCFLAGS}")
    link_directories( ${OPENEXR_LIBRARY_DIRS} )
    include_directories( ${OPENEXR_INCLUDE_DIRS} )
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${OPENEXR_LIBRARIES} )
endif()

if( LIBAVCODEC_FOUND  AND LIBAVFORMAT_FOUND AND LIBSWSCALE_FOUND AND LIBAVUTIL_FOUND )
    SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_FFMPEG_CCFLAGS}")
    link_directories( ${LIBAVFORMAT_LIBRARY_DIRS} )
    link_directories( ${LIBAVCODEC_LIBRARY_DIRS} )
    link_directories( ${LIBSWSCALE_LIBRARY_DIRS} )
    link_directories( ${LIBAVUTIL_LIBRARY_DIRS} )
    include_directories( ${LIBAVFORMAT_INCLUDE_DIRS} ${LIBAVFORMAT_INCLUDE_DIRS}/libavformat)
    include_directories( ${LIBAVCODEC_INCLUDE_DIRS} ${LIBAVCODEC_INCLUDE_DIRS}/libavcodec )
    include_directories( ${LIBSWSCALE_INCLUDE_DIRS} ${LIBSWSCALE_INCLUDE_DIRS}/libswscale)
    include_directories( ${LIBAVUTIL_INCLUDE_DIRS} ${LIBAVUTIL_INCLUDE_DIRS}/libavutil )
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${LIBAVFORMAT_LIBRARIES} )
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${LIBAVCODEC_LIBRARIES} )
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${LIBSWSCALE_LIBRARIES} )
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${LIBAVUTIL_LIBRARIES} )
endif()

if(NOT APPLE)
    if(NOT WIN32)
        if(X11_FOUND)
            SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_XSHM_CCFLAGS} ${CIMG_XRANDR_CCFLAGS}")
            SET(SYSTEM_LIBS ${SYSTEM_LIBS} Xext Xrandr)
        endif()
    endif(NOT WIN32)
endif(NOT APPLE)

if(X11_FOUND)
    link_directories(${X11_LIB_DIRS})
    include_directories(${X11_INCLUDE_DIR})
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${X11_LIBRARIES} )
endif()


if (NOT WIN32)
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${CMAKE_THREAD_LIBS_INIT} )
endif()

if( WIN32)
    SET( SYSTEM_LIBS  ${SYSTEM_LIBS}  gdi32 )
endif()

if(LAPACK_FOUND)
    SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_LAPACK_CCFLAGS}")
    link_directories( ${LAPACK_LIBRARY_DIRS} )
    include_directories( ${LAPACK_INCLUDE_DIRS} )
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${LAPACK_LIBRARIES} )
endif()

if(BLAS_FOUND)
    SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_BLAS_CCFLAGS}")
    link_directories( ${BLAS_LIBRARY_DIRS} )
    include_directories( ${BLAS_INCLUDE_DIRS} )
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${BLAS_LIBRARIES} )
endif()

# Add CIMG Flags to Compilation Flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CIMG_CFLAGS}")

include_directories(src)
include_directories(src/manipulations)
include_directories(lib)

add_executable(image-manipulator
        src/main.cpp
        src/manipulations/t1-basic.h
        src/manipulations/t1-basic.cpp
        src/manipulations/t1-geometric.h
        src/manipulations/t1-geometric.cpp
        src/manipulations/t1-noise-removal.h
        src/manipulations/t1-noise-removal.cpp
        src/manipulations/t1-analysis.h
        src/manipulations/t1-analysis.cpp
        src/manipulations/t0-other.cpp
        src/manipulations/t0-other.h
        src/manipulations/t2-histogram.cpp
        src/manipulations/t2-histogram.h
        src/manipulations/t2-characteristics.cpp
        src/manipulations/t2-characteristics.h
        src/manipulations/t2-quality-improvement.cpp
        src/manipulations/t2-quality-improvement.h
        )

target_link_libraries(image-manipulator ${SYSTEM_LIBS})



