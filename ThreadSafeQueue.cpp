#include "ThreadSafeQueue.h"

ThreadSafeQueue::ThreadSafeQueue(int size) : size(size) {}

void ThreadSafeQueue::push(Block &block) {
  std::unique_lock<std::mutex> lock(m);
  while (this->queue.size() == (unsigned int) this->size) {
    cond.wait(lock);
  }
  this->queue.push(std::move(block));
  lock.unlock();
  cond.notify_all();
}

Block ThreadSafeQueue::pop() {
  std::unique_lock<std::mutex> lock(m);
  while (this->queue.empty()) {
    cond.wait(lock);
  }
  Block block = std::move(this->queue.front());
  this->queue.pop();
  lock.unlock();
  cond.notify_all();
  return block;
}

ThreadSafeQueue::~ThreadSafeQueue() {}
