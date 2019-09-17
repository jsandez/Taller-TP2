#include <netinet/in.h>
#include <cstring>
#include <bitset>
#include "OutputStream.h"

OutputStream::OutputStream(const char *name) {
  this->f = new std::ofstream;
  this->f->open(name, std::iostream::binary);
}

void OutputStream::setReference(unsigned int reference) {
  char arr_ref[4];
  unsigned int referenceOut = htonl(reference);
  memcpy(arr_ref, &referenceOut, 4);
  this->f->put(arr_ref[0]);
  this->f->put(arr_ref[1]);
  this->f->put(arr_ref[2]);
  this->f->put(arr_ref[3]);
}
void OutputStream::setBitAmount(unsigned int c) {
  this->f->put((char) c);
}
void OutputStream::setBits(std::list<int> list) {
  std::bitset<8> bit_set;
  int i = 7;
  for (int entero : list) {
    bit_set[i] = entero;
    i--;
    if (i < 0) {
      this->f->put((char) bit_set.to_ulong());
      i = 7;
      bit_set.reset();
    }
  }
  if ((i > 0) && (i < 7)) {
    this->f->put((char) bit_set.to_ulong());
  }
}

OutputStream::~OutputStream() {
  this->f->close();
  delete this->f;
}
