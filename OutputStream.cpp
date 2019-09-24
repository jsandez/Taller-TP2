#include <netinet/in.h>
#include <cstring>
#include <bitset>
#include "OutputStream.h"
#include <list>

OutputStream::OutputStream(std::ostream *ostream) : os(ostream) {
  if (this->os->fail()) {
    throw std::runtime_error("File output error");
  }
}

void OutputStream::setReference(unsigned int reference) {
  char arr_ref[4];
  unsigned int referenceOut = htonl(reference);
  memcpy(arr_ref, &referenceOut, 4);
  this->os->put(arr_ref[0]);
  this->os->put(arr_ref[1]);
  this->os->put(arr_ref[2]);
  this->os->put(arr_ref[3]);
}
void OutputStream::setBitAmount(unsigned int c) {
  this->os->put((char) c);
}
void OutputStream::setBits(std::list<int> list) {
  std::bitset<8> bit_set;
  int i = 7;
  for (int entero : list) {
    bit_set[i] = entero;
    i--;
    if (i < 0) {
      this->os->put((char) bit_set.to_ulong());
      i = 7;
      bit_set.reset();
    }
  }
  if ((i > 0) && (i < 7)) {
    this->os->put((char) bit_set.to_ulong());
  }
}

OutputStream::~OutputStream() {}
