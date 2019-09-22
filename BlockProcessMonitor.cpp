#include "BlockProcessMonitor.h"
BlockProcessMonitor::BlockProcessMonitor(InputStream &input_stream)
                                        : input_stream(input_stream) {}

void BlockProcessMonitor::process(Block &block) {
  std::lock_guard<std::mutex> l(m);
  this->input_stream.fillBlock(block);
}
