#ifndef _OUTPUTFILE_H_
#define _OUTPUTFILE_H_
#include <stdio.h>
#include <fstream>
#include <list>

class OutputStream {
 private:
  std::ofstream ofs;
  bool failbit;

 public:
  explicit OutputStream(const char *name);
  void setReference(unsigned int reference);
  void setBitAmount(unsigned int c);
  void setBits(std::list<int> list);
  bool getFailBit() const;
  ~OutputStream();
};

#endif
