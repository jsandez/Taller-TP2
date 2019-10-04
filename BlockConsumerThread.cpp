#include "BlockConsumerThread.h"
#include <vector>

BlockConsumerThread::BlockConsumerThread
                                        (std::vector<ThreadSafeQueue *> queues,
                                         int number_of_blocks,
                                         OutputStream &output_stream)
    : queues(queues),
      number_of_blocks(number_of_blocks),
      output_stream(output_stream) {}

void BlockConsumerThread::run() {
  int number_of_queues = queues.size();
  for (int i = 0; i < number_of_blocks; i++) {
    Block block = queues[i % number_of_queues]->pop();
    output_stream.setReference(block.getReference());
    output_stream.setBitAmount(block.getBitSize());
    if (block.getBitSize() != 0) {
      output_stream.setBits(block.getList());
    }
  }
}
