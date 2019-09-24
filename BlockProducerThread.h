#ifndef _BLOCKPROCESS_H_
#define _BLOCKPROCESS_H_
#include "Thread.h"
#include "Block.h"
#include "BlockProcessMonitor.h"
#include "OutputStream.h"
#include "ThreadSafeQueue.h"

/*
 * Thread que producira los bloques en la
 * cola que luego deben ser consumidos por
 * el thread consumidor.
 */
class BlockProducerThread : public Thread {
 private:
  BlockProcessMonitor &block_process_monitor;
  int block_size;
  int number_of_blocks;
  int th_number;
  int number_of_threads;
  ThreadSafeQueue *thread_safe_queue;

 public:
  /*
   * Constructor del thread que recibe
   * un objeto monitor que regulara el acceso al
   * archivo de entrada, el tamaño del bloque,
   * el numero de bloques, el numero de thread,
   * la cantidad de threads y una cola thread safe
   */
  BlockProducerThread(BlockProcessMonitor &block_process_monitor,
                      int block_size,
                      int number_of_blocks,
                      int th_number,
                      int number_of_threads,
                      ThreadSafeQueue *thread_safe_queue);

  /*
   * Operacion que corre el thread
   */
  virtual void run() override;
  virtual ~BlockProducerThread() override;
};

#endif
