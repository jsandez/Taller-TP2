#ifndef _OUTPUTFILE_H_
#define _OUTPUTFILE_H_
#include <stdio.h>
#include <fstream>
#include <list>

class OutputStream {
 private:
  std::ofstream *f;

 public:
  OutputStream(const char *name, const char *flags);
  void setReference(char *c);
  void setBitAmount(char c);
  void setBits(std::list<int> list);
  ~OutputStream();

};

#endif
