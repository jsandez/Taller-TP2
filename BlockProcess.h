#ifndef _BLOCKPROCESS_H_
#define _BLOCKPROCESS_H_
#include "Thread.h"
#include "Block.h"
#include "BlockProcessMonitor.h"
#include "OutputStream.h"

class BlockProcess : public Thread {
 private:
  BlockProcessMonitor &block_process_monitor;
  int block_size;
  OutputStream &output_stream;

 public:
  BlockProcess(BlockProcessMonitor &block_process_monitor, int block_size, OutputStream &output_stream);
  virtual void run() override;
};

#endif
