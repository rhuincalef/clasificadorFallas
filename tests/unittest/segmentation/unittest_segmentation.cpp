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
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

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
*/
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
/*
TEST(PlanarAndEuclideanTest, ComputarDeprecated)
{
  std::vector<pcl::PointCloud<pcl::PointXYZ>> v;
  PlanarAndEuclidean<pcl::PointXYZ> pl_ec;
  pl_ec.setDistanceThreshold (.02);
  pl_ec.setMaxIterations (1000);
  v = pl_ec.computar (*cloud);
  EXPECT_EQ(2774, v.at(0).points.size());
  //pcl::io::savePCDFileASCII ("pl_ec_cloud.pcd", v.at(0));
}
*/
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
  PlanarAndEuclidean<pcl::PointXYZ> *pl_ec;
  p = new PlanarAndEuclidean<pcl::PointXYZ>;
  pl_ec = dynamic_cast<PlanarAndEuclidean<pcl::PointXYZ> *> (p);
  pl_ec->setDistanceThreshold (.02);
  pl_ec->setMaxIterations (1000);
  pl_ec->setNube (n);
  v = pl_ec->computar ();
  EXPECT_EQ(2774, v.at(0).points.size());
  pcl::io::savePCDFileASCII ("pl_ec_cloud.pcd", v.at(0));
}

TEST(PlanarAndEuclideanTest, Parametrizador)
{
  Json::CharReaderBuilder reader;
  Json::Value root;
  std::string errs;
  std::ifstream file("/home/manjaro-guille/mis_proyectos/clasificadorFallas/tests/unittest/segmentation/config_pipeline.json", std::ifstream::binary);
  bool ok = Json::parseFromStream(reader, file, &root, &errs);
  if(!ok) {
    std::cout << errs << std::endl;
  }
  EstrategiaSegmentationAbstract<pcl::PointXYZ> *p;
  PlanarAndEuclidean<pcl::PointXYZ>::configurarParametrizador();
  PlanarAndEuclidean<pcl::PointXYZ> *pl_ec;
  p = new PlanarAndEuclidean<pcl::PointXYZ>;
  pl_ec = dynamic_cast<PlanarAndEuclidean<pcl::PointXYZ> *> (p);
  Parametrizador param = PlanarAndEuclidean<pcl::PointXYZ>::parametrizador_;
  Json::Value s = root.get("estrategia_segmentador", "defValue");
  s = s.get(param.getNombre(), "defValue");
  std::cout << "Parametrizador nombre: " << s << std::endl;
  for (int i = 0; i < param.getParametros().size(); ++i)
  {
    Json::Value p = s.get(param.getParametros()[i].getNombre(), "defValue");
    std::cout << "Param " << param.getParametros()[i].getNombre() << " value: " << p.asString() << std::endl;
  }
/*
  Json::Value s = root.get("estrategia_segmentador", "defValue");
  s = s.get("planar_euclidean", "defValue");
  std::cout << "planar_euclidean" << std::endl;
  for (auto itr : s) {
      std::string name = itr.asString();
      std::cout << "\t" << name << std::endl;
  }
  s = root.get("clasificador", "defValue");
  std::cout << "clasificador" << std::endl;
  for (auto itr : s) {
      std::string name = itr.asString();
      std::cout << "\t" << name << std::endl;
  }
  const Json::Value point_feature = root.get("point_feature", "defValue");
  std::cout <<"point_feature" << std::endl;
  std::cout << "\t" <<  point_feature.asString() << std::endl;
  const Json::Value descriptor = root.get("estrategia_descriptor", "defValue");
  std::cout << "estrategia_descriptor" << std::endl;
  std::cout << "\t" << descriptor.asString() << std::endl;
*/
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
  ::testing::InitGoogleTest (&argc, argv);
  return (RUN_ALL_TESTS ());
}