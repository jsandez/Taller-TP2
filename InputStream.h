#ifndef _FILE_H_
#define _FILE_H_
#include <cstdio>
#include <fstream>
#include <iostream>
#include "Block.h"

class InputStream {
 protected:
  std::ifstream ifs;
  bool failbit;
  int __getSize();
  int __getNumber();

 public:
  explicit InputStream(const char *name);
  int getNumberOfBlocks(int block_size);
  void fillBlock(Block &block);
  bool failToOpen() const;
  ~InputStream();
};

#endif
