// A sample program demonstrating using Google C++ testing framework.
//
// Author: wan@google.com (Zhanyong Wan)


// This sample shows how to write a simple unit test for a function,
// using Google C++ testing framework.
//
// Writing a unit test using Google C++ testing framework is easy as 1-2-3:


// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.
#include <gtest/gtest.h>
#include "../../../source/descriptor/include/pointfeaturederivadas.hpp"
#include "../../../source/descriptor/include/descriptor.hpp"
#include "../../../source/segmentation/include/segmentation.hpp"
#include "../../../source/nube/include/nube.hpp"

// Step 2. Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>
pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);

class PointFeatureTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};

// Tests PlanarAndEuclidean()
/*
*/
TEST(PointFeatureTest, PlanarAndEuclideanYGRSD)
{
  Nube<pcl::PointXYZRGB>* n (new Nube<pcl::PointXYZRGB>(*cloud));
  std::vector<pcl::PointCloud<pcl::PointXYZRGB>> v;
  PlanarAndEuclidean<pcl::PointXYZRGB> pl_ec;
  pl_ec.setDistanceThreshold (.005);
  pl_ec.setMaxIterations (1000);
  pl_ec.setNube (*n);
  v = pl_ec.computar ();
  EXPECT_EQ(2774, v.at(0).points.size());
  //EstrategiaDescriptorsAbstract<pcl::PointXYZRGB,pcl::GRSDSignature21,PointFeatureGRSD>* estratDescriptor;
  EstrategiaDescriptorsAbstract<pcl::PointXYZRGB>* estratDescriptor;
  estratDescriptor = new GRSD<pcl::PointXYZRGB, pcl::GRSDSignature21, PointFeatureGRSD>();
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZRGB>);
  *cloud_cluster = v.at(0);
  pcl::PCDWriter writer;
  writer.write<pcl::PointXYZRGB>("setDistanceThreshold.pcd", v.at(0), false);
  Nube<pcl::PointXYZRGB>* nueva_nube (new Nube<pcl::PointXYZRGB>(cloud_cluster));
  PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* pointFeature = estratDescriptor->template generarDescriptor<pcl::PointXYZRGB, pcl::GRSDSignature21, PointFeatureGRSD> (nueva_nube);
  pcl::PointCloud<pcl::GRSDSignature21> descriptores = pointFeature->getDescriptorPCL();
  int pos_6 = descriptores.points[0].histogram[6];
  EXPECT_EQ(2932, pos_6);
  EXPECT_EQ(2033, descriptores.points[0].histogram[10]);
  //writer.write<pcl::GRSDSignature21>("grsd.pcd", descriptores, false);
}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?
/*
*/
int
main (int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "No test file given. Please download `bachecitos_tw_4.pcd` and pass its path to the test." << std::endl;
    return (-1);
  }
  // Read a PCD file from disk.
  if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(argv[1], *cloud) != 0)
  {
    std::cerr << "Failed to read test file. Please download `bachecitos_tw_4.pcd` and pass its path to the test." << std::endl;
    return -1;
  }
  ::testing::InitGoogleTest (&argc, argv);
  return (RUN_ALL_TESTS ());
}