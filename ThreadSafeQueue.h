#ifndef _THREADSAFEQUEUE_H_
#define _THREADSAFEQUEUE_H_
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Block.h"

/*
 * Cola thread safe, para escribir
 * de forma ordenada los bloques
 * en el output de salida
 */
class ThreadSafeQueue {
 private:
  std::queue<Block> queue;
  int size;
  std::mutex m;
  std::condition_variable cond;

 public:
  /*
   * Constructor que recibe
   * el tamaño de la cola
   */
  explicit ThreadSafeQueue(int size);

  /*
   * Operacion push thread-safe.
   * Si esta llena, espera a que
   * se vacie con un pop para poder
   * hacer el push
   */
  void push(Block &block);

  /*
   * Hace el pop en la cola,
   * si esta vacia espera a que
   * se realice un push para luego
   * poder realizar el pop
   */
  Block pop();
  ~ThreadSafeQueue();
};

#endif
