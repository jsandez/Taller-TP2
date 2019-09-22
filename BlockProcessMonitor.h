#ifndef _BLOCKPROCESSOR_H_
#define _BLOCKPROCESSOR_H_
#include <mutex>
#include "Block.h"
#include "InputStream.h"

/*
 * Esta es la clase monitor que controla la
 * lectura del bloque desde el InputStream
 */
class BlockProcessMonitor{
 private:
  InputStream &input_stream;
  std::mutex m;

 public:
  explicit BlockProcessMonitor(InputStream &input_stream);
  void process(Block &block);
};

#endif
