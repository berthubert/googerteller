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


TEST_CASE("IPv6 test") {
  LPMWrapper t;
  void* ptr = (void*)1;
  t.insert("::1", ptr);
  
  CHECK(t.lookup("::1") == ptr);
  CHECK(t.lookup("::2") == 0);
}


TEST_CASE("Mixed test") {
  LPMWrapper t;
  void* ptr = (void*)1;
  t.insert("::1", ptr);

  ptr = (void*)2;
  t.insert("192.168.0.0/16", ptr);


  CHECK(t.lookup("::1") == (void*)1);
  CHECK(t.lookup("192.168.1.1") == (void*)2);
  CHECK(t.lookup("192.168.255.255") == (void*)2);
  CHECK(t.lookup("10.0.0.1") == 0);
  CHECK(t.lookup("172.16.2.3") == 0);
  CHECK(t.lookup("1.0.0.0") == 0);
  
  
}


