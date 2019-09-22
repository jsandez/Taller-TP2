#ifndef _THREADSAFEQUEUE_H_
#define _THREADSAFEQUEUE_H_
#include <queue>
#include <mutex>
#include "Block.h"

class ThreadSafeQueue {
 private:
  std::queue<Block> queue;
  int size;
  mutable std::mutex m;

 public:
  ThreadSafeQueue(int size);
  void push(Block &block);
  Block &pop();
  ~ThreadSafeQueue();
};

#endif
