#include <netinet/in.h>
#include <cstring>
#include "InputStream.h"

void InputStream::__setNumberOfBlocks(int block_size) {
    if (this->size == 0) {
        std::cout << "Empty File!!" << std::endl;
        this->number_of_blocks = -1;
    } else {
        int cant_bloques = this->size / block_size;
        if (this->size % block_size != 0) {
            cant_bloques++;
        }
        this->number_of_blocks = cant_bloques;
    }
}

int InputStream::__getNumber() {
    char c[4];
    this->ifs.read(c, 4);
    if (this->ifs.gcount() == 0) {
        return -1;
    }
    int value;
    memcpy(&value, c, 4);
    return ntohl(value);
}

InputStream::InputStream(const char *name, int block_size)
        : ifs(name, std::ifstream::binary) {
    if (this->ifs.fail()) {
        throw std::runtime_error("File input error");
    } else {
        this->ifs.seekg(0, this->ifs.end);
        int size = this->ifs.tellg();
        this->ifs.seekg(0, this->ifs.beg);
        this->size = size / 4;
        __setNumberOfBlocks(block_size);
    }
}

void InputStream::fillBlock(Block &block, int block_number) {
    this->ifs.seekg(block_number * 4 * block.getSize(), this->ifs.beg);
    for (int i = 0; i < block.getSize(); i++) {
        int number = __getNumber();
        if (number != -1) {
            block.addNumber(i, number);
        } else {
            block.addNumber(i, block.getNumber(i - 1));
        }
    }
    this->ifs.seekg(0, this->ifs.beg);
}

int InputStream::getNumberOfBlocks() const {
    return this->number_of_blocks;
}

InputStream::~InputStream() {
    this->ifs.close();
}
