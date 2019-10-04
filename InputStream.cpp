#include <netinet/in.h>
#include <cstring>
#include "InputStream.h"

void InputStream::__setNumberOfBlocks(int block_size) {
  if (this->size == 0) {
    std::cout << "Empty File!!" << std::endl;
    this->number_of_blocks = -1;
  } else {
    int cant_bloques = this->size / block_size;
    if (this->size % block_size != 0) {
      cant_bloques++;
    }
    this->number_of_blocks = cant_bloques;
  }
}

unsigned int InputStream::__getNumber() {
  unsigned int value;
  this->is->read((char *) &value, 4);
  return ntohl(value);
}

InputStream::InputStream(std::istream *stream, int block_size)
    : is(stream) {
  if (this->is->fail()) {
    throw std::runtime_error("File input error");
  } else {
    this->is->seekg(0, this->is->end);
    int size = this->is->tellg();
    this->is->seekg(0, this->is->beg);
    this->size = size / 4;
    __setNumberOfBlocks(block_size);
  }
}

void InputStream::fillBlock(Block &block, int block_number) {
  this->is->seekg(block_number * 4 * block.getSize(), this->is->beg);
  for (int i = 0; i < block.getSize(); i++) {
    int number = __getNumber();
    if (number != -1) {
      block.addNumber(i, number);
    } else {
      block.addNumber(i, block.getNumber(i - 1));
    }
  }
  this->is->seekg(0, this->is->beg);
}

int InputStream::getNumberOfBlocks() const {
  if (this->number_of_blocks == -1) {
    throw new std::runtime_error("No hay bloques a procesar");
  }
  return this->number_of_blocks;
}
