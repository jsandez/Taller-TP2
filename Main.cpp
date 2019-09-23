#include <iostream>
#include <vector>
#include "OutputStream.h"
#include "InputStream.h"
#include "Thread.h"
#include "BlockProcessMonitor.h"
#include "BlockProducerThread.h"
#include "BlockConsumerThread.h"

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
  std::vector<ThreadSafeQueue *> queues;
  BlockProcessMonitor block_process_monitor(input_stream);
  for (int i = 0; i < number_of_threads; i++) {
    ThreadSafeQueue *thread_safe_queue =
                new ThreadSafeQueue(max_elements_by_queue);
    ths.push_back(new BlockProducerThread(block_process_monitor,
                                          block_size,
                                          number_of_blocks,
                                          i,
                                          number_of_threads,
                                          thread_safe_queue));
    queues.push_back(thread_safe_queue);
  }
  Thread *th_consumer =
              new BlockConsumerThread(queues, number_of_blocks, output_stream);

  for (int i = 0; i < number_of_threads; i++) {
    ths[i]->start();
  }
  th_consumer->start();

  for (int i = 0; i < number_of_threads; i++) {
    ths[i]->join();
  }
  th_consumer->join();

  for (int i = 0; i < number_of_threads; i++) {
    delete ths[i];
  }
  delete th_consumer;

  return 0;
}
