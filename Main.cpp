#include <iostream>
#include "OutputStream.h"
#include "InputStream.h"
#include "Thread.h"
#include "BlockProcessMonitor.h"
#include "BlockProducer.h"
#include "Block.h"

int main(int argc, char **argv) {
  int block_size = atoi(argv[1]);
  int max_elements_by_queue = atoi(argv[2]);
  int number_of_threads = atoi(argv[3]);
  const char *in_file_name = argv[4];
  const char *out_file_name = argv[5];

  InputStream input_stream(in_file_name, block_size);
  if (input_stream.failToOpen()) {
    std::cout << "Error intentando abrir archivo de entrada" << std::endl;
    return 1;
  }
  OutputStream output_stream(out_file_name);
  if (output_stream.getFailBit()) {
    std::cout << "Error intentando abrir archivo de salida" << std::endl;
    return 1;
  }

  int number_of_blocks = input_stream.getNumberOfBlocks();
  if (number_of_blocks == -1) {
    return 1;
  }

  std::vector<Thread *> ths;
  BlockProcessMonitor block_process_monitor(input_stream);
  for (int i = 0; i < number_of_threads; i++) {
    ths.push_back(new BlockProducer(block_process_monitor,
                                    block_size,
                                    number_of_blocks,
                                    i,
                                    number_of_threads,
                                    output_stream));
  }

  for (int i = 0; i < number_of_threads; i++) {
    ths[i]->start();
  }

  for (int i = 0; i < number_of_threads; i++) {
    ths[i]->join();
    delete ths[i];
  }

  return 0;
}
