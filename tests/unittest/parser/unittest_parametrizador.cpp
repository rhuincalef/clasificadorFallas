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
#include "../../../source/parser/include/parametrizador.hpp"

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

class ParametrizadorTest : public ::testing::Test {
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
TEST(ParametrizadorTest, Nombre)
{
  std::string nombre = "un_nombre";
  Parametrizador parametrizador;
  parametrizador.setNombre (nombre);
  EXPECT_EQ (nombre, parametrizador.getNombre());
}

TEST(ParametoTest, Nombre)
{
  std::string nombre = "un_nombre_parametro";
  Parametro p;
  p.setNombre (nombre);
  EXPECT_EQ (nombre, p.getNombre());
}

TEST(ParametoTest, ValorEsperado)
{
  std::string valor_esp = "valor_esperado_parametro";
  Parametro p;
  p.setValorEsperado (valor_esp);
  EXPECT_EQ (valor_esp, p.getValorEsperado());
}

TEST(ParametoTest, EsOpcional)
{
  bool opcional = false;
  Parametro p;
  EXPECT_EQ (true, p.esOpcional());
  p.setEsOpcional (opcional);
  EXPECT_EQ (opcional, p.esOpcional());
}
TEST(ParametrizadorTest, Agregar)
{
  std::string nombre = "un_nombre";
  Parametrizador parametrizador;
  parametrizador.setNombre (nombre);
  EXPECT_EQ (nombre, parametrizador.getNombre());
  Parametro p;
  std::string nombre_p = "un_nombre_p";
  p.setNombre (nombre_p);
  std::string valor_esp_p = "int";
  p.setValorEsperado (valor_esp_p);
  parametrizador.agregar (p);
  std::vector<Parametro> lista_params;
  lista_params = parametrizador.getParametros();
  EXPECT_EQ (1, lista_params.size());
  EXPECT_EQ (nombre_p, lista_params[0].getNombre());
  EXPECT_EQ (valor_esp_p, lista_params[0].getValorEsperado());
  EXPECT_EQ (true, lista_params[0].esOpcional());
}
/*
*/
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
  ::testing::InitGoogleTest (&argc, argv);
  return (RUN_ALL_TESTS ());
}