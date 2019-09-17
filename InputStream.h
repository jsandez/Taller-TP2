#ifndef _FILE_H_
#define _FILE_H_
#include <cstdio>
#include <fstream>

class InputStream {
 private:
  std::ifstream *f;

 public:
  InputStream(const char *name);
  int size();
  unsigned int getNumber();
  ~InputStream();

};

#endif
