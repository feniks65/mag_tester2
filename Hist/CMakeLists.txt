cmake_minimum_required(VERSION 2.8)

project(tester CXX)

set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 11)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

include_directories(/opt/local/include)
link_directories (/opt/local/lib /usr/local/lib)

ADD_EXECUTABLE(tester main.cpp)
TARGET_LINK_LIBRARIES(tester
		opencv_core
		opencv_imgproc
		opencv_video
		opencv_shape
		opencv_stitching
		opencv_objdetect
		opencv_superres
		opencv_videostab
		opencv_highgui
		opencv_videoio
		opencv_imgcodecs
		opencv_photo
		opencv_ml
		opencv_flann
		${EXTERNAL_LIBS})
