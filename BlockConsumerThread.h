#ifndef _BLOCKCONSUMERTHREAD_H_
#define _BLOCKCONSUMERTHREAD_H_
#include "Thread.h"
#include "ThreadSafeQueue.h"
#include "OutputStream.h"
#include <vector>

class BlockConsumerThread : public Thread {
 private:
  std::vector<ThreadSafeQueue*> queues;
  int number_of_blocks;
  OutputStream &output_stream;
 public:
  BlockConsumerThread(std::vector<ThreadSafeQueue*> queues,
                      int number_of_blocks,
                      OutputStream &output_stream);
  virtual void run() override;
  virtual ~BlockConsumerThread() override;
};

#endif
