cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(mainPipeLine)

enable_testing()

find_package (Threads)
find_package(PCL 1.8 REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++11 -fpermissive")

include_directories(
	${GTEST_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
	)

message(STATUS GTEST_ROOT=${gtest_SOURCE_DIR}/include)

link_directories(
	${PCL_LIBRARY_DIRS}
	${GTEST_BOTH_LIBRARIES}
	)

add_definitions(${PCL_DEFINITIONS})

#Se guardan todos los archivos fuente y de includes
file(GLOB_RECURSE SOURCES "source/*.cpp")
add_executable (mainPipeLine "mainPipeLine.cpp" "${SOURCES}")
add_executable (unittest_segmentation "test/unittest_segmentation.cpp" "source/segmentation/src/segmentation.cpp")
# Standard linking to gtest stuff.
target_link_libraries (mainPipeLine ${PCL_LIBRARIES} )
target_link_libraries(unittest_segmentation ${GTEST_BOTH_LIBRARIES} ${PCL_LIBRARIES})
