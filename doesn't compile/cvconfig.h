#ifndef OPENCV_CVCONFIG_H_INCLUDED
#define OPENCV_CVCONFIG_H_INCLUDED

/* OpenCV compiled as static or dynamic libs */
//#define BUILD_SHARED_LIBS

/* OpenCV intrinsics optimized code */
//#define CV_ENABLE_INTRINSICS

/* OpenCV additional optimized code */
//#define CV_DISABLE_OPTIMIZATION

/* Compile for 'real' NVIDIA GPU architectures */
//#define CUDA_ARCH_BIN "${OPENCV_CUDA_ARCH_BIN}"

/* Create PTX or BIN for 1.0 compute capability */
//#define CUDA_ARCH_BIN_OR_PTX_10

/* NVIDIA GPU features are used */
//#define CUDA_ARCH_FEATURES "${OPENCV_CUDA_ARCH_FEATURES}"

/* Compile for 'virtual' NVIDIA PTX architectures */
//#define CUDA_ARCH_PTX "${OPENCV_CUDA_ARCH_PTX}"

/* AVFoundation video libraries */
//#define HAVE_AVFOUNDATION

/* V4L capturing support */
//#define HAVE_CAMV4L

/* V4L2 capturing support */
//#define HAVE_CAMV4L2

/* Carbon windowing environment */
//#define HAVE_CARBON

/* AMD's Basic Linear Algebra Subprograms Library*/
//#define HAVE_CLAMDBLAS

/* AMD's OpenCL Fast Fourier Transform Library*/
//#define HAVE_CLAMDFFT

/* Clp support */
//#define HAVE_CLP

/* Cocoa API */
//#define HAVE_COCOA

/* C= */
//#define HAVE_CSTRIPES

/* NVidia Cuda Basic Linear Algebra Subprograms (BLAS) API*/
//#define HAVE_CUBLAS

/* NVidia Cuda Runtime API*/
//#define HAVE_CUDA

/* NVidia Cuda Fast Fourier Transform (FFT) API*/
//#define HAVE_CUFFT

/* IEEE1394 capturing support */
//#define HAVE_DC1394

/* IEEE1394 capturing support - libdc1394 v2.x */
//#define HAVE_DC1394_2

/* DirectX */
//#define HAVE_DIRECTX
//#define HAVE_DIRECTX_NV12
//#define HAVE_D3D11
//#define HAVE_D3D10
//#define HAVE_D3D9

/* DirectShow Video Capture library */
//#define HAVE_DSHOW

/* Eigen Matrix & Linear Algebra Library */
//#define HAVE_EIGEN

/* FFMpeg video library */
#define HAVE_FFMPEG

/* Geospatial Data Abstraction Library */
//#define HAVE_GDAL

/* GStreamer multimedia framework */
//#define HAVE_GSTREAMER

/* GTK+ 2.0 Thread support */
//#define HAVE_GTHREAD

/* GTK+ 2.x toolkit */
//#define HAVE_GTK

/* Halide support */
//#define HAVE_HALIDE

/* Define to 1 if you have the <inttypes.h> header file. */
//#define HAVE_INTTYPES_H 1

/* Intel Perceptual Computing SDK library */
//#define HAVE_INTELPERC

/* Intel Integrated Performance Primitives */
//#define HAVE_IPP
//#define HAVE_IPP_ICV
//#define HAVE_IPP_IW

/* Intel IPP Async */
//#define HAVE_IPP_A

/* JPEG-2000 codec */
//#define HAVE_JASPER

/* IJG JPEG codec */
#define HAVE_JPEG

/* libpng/png.h needs to be included */
#define HAVE_LIBPNG_PNG_H

/* GDCM DICOM codec */
//#define HAVE_GDCM

/* V4L/V4L2 capturing support via libv4l */
//#define HAVE_LIBV4L

/* Microsoft Media Foundation Capture library */
//#define HAVE_MSMF

/* NVidia Video Decoding API*/
//#define HAVE_NVCUVID

/* NVidia Video Encoding API*/
//#define HAVE_NVCUVENC

/* OpenCL Support */
//#define HAVE_OPENCL
//#define HAVE_OPENCL_STATIC
//#define HAVE_OPENCL_SVM

/* OpenEXR codec */
#define HAVE_OPENEXR

/* OpenGL support*/
//#define HAVE_OPENGL

/* OpenNI library */
//#define HAVE_OPENNI

/* OpenNI library */
//#define HAVE_OPENNI2

/* PNG codec */
#define HAVE_PNG

/* Posix threads (pthreads) */
//#define HAVE_PTHREAD

/* parallel_for with pthreads */
//#define HAVE_PTHREADS_PF

/* Qt support */
//#define HAVE_QT

/* Qt OpenGL support */
//#define HAVE_QT_OPENGL

/* QuickTime video libraries */
//#define HAVE_QUICKTIME

/* QTKit video libraries */
//#define HAVE_QTKIT

/* Intel Threading Building Blocks */
//#define HAVE_TBB

/* TIFF codec */
#define HAVE_TIFF

/* Unicap video capture library */
//#define HAVE_UNICAP

/* Video for Windows support */
//#define HAVE_VFW

/* V4L2 capturing support in videoio.h */
//#define HAVE_VIDEOIO

/* Win32 UI */
//#define HAVE_WIN32UI

/* XIMEA camera support */
//#define HAVE_XIMEA

/* Xine video library */
//#define HAVE_XINE

/* Define if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
//#define WORDS_BIGENDIAN

/* gPhoto2 library */
//#define HAVE_GPHOTO2

/* VA library (libva) */
////#define HAVE_VA

/* Intel VA-API/OpenCL */
//#define HAVE_VA_INTEL

/* Intel Media SDK */
//#define HAVE_MFX

/* Lapack */
//#define HAVE_LAPACK

/* Library was compiled with functions instrumentation */
//#define ENABLE_INSTRUMENTATION

/* OpenVX */
//#define HAVE_OPENVX

#if defined(HAVE_XINE)         || \
    defined(HAVE_GSTREAMER)    || \
    defined(HAVE_QUICKTIME)    || \
    defined(HAVE_QTKIT)        || \
    defined(HAVE_AVFOUNDATION) || \
    /*defined(HAVE_OPENNI)     || too specialized */ \
    defined(HAVE_FFMPEG)       || \
    defined(HAVE_MSMF)
#define HAVE_VIDEO_INPUT
#endif

#if /*defined(HAVE_XINE)       || */\
    defined(HAVE_GSTREAMER)    || \
    defined(HAVE_QUICKTIME)    || \
    defined(HAVE_QTKIT)        || \
    defined(HAVE_AVFOUNDATION) || \
    defined(HAVE_FFMPEG)       || \
    defined(HAVE_MSMF)
#define HAVE_VIDEO_OUTPUT
#endif

/* OpenCV trace utilities */
#define OPENCV_TRACE


#endif // OPENCV_CVCONFIG_H_INCLUDED
