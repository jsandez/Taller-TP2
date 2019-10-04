#include <bitset>
#include "OutputStream.h"
#include <list>
#include <netinet/in.h>
#include <cstring>

OutputStream::OutputStream(std::ostream *ostream) : os(ostream) {
  if (this->os->fail()) {
    throw std::runtime_error("File output error");
  }
}

void OutputStream::setReference(unsigned int reference) {
  unsigned int reference_out(htonl(reference));
  this->os->write((const char *) &reference_out, 4);
}

void OutputStream::setBitAmount(unsigned int c) {
  this->os->put((char) c);
}

void OutputStream::setBits(const std::list<int>& list) {
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
