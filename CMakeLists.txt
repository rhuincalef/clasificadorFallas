cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(mainPipeLine)

enable_testing()

find_package (Threads)
find_package(PCL 1.8 REQUIRED)
find_package(GTest REQUIRED)

#set(CMAKE_CXX_FLAGS "-std=c++11 -fpermissive ../libs/libsvm.so")
#set(CMAKE_CXX_FLAGS "-std=c++11 -fpermissive -lgtest")

set(CMAKE_CXX_FLAGS "-std=c++11 -fpermissive")


#########################################################

add_subdirectory(tests/googletest-release-1.8.0/googletest)
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR}/include ${COMMON_INCLUDES})


#########################################################

include_directories( 
	${GTEST_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
	)

message(STATUS GTEST_ROOT=${gtest_SOURCE_DIR}/include)

link_directories(
	${GTEST_BOTH_LIBRARIES}
	${PCL_LIBRARY_DIRS}
	)

#Se agrega la libsvm.so.2 que contiene los elementos de svm-predict y svm-train
#add_library(libsvm SHARED IMPORTED)
#set_property(TARGET libsvm PROPERTY IMPORTED_LOCATION "libs/")

add_definitions(${PCL_DEFINITIONS})

#Se guardan todos los archivos fuente y de includes
file(GLOB_RECURSE SOURCES "source/*.cpp")
add_executable (mainPipeLine "mainPipeLine.cpp" "${SOURCES}")

add_executable (unittest_segmentation "tests/unittest/segmentation/unittest_segmentation.cpp" "source/segmentation/src/segmentation.cpp")

# Standard linking to gtest stuff.

#target_link_libraries(unittest_segmentation ${GTEST_BOTH_LIBRARIES} ${PCL_LIBRARIES} )
target_link_libraries(unittest_segmentation ${GTEST_BOTH_LIBRARIES} ${PCL_LIBRARIES} gtest)

target_link_libraries (mainPipeLine ${PCL_LIBRARIES} )