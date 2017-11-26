cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(unit_test_estrategia_clasificador)

find_package(PCL 1.8 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS} "../googletest/cmake/build")
add_definitions(${PCL_DEFINITIONS})

#set(CMAKE_CXX_FLAGS "-std=c++11 -fpermissive -lgtest -lpthread")
set(CMAKE_CXX_FLAGS "-std=c++98 -fpermissive -lgtest")

#cmake_policy(SET CMP0015 NEW)

#Se guardan todos los archivos fuente y de includes
#file(GLOB_RECURSE SOURCES "source/*.cpp")

add_executable (unit_test_estrategia_clasificador "unit_test_estrategia_clasificador.cpp")
target_link_libraries (unit_test_estrategia_clasificador ${PCL_LIBRARIES} )


