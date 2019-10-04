#include "Block.h"
#include "Bits.h"
#include <list>
#include <iostream>

// PRIVADO
unsigned int Block::__getMax() {
  unsigned int max = this->numbers[0];
  for (int i = 0; i < this->size; i++) {
    if (this->numbers[i] > max) {
      max = this->numbers[i];
    }
  }
  return max;
}

void Block::__setReference() {
  this->reference = this->numbers[0];
  for (int i = 1; i < this->size; i++) {
    if (this->numbers[i] < reference) {
      this->reference = this->numbers[i];
    }
  }
}

void Block::__setMaxBitSize() {
  unsigned int max = __getMax();
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

void Block::__fillList() {
  for (int i = 0; i < this->size; i++) {
    Bits bit_representation(this->bit_size);
    bit_representation.represent(this->numbers[i]);
    for (int j = this->bit_size - 1; j >= 0; j--) {
      this->list_int.push_back(bit_representation.get(j));
    }
  }
}

// PUBLICO
Block::Block(int size) : numbers(size) {
  this->size = size;
}

void Block::process() {
  __setReference();
  for (int i = 0; i < this->size; i++) {
    this->numbers[i] = this->numbers[i] - this->reference;
  }
  __setMaxBitSize();
  __fillList();
}

void Block::addNumber(unsigned int index, unsigned int number) {
  this->numbers[index] = number;
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

int Block::getSize() const {
  return this->size;
}

unsigned int Block::getNumber(unsigned int index) const {
  return this->numbers[index];
}

Block::Block(Block&& other) {
    this->bit_size = other.bit_size;
    this->list_int = std::move(other.list_int);
    this->numbers = std::move(other.numbers);
    this->reference = other.reference;
    this->size = other.size;

    other.bit_size = 0;
    other.reference= 0;
    other.size = 0;
}

Block& Block::operator=(Block &&other) {
    if (this == &other) {
        return *this;
    }
    this->bit_size = other.bit_size;
    this->list_int = std::move(other.list_int);
    this->numbers = std::move(other.numbers);
    this->reference = other.reference;
    this->size = other.size;

    other.bit_size = 0;
    other.reference= 0;
    other.size = 0;
    return *this;
}

Block::~Block() {}
