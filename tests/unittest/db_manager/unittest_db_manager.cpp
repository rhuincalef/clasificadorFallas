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
#include "../../../source/db_manager/include/db_manager.hpp"

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

int db_argc;
char **db_argv;

class DBManagerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};

/*
*/
TEST(DBManagerTest, AbrirConexion)
{
  DBManager db;
  bool result = db.abrirConexion(db_argv[1]);
  EXPECT_TRUE (result);
  result = db.cerrarConexion();
  EXPECT_TRUE (result);
}

TEST(DBManagerTest, EjecutarConsulta)
{
  DBManager db;
  bool result = db.abrirConexion(db_argv[1]);
  EXPECT_TRUE (result);
  result = db.estaProcesada(1, "letter/algo/mas.pcd");
  EXPECT_TRUE (result);
  result = db.estaProcesada(10, "letter/algo/mas.pcd");
  EXPECT_FALSE(result);
  result = db.cerrarConexion();
  EXPECT_TRUE (result);
}

TEST(DBManagerTest, Insertar)
{
  DBManager db;
  bool result = db.abrirConexion(db_argv[1]);
  EXPECT_TRUE (result);
  result = db.insertar(4, "letter/algo/mas.pcd");
  EXPECT_TRUE (result);
  result = db.cerrarConexion();
  EXPECT_TRUE (result);
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
  db_argc = argc;
  db_argv = argv;
  ::testing::InitGoogleTest (&argc, argv);
  return (RUN_ALL_TESTS ());
}
