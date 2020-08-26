# CMAKE requirements
cmake_minimum_required(VERSION 3.10)

# CMAKE variables
set(PATH_INCLUDES                	      /home/error/Desktop/learn_2_squat/includes) 
set(PATH_SOURCE                  	      /home/error/Desktop/learn_2_squat/source)
set(PATH_TENSORFLOWLITE_BIN 	   	      /usr/local/lib/libtensorflow-lite.a)
set(PATH_TENSORFLOWLITE_INCLUDES 	      /home/error/tensorflow/)
set(PATH_TENSORFLOWLITE_FLATBUFFERS_INCLUDE /home/error/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers/include/)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-as-needed -ldl -lpthread")
 
# set the project name and version
project(learn_2_squat VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find packages 
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PATH_TENSORFLOWLITE_INCLUDES})
include_directories(${PATH_TENSORFLOWLITE_FLATBUFFERS_INCLUDE})
include_directories(${PATH_INCLUDES})

# Libraries
add_library(camera_LIBARARY          ${PATH_SOURCE}/camera.cpp          ${PATH_INCLUDES}/camera.hpp)
add_library(pose_estimation_LIBARARY ${PATH_SOURCE}/pose_estimation.cpp ${PATH_INCLUDES}/pose_estimation.hpp)
add_library(utility_LIBARARY         ${PATH_SOURCE}/utility.cpp         ${PATH_INCLUDES}/utility.hpp)

# Add executables
add_executable(main_exe ${PATH_SOURCE}/main.cpp)

# Link libraries
target_link_libraries(main_exe PRIVATE camera_LIBARARY pose_estimation_LIBARARY utility_LIBARARY ${OpenCV_LIBS} ${PATH_TENSORFLOWLITE_BIN} ${CMAKE_THREAD_LIBS_INIT}) 
