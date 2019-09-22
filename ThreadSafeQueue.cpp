#include "ThreadSafeQueue.h"

ThreadSafeQueue::ThreadSafeQueue(int size) : size(size) {}

void ThreadSafeQueue::push(Block &block) {
  this->queue.push(block);
}

Block &ThreadSafeQueue::pop() {
  Block block = this->queue.front();
  this->queue.pop();
  return block;
}

ThreadSafeQueue::~ThreadSafeQueue() {}