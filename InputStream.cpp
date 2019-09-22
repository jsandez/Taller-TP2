#include <netinet/in.h>
#include "InputStream.h"

int InputStream::__getSize() {
  this->ifs.seekg(0, this->ifs.end);
  int size = this->ifs.tellg();
  this->ifs.seekg(0, this->ifs.beg);
  return size / 4;
}

int InputStream::__getNumber() {
  char c[4];
  this->ifs.read(c, 4);
  if (this->ifs.gcount() == 0) {
    return -1;
  }
  int value = *((unsigned int *) &c[0]);
  return ntohl(value);
}

InputStream::InputStream(const char *name) : ifs(name, std::ifstream::binary) {
  if (this->ifs.fail()) {
    this->failbit = true;
  } else {
    this->failbit = false;
  }
}

int InputStream::getNumberOfBlocks(int block_size) {
  int size_file = __getSize();
  if (size_file == 0) {
    std::cout << "Empty File!!" << std::endl;
    return -1;
  }
  int cant_bloques = size_file / block_size;
  if (size_file % block_size != 0) {
    cant_bloques++;
  }
  return cant_bloques;
}

void InputStream::fillBlock(Block &block) {
  for (int i = 0; i < block.getSize(); i++) {
    int number = __getNumber();
    if (number != -1) {
      block.addNumber(i, number);
    } else {
      block.addNumber(i, block.lastNumber());
    }
  }
}

bool InputStream::failToOpen() const {
  return this->failbit;
}

InputStream::~InputStream() {
  this->ifs.close();
}
