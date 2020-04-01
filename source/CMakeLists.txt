# CMAKE variables
set( PATH_INCLUDES /home/error/Desktop/learn_2_squat/includes ) 

# CMAKE requirements
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(camera VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find packages 
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PATH_INCLUDES})

# Add executables
add_executable(camera camera.cpp)

# Link libraries
target_link_libraries(camera ${OpenCV_LIBS})
