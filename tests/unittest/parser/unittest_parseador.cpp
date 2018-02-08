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
#include "../../../source/parser/include/parseador.hpp"

#include <json/json.h>
#include <string>
#include <unordered_map>
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
char **margv;
int margc;

class ParseadorTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};

// Tests Parseador()
/*
*/
TEST(ParseadorTest, Nombre)
{
  std::cout << margv[0] << std::endl;
  std::cout << margv[1] << std::endl;
  std::cout << margv[2] << std::endl;
  Parseador p;
  int index = p.find_argument(margc, margv, "-f");
  std::cout << index << std::endl;
}
/*
TEST(ParseadorTest, AperturaArchivoJSON)
{
  ParseadorJSON p;
  bool ok = p.open("/home/manjaro-guille/mis_proyectos/clasificadorFallas/tests/unittest/parser/config_pipeline.json");
  EXPECT_EQ(true, ok);
}

TEST(ParseadorTest, GetElementoJSON)
{
  std::cout << "GetElementoJSON" << std::endl;
  ParseadorJSON p;
  bool ok = p.open("/home/manjaro-guille/mis_proyectos/clasificadorFallas/tests/unittest/parser/config_pipeline.json");
  ASSERT_TRUE(p.get_element("database_muestras") == "path_database");
  Json::Value valor = p.get_element("clasificador");
  Json::Value::Members memberNames = valor.getMemberNames();
  EXPECT_EQ(memberNames[0], "dir_salida_dataset");
  EXPECT_EQ(memberNames[1], "path_modelo");
  EXPECT_EQ(memberNames[2], "tipo");
  for(unsigned int i=0; i<memberNames.size(); ++i)
  {
    //string memberName = memberNames[i];
    Json::Value value = valor[memberNames[i]];
    std::cout << "Key: " << memberNames[i] << std::endl;
    std::cout << "Value: " << value.toStyledString() << std::endl;
  }
}
*/
TEST(ParseadorTest, FileExtensionSearch)
{
  Parseador p;
  std::vector<int> index_archivos = p.parse_file_extension_argument(margc, margv, ".json");
  EXPECT_EQ(1, index_archivos.size());
}
//TEST(ParseadorTest, GetElementoRAPIDJSON)
TEST(ParseadorTest, ParametrizadorRAPIDJSON)
{
  ParseadorJSON p;
  //char file_name[] = "/home/manjaro-guille/mis_proyectos/clasificadorFallas/tests/unittest/parser/config_pipeline.json";
  std::vector<int> v = p.parse_file_extension_argument(margc, margv, ".json");
  //bool ok = p.openRapid(file_name);
  bool ok = p.openRapid(margv[v[0]]);
  EXPECT_TRUE(ok);
  /* Parametrizador para test */
  Parametrizador parametrizador;
  parametrizador.setNombre("clasificador");
  Parametro p1;
  p1.setNombre("tipo");
  p1.setTipoValorEsperado("string");
  parametrizador.agregar(p1);
  // p3 no se encuentra en archivo pero no es requerido. No hay problema.
  Parametro p3;
  p3.setNombre("numerico");
  p3.setEsRequerido(false);
  p3.setTipoValorEsperado("float");
  parametrizador.agregar(p3);
  Parametro p2;
  p2.setNombre("path_modelo");
  p2.setTipoValorEsperado("int");
  parametrizador.agregar(p2);
  /* Fin Parametrizador para test */
  std::unordered_map<std::string, std::string> values;
  bool result = p.parser_rapid(&parametrizador, values);
  EXPECT_TRUE(result);
  for (auto i = values.begin(); i != values.end(); ++i)
  {
    std::cout << "Name: " << i->first << std::endl;
    std::cout << "Value: " << i->second << std::endl;
  }
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
  margv = argv;
  margc = argc;
  ::testing::InitGoogleTest (&argc, argv);
  return (RUN_ALL_TESTS ());
}