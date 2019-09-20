#ifndef _INPUTFILESTREAM_H_
#define _INPUTFILESTREAM_H_
#include "InputStream.h"

class InputFileStream : public InputStream {
 private:
  std::ifstream ifs;
  int __getSize();

 public:
  InputFileStream(const char *name);
  int getNumberOfBlocks(int block_size);
  unsigned int getNumber();
  ~InputFileStream();
};

#endif
