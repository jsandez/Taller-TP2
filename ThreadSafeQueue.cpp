#include "ThreadSafeQueue.h"

ThreadSafeQueue::ThreadSafeQueue(int size) : size(size) {}

void ThreadSafeQueue::push(Block &block) {
  std::unique_lock<std::mutex> lock(m);
  while (this->queue.size() == (unsigned int) this->size) {
    cond_push.wait(lock);
  }
  this->queue.push(std::move(block));
  lock.unlock();
  cond_pop.notify_all();
}

Block ThreadSafeQueue::pop() {
  std::unique_lock<std::mutex> lock(m);
  while (this->queue.empty()) {
    cond_pop.wait(lock);
  }
  Block block = std::move(this->queue.front());
  this->queue.pop();
  lock.unlock();
  cond_push.notify_all();
  return block;
}
