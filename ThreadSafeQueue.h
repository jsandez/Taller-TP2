#ifndef _THREADSAFEQUEUE_H_
#define _THREADSAFEQUEUE_H_
#include <queue>
#include <mutex>
#include <condition_variable>

#include "Block.h"

class ThreadSafeQueue {
 private:
  std::queue<Block> queue;
  int size;
  std::mutex m;
  std::condition_variable cond;

 public:
  explicit ThreadSafeQueue(int size);
  void push(Block &block);
  Block pop();
  ~ThreadSafeQueue();
};

#endif
