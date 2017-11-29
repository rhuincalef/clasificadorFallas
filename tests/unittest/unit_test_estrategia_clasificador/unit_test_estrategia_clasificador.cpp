// Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include <string>
#include <limits.h>
//Se incluye el .hpp de estrategia_clasificador
#include "../../../source/ML/include/estrategia_clasificacion.hpp"

//#include "gtest/gtest.h"
//#include "../../googletest/include/gtest/gtest.h"
#include "../../googletest-release-1.8.0/googletest/include/gtest/gtest.h"

namespace {

// The fixture for testing class Foo.
class EstrategiaClasificacionSVMTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  EstrategiaClasificacionSVMTest() {
    // You can do set-up work for each test here.
  }

  virtual ~EstrategiaClasificacionSVMTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).


  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
  //EstrategiaClasificacionSVM estrClasificacion;
    
};

// Test de fixture que verifica si la estrategia de clasificacion valida el path del datasetTmp
TEST_F(EstrategiaClasificacionSVMTest, seValidaPathTmpDataset) {
  //EXPECT_EQ(1,estrClasificacion.leerDatasetTmp(""));
  //EXPECT_EQ(1,estrClasificacion.leerDatasetTmp("/path/to/non-existent/file.dat"));


  /*
  EXPECT_EQ(1,estrClasificacion->leerDatasetTmp(""));
  EXPECT_EQ(1,estrClasificacion->leerDatasetTmp("/path/to/non-existent/file.dat"));
  */


  /*const string input_filepath = "this/package/testdata/myinputfile.dat";
  const string output_filepath = "this/package/testdata/myoutputfile.dat";
  Foo f;
  EXPECT_EQ(0, f.Bar(input_filepath, output_filepath));*/
}

}  //end namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/*
//Default
namespace {

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  FooTest() {
    // You can do set-up work for each test here.
  }

  virtual ~FooTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(FooTest, MethodBarDoesAbc) {
  const string input_filepath = "this/package/testdata/myinputfile.dat";
  const string output_filepath = "this/package/testdata/myoutputfile.dat";
  Foo f;
  EXPECT_EQ(0, f.Bar(input_filepath, output_filepath));
}

// Tests that Foo does Xyz.
TEST_F(FooTest, DoesXyz) {
  // Exercises the Xyz feature of Foo.
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
*/