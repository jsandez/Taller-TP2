#include <InputStream.h>
#include <Block.h>
#include <iostream>
#include "OutputStream.h"

int main() {
  InputStream input_stream("largenum");
  OutputStream output_stream("myfile-asd");

  int N = 4;
  int size_file = input_stream.size();

  if (size_file == 0) {
    std::cout << "Empty File!!" << std::endl;
    return -1;
  }
  int cant_bloques = size_file / N;
  if (size_file % N != 0) {
    cant_bloques++;
  }

  for (int i = 0; i < cant_bloques; i++) {
    Block block(N);

    block.fillNumbers(input_stream);
    block.resizeNumbers();

    output_stream.setReference(block.getReference());
    output_stream.setBitAmount(block.getBitSize());

    if (block.getBitSize() != 0) {
      block.fillList();
      output_stream.setBits(block.getList());
    }
  }
  return 0;
}
