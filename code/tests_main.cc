#include "test_board.hh"
#include <cppunit/ui/text/TestRunner.h>

int main ()
{
  CppUnit::TextUi::TestRunner runner;
  
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  runner.run();
  
  return EXIT_SUCCESS;
}
