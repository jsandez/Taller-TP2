#ifndef _BLOCKCONSUMERTHREAD_H_
#define _BLOCKCONSUMERTHREAD_H_
#include "Thread.h"
#include "ThreadSafeQueue.h"
#include "OutputStream.h"
#include <vector>

/*
 * Thread que consumira de la cola de forma
 * ordenada para luego
 * escribir en el archivo de salida.
 */
class BlockConsumerThread : public Thread {
 private:
  std::vector<ThreadSafeQueue *> queues;
  int number_of_blocks;
  OutputStream &output_stream;

 public:
  /*
   * Constructor del thread consumidor.
   * Recibe un vector de colas, el numero
   * de bloques correspondientes y el stream
   * de salida
   */
  BlockConsumerThread(std::vector<ThreadSafeQueue *> queues,
                      int number_of_blocks,
                      OutputStream &output_stream);

  /*
   * Corre el thread
   */
  virtual void run() override;

  virtual ~BlockConsumerThread() override;
};

#endif
