#ifndef _FILE_H_
#define _FILE_H_
#include <cstdio>
#include <fstream>
#include <iostream>
#include "Block.h"

class InputStream {
 protected:
  std::ifstream ifs;
  int size;
  int number_of_blocks;
  bool failbit;
  int __getNumber();
  void __setNumberOfBlocks(int block_size);

 public:
  explicit InputStream(const char *name, int block_size);
  void fillBlock(Block &block, int block_number);
  bool failToOpen() const;
  int getNumberOfBlocks() const;
  ~InputStream();
};

#endif
