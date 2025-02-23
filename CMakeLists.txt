cmake_minimum_required(VERSION 3.10)

project(milestone1_exe)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

# Add directories for header files
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/external)


find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(TinyObjLoader REQUIRED)

target_link_libraries(milestone1_exe PRIVATE tinyobjloader)


include_directories(${GLEW_INCLUDE_DIRS})



add_executable(milestone1_exe ${PROJECT_SOURCES})
add_executable(milestone1_exe src/main.cpp src/ShaderUtils.cpp src/ObjLoader.cpp ...)
target_link_libraries(milestone1_exe ${OPENGL_LIBRARIES} GLEW::GLEW glfw ...)


target_link_libraries(milestone1_exe PRIVATE glfw GLEW::GLEW ${OPENGL_LIBRARIES})

if(APPLE)
    # Add configurations for macOS here
elseif(WIN32)
    # Add configurations for Windows here
elseif(UNIX AND NOT APPLE)
    # Add configurations for Unix/Linux here (you've already done this)
endif()
