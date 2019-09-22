#include "BlockProcess.h"
BlockProcess::BlockProcess(BlockProcessMonitor &block_process_monitor, int block_size, OutputStream &output_stream)
    : block_process_monitor(block_process_monitor), block_size(block_size), output_stream(output_stream) {}

void BlockProcess::run() {
  Block block(4);
  block_process_monitor.process(block);
  block.process();
  output_stream.setReference(block.getReference());
  output_stream.setBitAmount(block.getBitSize());
  if (block.getBitSize() != 0) {
    output_stream.setBits(block.getList());
  }
}
