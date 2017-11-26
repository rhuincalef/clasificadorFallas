cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(mainPipeLine)

find_package(PCL 1.8 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS} "tests/googletest/cmake/build")
add_definitions(${PCL_DEFINITIONS})

set(CMAKE_CXX_FLAGS "-std=c++11 -fpermissive")

#Se configura dir build/
#set(DESTDIR "build/")

#cmake_policy(SET CMP0015 NEW)

#Se guardan todos los archivos fuente y de includes
file(GLOB_RECURSE SOURCES "source/*.cpp")
add_executable (mainPipeLine "mainPipeLine.cpp" "${SOURCES}")
target_link_libraries (mainPipeLine ${PCL_LIBRARIES} )
























#file(GLOB_RECURSE HEADERS "include/*.hpp")
#set (Foo_INCLUDE_DIRS "")
#foreach (_headerFile ${HEADERS})
#    get_filename_component(_dir ${_headerFile} PATH)
#    list (APPEND Foo_INCLUDE_DIRS ${_dir})
#endforeach()
#list(REMOVE_DUPLICATES Foo_INCLUDE_DIRS)
#add_executable (mainPipeLine "mainPipeLine.cpp" "${SOURCES}")
#target_link_libraries (mainPipeLine ${PCL_LIBRARIES} ${Foo_INCLUDE_DIRS})

