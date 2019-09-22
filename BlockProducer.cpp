#include "BlockProducer.h"
BlockProducer::BlockProducer(BlockProcessMonitor &block_process_monitor,
                             int block_size,
                             int number_of_blocks,
                             int th_number,
                             int number_of_threads,
                             OutputStream &output_stream)
    : block_process_monitor(block_process_monitor),
      block_size(block_size),
      number_of_blocks(number_of_blocks),
      th_number(th_number),
      number_of_threads(number_of_threads),
      output_stream(output_stream) {}

void BlockProducer::run() {
  for (int i = th_number; i < this->number_of_blocks; i = i + number_of_threads) {
    std::cout << "corrio " << th_number << "pidio " << i << std::endl;
    Block block(this->block_size);
    block_process_monitor.readBlock(block, i);
    block.process();
    output_stream.setReference(block.getReference());
    output_stream.setBitAmount(block.getBitSize());
    if (block.getBitSize() != 0) {
      output_stream.setBits(block.getList());
    }
  }
}
