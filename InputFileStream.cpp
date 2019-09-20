#include <netinet/in.h>
#include "InputFileStream.h"

int InputFileStream::__getSize() {
  this->ifs.seekg(0, this->ifs.end);
  int size = this->ifs.tellg();
  this->ifs.seekg(0, this->ifs.beg);
  return size / 4;
}

InputFileStream::InputFileStream(const char *name) : InputStream(), ifs(name, std::ifstream::binary) {
  if (this->ifs.fail()) {
    this->failbit = true;
  } else {
    this->failbit = false;
  }
}

int InputFileStream::getNumberOfBlocks(int block_size) {
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

unsigned int InputFileStream::getNumber() {
  char c[4];
  this->ifs.read(c, 4);
  if (this->ifs.gcount() == 0) {
    return -1;
  }
  int value = *((unsigned int *) &c[0]);
  return ntohl(value);
}

InputFileStream::~InputFileStream() {
  this->ifs.close();
}
