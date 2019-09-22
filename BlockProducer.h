#ifndef _BLOCKPROCESS_H_
#define _BLOCKPROCESS_H_
#include "Thread.h"
#include "Block.h"
#include "BlockProcessMonitor.h"
#include "OutputStream.h"

class BlockProducer : public Thread {
 private:
  BlockProcessMonitor &block_process_monitor;
  int block_size;
  int number_of_blocks;
  int th_number;
  int number_of_threads;
  OutputStream &output_stream;

 public:
  BlockProducer(BlockProcessMonitor &block_process_monitor,
                int block_size,
                int number_of_blocks,
                int th_number,
                int number_of_threads,
                OutputStream &output_stream);
  virtual void run() override;
};

#endif
