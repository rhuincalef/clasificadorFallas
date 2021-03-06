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
#include <json/json.h>
#include <fstream>
#include <unordered_map>
#include "../../../source/segmentation/include/segmentation.hpp"
#include "../../../source/nube/include/nube.hpp"
#include "../../../source/parser/include/parseador.hpp"

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
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
char **test_margv;
int test_margc;

class PlanarAndEuclideanTest : public ::testing::Test {
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
TEST(PlanarAndEuclideanTest, TamanioNube)
{
  srand (time (NULL));

  pcl::PointCloud<pcl::PointXYZ>::Ptr my_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  // Generate pointcloud data
  my_cloud->width = 1000;
  my_cloud->height = 1;
  my_cloud->points.resize (my_cloud->width * my_cloud->height);

  for (size_t i = 0; i < my_cloud->points.size (); ++i)
  {
    my_cloud->points[i].x = 1024.0f * rand () / (RAND_MAX + 1.0f);
    my_cloud->points[i].y = 1024.0f * rand () / (RAND_MAX + 1.0f);
    my_cloud->points[i].z = 1024.0f * rand () / (RAND_MAX + 1.0f);
  }
  PlanarAndEuclidean<pcl::PointXYZ> pl_ec;
  pl_ec.setNube(*my_cloud);
  int orig_cloud_size = 0;
  orig_cloud_size = my_cloud->points.size();
  EXPECT_EQ(orig_cloud_size, pl_ec.getSizeNube());
}
*/

TEST(PlanarAndEuclideanTest, DistanceThreshold)
{
  PlanarAndEuclidean<pcl::PointXYZ> pl_ec;
  float distance_tresh = 9;
  pl_ec.setDistanceThreshold(distance_tresh);
  EXPECT_EQ(9, pl_ec.getDistanceThreshold());
}

TEST(PlanarAndEuclideanTest, MinClusterSize)
{
  PlanarAndEuclidean<pcl::PointXYZ> pl_ec;
  int min_cluster_size = 1000;
  pl_ec.setMinClusterSize(min_cluster_size);
  EXPECT_EQ(1000, pl_ec.getMinClusterSize());
}

TEST(PlanarAndEuclideanTest, MaxClusterSize)
{
  PlanarAndEuclidean<pcl::PointXYZ> pl_ec;
  int max_cluster_size = 250000;
  pl_ec.setMaxClusterSize(max_cluster_size);
  EXPECT_EQ(250000, pl_ec.getMaxClusterSize());
}

TEST(PlanarAndEuclideanTest, MaxIterations)
{
  PlanarAndEuclidean<pcl::PointXYZ> pl_ec;
  int max_iterations = 1000;
  pl_ec.setMaxIterations(max_iterations);
  EXPECT_EQ(1000, pl_ec.getMaxIterations());
}

TEST(PlanarAndEuclideanTest, ClusterTolerance)
{
  PlanarAndEuclidean<pcl::PointXYZ> pl_ec;
  float tolerance = .023f;
  pl_ec.setClusterTolerance(tolerance);
  EXPECT_EQ(.023f, pl_ec.getClusterTolerance());
}

TEST(PlanarAndEuclideanTest, PlanarSegmentation)
{
  PlanarAndEuclidean<pcl::PointXYZ> pl_ec;
  pcl::PointCloud<pcl::PointXYZ>::Ptr plane (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr no_plane (new pcl::PointCloud<pcl::PointXYZ>);
  pl_ec.setDistanceThreshold (.02);
  pl_ec.setMaxIterations (1000);
  pl_ec.planarSegmentation (*cloud, *no_plane, *plane);
  EXPECT_EQ(26115, cloud->points.size()) << "Cloud size not match " << plane->points.size();
  EXPECT_EQ(23316, plane->points.size()) << "CloudPlane size not match " << plane->points.size();
  EXPECT_EQ(2799, no_plane->points.size()) << "CloudNoPlane size not match " << no_plane->points.size();
}

TEST(PlanarAndEuclideanTest, Computar)
{
  Nube<pcl::PointXYZ> n (cloud);
  std::vector<pcl::PointCloud<pcl::PointXYZ>> v;
  PlanarAndEuclidean<pcl::PointXYZ> pl_ec;
  pl_ec.setDistanceThreshold (.02);
  pl_ec.setMaxIterations (1000);
  pl_ec.setNube (n);
  v = pl_ec.computar ();
  EXPECT_EQ(2774, v.at(0).points.size());
  pcl::io::savePCDFileASCII ("pl_ec_cloud.pcd", v.at(0));
}

TEST(PlanarAndEuclideanTest, ComputarAbstract)
{
  Nube<pcl::PointXYZ> n (cloud);
  std::vector<pcl::PointCloud<pcl::PointXYZ>> v;
  EstrategiaSegmentationAbstract<pcl::PointXYZ> *p;
  //PlanarAndEuclidean<pcl::PointXYZ> *pl_ec = new PlanarAndEuclidean<pcl::PointXYZ>;
  p = new PlanarAndEuclidean<pcl::PointXYZ>;
  PlanarAndEuclidean<pcl::PointXYZ> *pl_ec;
  pl_ec = dynamic_cast<PlanarAndEuclidean<pcl::PointXYZ> *> (p);
  /*
  */
  pl_ec->setDistanceThreshold (.02);
  pl_ec->setMaxIterations (1000);
  pl_ec->setNube (n);
  v = pl_ec->computar ();
  EXPECT_EQ(2774, v.at(0).points.size());
  pcl::io::savePCDFileASCII ("pl_ec_cloud.pcd", v.at(0));
}

TEST(PlanarAndEuclideanTest, Parametrizador)
{
  ParseadorJSON parser;
  std::vector<int> v = parser.parse_file_extension_argument(test_margc, test_margv, ".json");
  bool ok = parser.openRapid(test_margv[v[0]]);
  EXPECT_TRUE(ok);
  EstrategiaSegmentationAbstract<pcl::PointXYZ> *p;
  PlanarAndEuclidean<pcl::PointXYZ> *pl_ec;
  p = new PlanarAndEuclidean<pcl::PointXYZ>;
  pl_ec = dynamic_cast<PlanarAndEuclidean<pcl::PointXYZ> *> (p);
  Parametrizador parametrizador = PlanarAndEuclidean<pcl::PointXYZ>::getParametrizador();
  std::unordered_map<std::string, std::string> values;
  bool result = parser.parser_rapid(&parametrizador, values);
  EXPECT_TRUE(result);
  for (auto i = values.begin(); i != values.end(); ++i)
  {
    std::cout << "Name: " << i->first << std::endl;
    std::cout << "Value: " << i->second << std::endl;
  }
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
    std::cerr << "No test file given. Please download `voxel_bachecitos_tw_4.pcd` and pass its path to the test." << std::endl;
    return (-1);
  }
  // Read a PCD file from disk.
  if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *cloud) != 0)
  {
    std::cerr << "Failed to read test file. Please download `voxel_bachecitos_tw_4.pcd` and pass its path to the test." << std::endl;
    return -1;
  }
  test_margv = argv;
  test_margc = argc;
  ::testing::InitGoogleTest (&argc, argv);
  return (RUN_ALL_TESTS ());
}