#include <Block.h>
#include <iostream>
#include "OutputStream.h"
#include "InputFileStream.h"

int main(int argc, char **argv) {
  int block_size = atoi(argv[1]);
  int max_elements_by_queue = atoi(argv[2]);
  int number_of_threads = atoi(argv[3]);
  const char *in_file_name = argv[4];
  const char *out_file_name = argv[5];

  InputFileStream input_file_stream(in_file_name);
  if (input_file_stream.failToOpen()) {
    std::cout << "Error intentando abrir archivo de entrada" << std::endl;
    return 1;
  }
  OutputStream output_stream(out_file_name);
  if (output_stream.getFailBit()) {
    std::cout << "Error intentando abrir archivo de salida" << std::endl;
    return 1;
  }

  int cant_bloques = input_file_stream.getNumberOfBlocks(block_size);
  if (cant_bloques == -1) {
    return 1;
  }

  for (int i = 0; i < cant_bloques; i++) {
    Block block(block_size);
    block.fillNumbers(input_file_stream);
    block.process();

    output_stream.setReference(block.getReference());
    output_stream.setBitAmount(block.getBitSize());
    if (block.getBitSize() != 0) {
      block.fillList();
      output_stream.setBits(block.getList());
    }
  }
  return 0;
}
