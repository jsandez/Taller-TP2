#ifndef _FILE_H_
#define _FILE_H_
#include <cstdio>
#include <fstream>
#include <iostream>

class InputStream {
 protected:
  virtual int __getSize() = 0;
  bool failbit;

 public:
  InputStream();
  virtual int getNumberOfBlocks(int block_size) = 0;
  virtual unsigned int getNumber() = 0;
  bool failToOpen() const;
  virtual ~InputStream() = 0;
};

#endif
