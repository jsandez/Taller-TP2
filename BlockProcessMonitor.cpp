#include "BlockProcessMonitor.h"
BlockProcessMonitor::BlockProcessMonitor(InputStream &input_stream)
    : input_stream(input_stream) {}

void BlockProcessMonitor::readBlock(Block &block, int block_number) {
  std::lock_guard<std::mutex> l(m);
  this->input_stream.fillBlock(block, block_number);
}
