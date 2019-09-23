#ifndef _BLOCKPROCESS_H_
#define _BLOCKPROCESS_H_
#include "Thread.h"
#include "Block.h"
#include "BlockProcessMonitor.h"
#include "OutputStream.h"
#include "ThreadSafeQueue.h"

class BlockProducerThread : public Thread {
 private:
  BlockProcessMonitor &block_process_monitor;
  int block_size;
  int number_of_blocks;
  int th_number;
  int number_of_threads;
  ThreadSafeQueue *thread_safe_queue;

 public:
  BlockProducerThread(BlockProcessMonitor &block_process_monitor,
                      int block_size,
                      int number_of_blocks,
                      int th_number,
                      int number_of_threads,
                      ThreadSafeQueue *thread_safe_queue);
  virtual void run() override;
  virtual ~BlockProducerThread() override;
};

#endif
