#include <iostream>
#include <vector>
#include "OutputStream.h"
#include "InputStream.h"
#include "Thread.h"
#include "BlockProcessMonitor.h"
#include "BlockProducerThread.h"
#include "BlockConsumerThread.h"

int main(int argc, char **argv) {
  if (argc < 6) {
    std::cout << "WRONG ARGS" << std::endl;
  }
  try {
    /*
     * Preparo los archivos de stream segun
     * si van a ser tomados de IO estandar
     * o de archivos.
     */
    std::istream *istream;
    if (argv[4][0] != '-') {
      istream = new std::ifstream(argv[4], std::ifstream::binary);
    } else {
      istream = &std::cin;
    }
    InputStream input_stream(istream, atoi(argv[1]));
    std::ostream *ostream;
    if (argv[5][0] != '-') {
      ostream = new std::ofstream(argv[5], std::ofstream::binary);
    } else {
      ostream = &std::cout;
    }
    OutputStream output_stream(ostream);

    /*
     * ZONA DE THREADS
     */
    // Creo los threads
    int number_of_blocks = input_stream.getNumberOfBlocks();
    std::vector<Thread *> ths;
    std::vector<ThreadSafeQueue *> queues;
    BlockProcessMonitor block_process_monitor(input_stream);

    // Threads productores
    for (int i = 0; i < atoi(argv[3]); i++) {
      ThreadSafeQueue *thread_safe_queue =
          new ThreadSafeQueue(atoi(argv[2]));
      ths.push_back(new BlockProducerThread(block_process_monitor,
                                            atoi(argv[1]),
                                            number_of_blocks,
                                            i,
                                            atoi(argv[3]),
                                            thread_safe_queue));
      queues.push_back(thread_safe_queue);
    }
    // Thread consumidor
    BlockConsumerThread th_consumer(queues,
                                    number_of_blocks,
                                    output_stream);
    // Run threads
    for (int i = 0; i < atoi(argv[3]); i++) {
      ths[i]->start();
    }
    th_consumer.start();

    // Join threads
    for (int i = 0; i < atoi(argv[3]); i++) {
      ths[i]->join();
    }
    th_consumer.join();

    // Delete threads y streams
    for (int i = 0; i < atoi(argv[3]); i++) {
      delete ths[i];
    }
    delete istream;
    delete ostream;
  }
  catch (const std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}
