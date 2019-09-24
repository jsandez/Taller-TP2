#ifndef _BLOCKPROCESSOR_H_
#define _BLOCKPROCESSOR_H_
#include <mutex>
#include "Block.h"
#include "InputStream.h"
#include "OutputStream.h"

/*
 * Esta es la clase monitor que controla la
 * lectura del bloque en el InputStream
 * para que dos threads no puedan leer el mismo bloque
 * en el mismo momento
 */
class BlockProcessMonitor {
 private:
  InputStream &input_stream;
  std::mutex m;

 public:
  /*
   * Constructor que recibe un stream de entrada
   */
  explicit BlockProcessMonitor(InputStream &input_stream);

  /*
   * Operacion que tiene que ser lockeada para que
   * solo un thread pueda acceder a leer un bloque
   */
  void readBlock(Block &block, int block_number);
};

#endif
