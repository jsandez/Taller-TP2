#ifndef _FILE_H_
#define _FILE_H_
#include <cstdio>
#include <fstream>

class InputStream {
 private:
  std::ifstream *f;
  bool failbit;

 public:
  InputStream(const char *name);
  int size();
  unsigned int getNumber();
  bool getFailBit() const;
  ~InputStream();

};

#endif
