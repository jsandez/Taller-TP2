#ifndef _FILE_H_
#define _FILE_H_
#include <cstdio>
#include <fstream>
#include <iostream>
#include "Block.h"

/*
 * Clase que representa un stream de
 * entrada
 */
class InputStream {
 protected:
  std::istream* is;
  int size;
  int number_of_blocks;
  int __getNumber();
  void __setNumberOfBlocks(int block_size);

 public:
  /*
   * Constructor que recibe el tipo de stream
   * y el tamaño de los bloques en los que debe
   * dividirse
   */
  explicit InputStream(std::istream* stream, int block_size);

  /*
   * Recibe un objeto bloque y lo completa
   * con el bloque correspondiente en la posicion
   * block_number
   */
  void fillBlock(Block &block, int block_number);

  /*
   * Devuelve la cantidad de de bloques que
   * contiene el stream
   */
  int getNumberOfBlocks() const;
  ~InputStream();
};

#endif
