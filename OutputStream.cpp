#include <netinet/in.h>
#include <cstring>
#include <bitset>
#include "OutputStream.h"
#include <list>

OutputStream::OutputStream(const char *name): ofs(name,std::iostream::binary) {
    if (this->ofs.fail()) {
        throw std::runtime_error("File output error");
    }
}

void OutputStream::setReference(unsigned int reference) {
  char arr_ref[4];
  unsigned int referenceOut = htonl(reference);
  memcpy(arr_ref, &referenceOut, 4);
  this->ofs.put(arr_ref[0]);
  this->ofs.put(arr_ref[1]);
  this->ofs.put(arr_ref[2]);
  this->ofs.put(arr_ref[3]);
}
void OutputStream::setBitAmount(unsigned int c) {
  this->ofs.put((char) c);
}
void OutputStream::setBits(std::list<int> list) {
  std::bitset<8> bit_set;
  int i = 7;
  for (int entero : list) {
    bit_set[i] = entero;
    i--;
    if (i < 0) {
      this->ofs.put((char) bit_set.to_ulong());
      i = 7;
      bit_set.reset();
    }
  }
  if ((i > 0) && (i < 7)) {
    this->ofs.put((char) bit_set.to_ulong());
  }
}

OutputStream::~OutputStream() {
  this->ofs.close();
}
