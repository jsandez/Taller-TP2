#include "Block.h"
#include <list>

Block::Block(int size) {
  this->size = size;
  this->numbers = new unsigned int[size]();
}

void Block::setNumbers(InputStream &input_stream) {
  for (int i = 0; i < this->size; i++) {
    this->numbers[i] = input_stream.getNumber();
  }
}

void Block::setReference() {
  this->reference = this->numbers[0];
  for (int i = 1; i < this->size; i++) {
    if (this->numbers[i] < reference) {
      this->reference = this->numbers[i];
    }
  }
}

void Block::numbersDifference() {
  for (int i = 0; i < this->size; i++) {
    this->numbers[i] = this->numbers[i] - this->reference;
  }
}

unsigned int Block::getMax() {
  unsigned int max = this->numbers[0];
  for (int i = 0; i < this->size; i++) {
    if (this->numbers[i] > max) {
      max = this->numbers[i];
    }
  }
  return max;
}

unsigned int Block::getReference() const {
  return this->reference;
}

unsigned int Block::getNumber(int pos) const {
  return this->numbers[pos];
}

unsigned int Block::getMaxBitSize() {
  unsigned int max = getMax();
  unsigned int bits_amount = 1;
  if (max == 0) {
    return 0;
  } else {
    while (max > 1) {
      max = max / 2;
      bits_amount++;
    }
  }
  return bits_amount;
}

void Block::addList(int value) {
  this->list_int.push_back(value);
}
std::list<int> Block::getList() const {
  return this->list_int;
}
Block::~Block() {
  delete[] this->numbers;
}
