# CMAKE variables
set( PATH_INCLUDES /home/error/Desktop/learn_2_squat/includes ) 

# CMAKE requirements
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(learn_2_squat VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find packages 
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PATH_INCLUDES})

# Libraries
add_library(camera_LIBARARY          camera.cpp ${PATH_INCLUDES}/camera.hpp)
add_library(pose_estimation_LIBARARY pose_estimation.cpp ${PATH_INCLUDES}/pose_estimation.hpp)

# Add executables
add_executable(main_exe main.cpp)

# Link libraries
target_link_libraries(main_exe PRIVATE camera_LIBARARY pose_estimation_LIBARARY ${OpenCV_LIBS} )
