#include <istream>
#include <netinet/in.h>
#include "InputStream.h"

InputStream::InputStream(const char *name) {
    this->f = new std::ifstream;
    this->f->open(name, std::iostream::binary);
    if (this->f->fail()) {
        this->failbit = true;
    } else {
        this->failbit = false;
    }
}

int InputStream::size() {
    this->f->seekg(0, this->f->end);
    int size = this->f->tellg();
    this->f->seekg(0, this->f->beg);
    return size / 4;
}

unsigned int InputStream::getNumber() {
    char c[4];
    this->f->read(c, 4);
    if (this->f->gcount() == 0) {
        return -1;
    }
    int value = *((unsigned int *) &c[0]);
    return ntohl(value);
}

bool InputStream::getFailBit() const {
    return this->failbit;
}
InputStream::~InputStream() {
    this->f->close();
    delete this->f;
}
