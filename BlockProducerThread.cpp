#include "BlockProducerThread.h"
BlockProducerThread::BlockProducerThread
                          (BlockProcessMonitor &block_process_monitor,
                          int block_size,
                          int number_of_blocks,
                          int th_number,
                          int number_of_threads,
                          ThreadSafeQueue *thread_safe_queue)
    : block_process_monitor(block_process_monitor),
      block_size(block_size),
      number_of_blocks(number_of_blocks),
      th_number(th_number),
      number_of_threads(number_of_threads),
      thread_safe_queue(thread_safe_queue) {}

void BlockProducerThread::run() {
  for (int i = th_number;
        i < this->number_of_blocks;
        i = i + number_of_threads) {
    Block block(this->block_size);
    block_process_monitor.readBlock(block, i);
    block.process();
    thread_safe_queue->push(block);
  }
}

BlockProducerThread::~BlockProducerThread() {
  delete thread_safe_queue;
}
