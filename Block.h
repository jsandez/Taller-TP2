#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <list>
#include "InputStream.h"

/*
 * Clase que representa un bloque en el marco de referencia
 * Atributos:
 *            - size: cantidad de numeros que contiene el bloque.
 *            - numbers: numeros del bloque
 *            - reference: numero que sera utilizado como referencia
 *            - bit_size: cantidad de bits necesarios para representar al mayor numero
 *            - list_int: lista que contiene la representacion de los numeros
 *                        en la cantidad de bits correspondientes
 */

class Block {
 private:
  int size;
  unsigned int *numbers;
  unsigned int reference;
  unsigned int bit_size;
  std::list<int> list_int;
  /*
   * Metodos privados que se llamaran cuando se ejecuten los metodos publicos correspondientes.
   */
  unsigned int __getMax();
  void __setReference();
  void __setMaxBitSize();

 public:
  Block(int size);
  /*
   * Metodos publicos para manejar el ciclo de vida del bloque
   */
  void fillNumbers(InputStream &input_stream);
  void resizeNumbers();
  void fillList();

  /*
   * Getters correspondientes para escribir en el output stream
   */
  unsigned int getReference() const;
  unsigned int getBitSize() const;
  std::list<int> getList() const;

  ~Block();
};

#endif
