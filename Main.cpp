#include <iostream>
#include <vector>
#include "OutputStream.h"
#include "InputStream.h"
#include "Thread.h"
#include "BlockProcessMonitor.h"
#include "BlockProducerThread.h"
#include "BlockConsumerThread.h"

static void __checkArgs(int argc) {
    if (argc < 6) {
        throw std::invalid_argument("WRONG ARGS");
    }
}

int main(int argc, char **argv) {
    try {
        __checkArgs(argc);
    }
    catch (const std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    int block_size = atoi(argv[1]);
    int max_elements_by_queue = atoi(argv[2]);
    int number_of_threads = atoi(argv[3]);
    const char *in_file_name = argv[4];
    const char *out_file_name = argv[5];
    try {
        InputStream input_stream(in_file_name, block_size);
        OutputStream output_stream(out_file_name);
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
    }
    catch (const std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
