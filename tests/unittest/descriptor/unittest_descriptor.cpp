
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
#include "../../../source/nube/include/nube.hpp"
#include "../../../source/descriptor/include/descriptor.hpp"
#include "../../../source/descriptor/include/pointfeature.hpp"
#include "../../../source/descriptor/include/pointfeaturederivadas.hpp"
#include <pcl/io/pcd_io.h>

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
std::string pcdNoEscaneado;
std::string pathModeloGRSD;
std::string pathModeloESF;

/*
*/


/******************************************** Estrategia de descriptor GRSD  ********************************************/
class GRSDTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};

// Tests PlanarAndEuclidean()
TEST(GRSDTest, PathModeloEntrenado)
{
  srand (time (NULL));

  GRSD<pcl::PointXYZRGB,pcl::GRSDSignature21,PointFeatureGRSD>* descGRSD = new GRSD<pcl::PointXYZRGB,pcl::GRSDSignature21,PointFeatureGRSD>();
  EXPECT_NE("",descGRSD->getPathModeloEntrenado());
}



//NOTA: Se chequean los getters y setters calculados de PointFeature 
TEST(GRSDTest, generarDescriptor)
{
  srand (time (NULL));

  EstrategiaDescriptorsAbstract<pcl::PointXYZRGB>* estrategiaGRSD = new GRSD<pcl::PointXYZRGB,pcl::GRSDSignature21,PointFeatureGRSD>();

  Nube<pcl::PointXYZRGB>* n = new Nube<pcl::PointXYZRGB>(pcdNoEscaneado);

  
  std::cout <<"antes de generar descriptor GRSD" << std::endl;
  //PointT,SignatureT,PointFeatureT
  PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* pointFeature = estrategiaGRSD->template generarDescriptor<pcl::PointXYZRGB,
                                                                                                                  pcl::GRSDSignature21,
                                                                                                                  PointFeatureGRSD>(n);
  std::cout <<"despues de generar descriptor GRSD" << std::endl;

  EXPECT_LT(0,pointFeature->getDescriptorPCL().points.size());
  EXPECT_LT(0,pointFeature->getDiffAltoAncho());
}

/*
//NOTA: Se chequean los getters y setters calculados de PointFeature 
TEST(GRSDTest, generarDescriptor)
{
  srand (time (NULL));

  //GRSD<pcl::PointXYZRGB>* estrategiaGRSD = new GRSD<pcl::PointXYZRGB>();
  EstrategiaDescriptorsAbstract<pcl::PointXYZRGB,pcl::GRSDSignature21,PointFeatureGRSD>* estrategiaGRSD = new GRSD<pcl::PointXYZRGB>();

  Nube<pcl::PointXYZRGB>* n = new Nube<pcl::PointXYZRGB>(pcdNoEscaneado);

  //PointFeatureGRSD<pcl::PointXYZRGB>* pointFeature = estrategiaGRSD->generarDescriptor(n);
  std::cout <<"antes de generar descriptor GRSD" << std::endl;
  //PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* pointFeature = estrategiaGRSD->generarDescriptor(n);
  PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* pointFeature = estrategiaGRSD->generarDescriptor(n);

  std::cout <<"despues de generar descriptor GRSD" << std::endl;

  EXPECT_LT(0,pointFeature->getDescriptorPCL().points.size());
  EXPECT_LT(0,pointFeature->getDiffAltoAncho());
}

*/

/******************************************** Estrategia de descriptor ESF  ********************************************/
class ESFTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};

// Tests PlanarAndEuclidean()

TEST(ESFTest, PathModeloEntrenado)
{
  srand (time (NULL));

  ESF<pcl::PointXYZRGB,pcl::ESFSignature640,PointFeatureESF>* descESF = new ESF<pcl::PointXYZRGB,pcl::ESFSignature640,PointFeatureESF>();
  
  EXPECT_NE("",descESF->getPathModeloEntrenado());
}

//NOTA: Se chequean los getters y setters calculados de PointFeature 
TEST(ESFTest, generarDescriptor)
{

  srand (time (NULL));

  EstrategiaDescriptorsAbstract<pcl::PointXYZRGB>* estrategiaESF = new ESF<pcl::PointXYZRGB,pcl::ESFSignature640,PointFeatureESF>();

  Nube<pcl::PointXYZRGB>* n = new Nube<pcl::PointXYZRGB>(pcdNoEscaneado);

  
  std::cout <<"antes de generar descriptor GRSD" << std::endl;
  //PointT,SignatureT,PointFeatureT
  PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* pointFeature = estrategiaESF->template generarDescriptor<pcl::PointXYZRGB,
                                                                                                                  pcl::ESFSignature640,
                                                                                                                  PointFeatureESF>(n);
  std::cout <<"despues de generar descriptor GRSD" << std::endl;

  EXPECT_LT(0,pointFeature->getDescriptorPCL().points.size());
  EXPECT_LT(0,pointFeature->getDiffAltoAncho());
}


/*
//NOTA: Se chequean los getters y setters calculados de PointFeature 
TEST(ESFTest, generarDescriptor)
{
  srand (time (NULL));

  ESF<pcl::PointXYZRGB>* estrategiaESF = new ESF<pcl::PointXYZRGB>();
  Nube<pcl::PointXYZRGB>* n = new Nube<pcl::PointXYZRGB>(pcdNoEscaneado);
  
  //PointFeatureESF<pcl::ESFSignature640,pcl::PointXYZRGB>* pointFeature = descESF->generarDescriptor(n);
  PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* pointFeature = estrategiaESF->generarDescriptor(n);
  
  EXPECT_GT(0,pointFeature->getDescriptorPCL().points.size());
  EXPECT_GT(0,pointFeature->getDiffAltoAncho());
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
*/
//Modo de prueba -->
// ./unittest_descriptor REAL_BACHE.pcd /home/rodrigo/TESINA-2016-KINECT/MACHINE_LEARNING/clasificadorFallas/modelo_grsd/modelo.dat /home/rodrigo/TESINA-2016-KINECT/MACHINE_LEARNING/clasificadorFallas/modelo_esf/modelo.dat 

int
main (int argc, char** argv)
{
  //if (argc < 2)
  if (argc < 3)
  {
    std::cerr << "Erorr de parametros. Modo de uso: " << argv[0] << " <MUESTRA.pcd> <PATH_MODELO_ENTRENADO_GRSD.dat> <PATH_MODELO_ENTRENADO_ESF.dat>" << std::endl;
    return (-1);
  }

  //MUESTRA.pcd -->
  pcdNoEscaneado = argv[1];
  //PATH MODELO_GRSD -->
  pathModeloGRSD = argv[2];

  //PATH MODELO_ESF -->
  pathModeloESF = argv[3];


  // Read a PCD file from disk.
  //if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *cloud) != 0)
  if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(argv[1], *cloud) != 0)
  {
    std::cerr << "Failed to read test file. Please download `bachecitos_tw_4.pcd` and pass its path to the test." << std::endl;
    return -1;
  }


  ::testing::InitGoogleTest (&argc, argv);
  return (RUN_ALL_TESTS ());
  /*
  */
}