#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "ext/doctest.h"
#include "lpmwrapper.hh"
using namespace std;

TEST_CASE("basic test") {
  LPMWrapper t;
  void* ptr = (void*)1;
  t.insert("127.0.0.1/32", ptr);
  
  CHECK(t.lookup("127.0.0.1") == ptr);
  CHECK(t.lookup("127.0.0.2") == 0);
}


