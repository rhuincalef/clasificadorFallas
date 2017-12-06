
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
#include "../../../source/ML/include/formateador_dataset.hpp"
#include "../../../source/ML/include/estrategia_clasificacion.hpp"
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
class EstrategiaClasificacionSVMTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};


TEST(EstrategiaClasificacionSVMTest, cargarModelo)
{
  srand (time (NULL));

  EstrategiaClasificacionMLAbstract* estratClasificacion = new EstrategiaClasificacionSVM<pcl::GRSDSignature21,svm_problem,svm_model,pcl::PointXYZRGB>();
  EXPECT_EQ(1,estratClasificacion->cargarModelo("MODELO_NO_EXISTENTE.DAT"));
}



TEST(EstrategiaClasificacionSVMTest, setGetFormateador)
{
  srand (time (NULL));

  EstrategiaClasificacionMLAbstract* estratClasificacion = new EstrategiaClasificacionSVM<pcl::GRSDSignature21,svm_problem,svm_model,pcl::PointXYZRGB>();
  
  FormateadorDatasetAbstract* f = NULL;
  estratClasificacion->setFormateador(f);
  EXPECT_EQ(NULL,estratClasificacion->getFormateador());
}


//NOTA: Se chequean los getters y setters calculados de PointFeature 
TEST(EstrategiaClasificacionSVMTest, clasificarGRSD)
{
  srand (time (NULL));

  EstrategiaDescriptorsAbstract<pcl::PointXYZRGB>* estrategiaGRSD = new GRSD<pcl::PointXYZRGB,pcl::GRSDSignature21,PointFeatureGRSD>();

  Nube<pcl::PointXYZRGB>* n = new Nube<pcl::PointXYZRGB>(pcdNoEscaneado);

  
  
  //PointT,SignatureT,PointFeatureT
  PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* descriptor = NULL;
  descriptor = estrategiaGRSD->template generarDescriptor<pcl::PointXYZRGB,pcl::GRSDSignature21,
                                                                  PointFeatureGRSD>(n);
  std::cout <<"despues de generar descriptor GRSD" << std::endl;

  ASSERT_NE(NULL,descriptor);
  EXPECT_LT(0,descriptor->getDescriptorPCL().points.size());
  EXPECT_LT(0,descriptor->getDiffAltoAncho());

  EstrategiaClasificacionMLAbstract* estratClasificacion = NULL;
  estratClasificacion = new EstrategiaClasificacionSVM<pcl::GRSDSignature21,svm_problem,svm_model,pcl::PointXYZRGB>();
 

  ASSERT_NE("",estrategiaGRSD->getPathModeloEntrenado());

  int resultado = -1;
  resultado = estratClasificacion->template clasificar<pcl::GRSDSignature21,pcl::PointXYZRGB,
                                            svm_problem,svm_model,pcl::SVMData>(
                                                estrategiaGRSD->getPathModeloEntrenado(),descriptor);

  EXPECT_NE(-1,resultado);
  EXPECT_TRUE( (resultado == 1 || resultado == 2) );
}


//NOTA: Se chequean los getters y setters calculados de PointFeature 
TEST(EstrategiaClasificacionSVMTest, clasificarESF)
{
  srand (time (NULL));

  EstrategiaDescriptorsAbstract<pcl::PointXYZRGB>* estrategiaGRSD = new ESF<pcl::PointXYZRGB,pcl::ESFSignature640,PointFeatureESF>();

  Nube<pcl::PointXYZRGB>* n = new Nube<pcl::PointXYZRGB>(pcdNoEscaneado);

  
  
  //PointT,SignatureT,PointFeatureT
  PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* descriptor = NULL;
  descriptor = estrategiaGRSD->template generarDescriptor<pcl::PointXYZRGB,pcl::ESFSignature640,
                                                                  PointFeatureESF>(n);
  std::cout <<"despues de generar descriptor GRSD" << std::endl;

  ASSERT_NE(NULL,descriptor);
  EXPECT_LT(0,descriptor->getDescriptorPCL().points.size());
  EXPECT_LT(0,descriptor->getDiffAltoAncho());

  EstrategiaClasificacionMLAbstract* estratClasificacion = NULL;
  estratClasificacion = new EstrategiaClasificacionSVM<pcl::ESFSignature640,svm_problem,svm_model,pcl::PointXYZRGB>();
 

  ASSERT_NE("",estrategiaGRSD->getPathModeloEntrenado());

  int resultado = -1;
  resultado = estratClasificacion->template clasificar<pcl::ESFSignature640,pcl::PointXYZRGB,
                                            svm_problem,svm_model,pcl::SVMData>(
                                                estrategiaGRSD->getPathModeloEntrenado(),descriptor);

  EXPECT_NE(-1,resultado);
  EXPECT_TRUE( (resultado == 1 || resultado == 2) );
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

//Modo de prueba -->
// ./unittest_estrategia_clasificacion REAL_BACHE.pcd /home/rodrigo/TESINA-2016-KINECT/MACHINE_LEARNING/clasificadorFallas/modelo_grsd/modelo.dat /home/rodrigo/TESINA-2016-KINECT/MACHINE_LEARNING/clasificadorFallas/modelo_esf/modelo.dat 

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