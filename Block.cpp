#include "Block.h"
#include "Bits.h"
#include <list>

// PRIVADO
unsigned int Block::getMax() {
  unsigned int max = this->numbers[0];
  for (int i = 0; i < this->size; i++) {
    if (this->numbers[i] > max) {
      max = this->numbers[i];
    }
  }
  return max;
}

void Block::setReference() {
  this->reference = this->numbers[0];
  for (int i = 1; i < this->size; i++) {
    if (this->numbers[i] < reference) {
      this->reference = this->numbers[i];
    }
  }
}

void Block::setMaxBitSize() {
  unsigned int max = getMax();
  unsigned int bits_amount = 1;
  if (max == 0) {
    this->bit_size = 0;
  } else {
    while (max > 1) {
      max = max / 2;
      bits_amount++;
    }
    this->bit_size = bits_amount;
  }
}

// PUBLICO
Block::Block(int size) {
  this->size = size;
  this->numbers = new unsigned int[size]();
}

void Block::fillNumbers(InputStream &input_stream) {
  for (int i = 0; i < this->size; i++) {
    unsigned int number = input_stream.getNumber();
    if (number != -1) {
      this->numbers[i] = number;
    } else {
      this->numbers[i] = this->numbers[i - 1];
    }
  }
  setReference();
}

void Block::resizeNumbers() {
  for (int i = 0; i < this->size; i++) {
    this->numbers[i] = this->numbers[i] - this->reference;
  }
  setMaxBitSize();
}

void Block::fillList() {
  for (int i = 0; i < this->size; i++) {
    Bits bit_representation(this->bit_size);
    bit_representation.represent(this->numbers[i]);
    for (int j = this->bit_size - 1; j >= 0; j--) {
      this->list_int.push_back(bit_representation.get(j));
    }
  }
}

unsigned int Block::getReference() const {
  return this->reference;
}

unsigned int Block::getBitSize() const {
  return this->bit_size;
}

std::list<int> Block::getList() const {
  return this->list_int;
}
Block::~Block() {
  delete[] this->numbers;
}
