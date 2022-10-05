extern "C" {
#include "ext/lpm.h"
}

class LPMWrapper
{
public:
  LPMWrapper()
  {
    d_lpm = lpm_create();
  }
  ~LPMWrapper()
  {
    lpm_destroy(d_lpm);
  }

  void insert(const std::string& str, void* val=(void*)1)
  {
    char addr[16];
    size_t len=sizeof(addr);
    unsigned preflen=0;
    lpm_strtobin(str.c_str(), addr, &len, &preflen);
    if(lpm_insert(d_lpm, addr, len, preflen, val) < 0)
      throw std::runtime_error("Error inserting prefix");    
  }

  void* lookup(const char*str)
  {
    char addr[16];
    size_t len=sizeof(addr);
    unsigned preflen=0;
    lpm_strtobin(str, addr, &len, &preflen);
    return lpm_lookup(d_lpm, addr, len);
  }
  
private:
  lpm_t* d_lpm;
};
