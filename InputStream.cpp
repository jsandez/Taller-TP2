#include "InputStream.h"

InputStream::InputStream() {}

bool InputStream::failToOpen() const {
  return this->failbit;
}

InputStream::~InputStream() {}