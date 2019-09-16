#include "Bits.h"

Bits::Bits(int size) {
  this->size = size;
  this->data = new int[size]();
}

void Bits::represent(unsigned int number){
  int i = 0;
  if (number > 0) {
    unsigned long result_division = number;
    int rest = 0;
    while (result_division > 1) {
      result_division = result_division / 2;
      rest = number % 2;
      this->data[i] = rest;
      i++;
    }
    this->data[i] = result_division;
  }
}

bool Bits::get(int pos) const {
  return this->data[pos];
}

Bits::~Bits() {
  delete[] this->data;
}
