#include <iostream>
#include "OutputStream.h"
#include "InputStream.h"
#include "Thread.h"
#include "BlockProcessMonitor.h"
#include "BlockProcess.h"
#include "Block.h"

int main(int argc, char **argv) {
  int block_size = atoi(argv[1]);
  int max_elements_by_queue = atoi(argv[2]);
  int number_of_threads = atoi(argv[3]);
  const char *in_file_name = argv[4];
  const char *out_file_name = argv[5];

  InputStream input_stream(in_file_name);
  if (input_stream.failToOpen()) {
    std::cout << "Error intentando abrir archivo de entrada" << std::endl;
    return 1;
  }
  OutputStream output_stream(out_file_name);
  if (output_stream.getFailBit()) {
    std::cout << "Error intentando abrir archivo de salida" << std::endl;
    return 1;
  }

  int cant_bloques = input_stream.getNumberOfBlocks(block_size);
  if (cant_bloques == -1) {
    return 1;
  }
  BlockProcessMonitor block_process_monitor(input_stream);
  Thread *th = new BlockProcess(block_process_monitor,block_size,output_stream);

  for (int i = 0; i < cant_bloques; i++) {
    th->start();
    /*Block block(block_size);
    input_stream.fillBlock(block);
    block.process();
    output_stream.setReference(block.getReference());
    output_stream.setBitAmount(block.getBitSize());
    if (block.getBitSize() != 0) {
      output_stream.setBits(block.getList());
    }*/
  }
  th->join();
  delete th;
  return 0;
}
