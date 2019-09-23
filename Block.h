#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <list>
#include <vector>

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
  std::vector<unsigned int> numbers;
  unsigned int reference;
  unsigned int bit_size;
  std::list<int> list_int;
  unsigned int __getMax();
  void __setReference();
  void __setMaxBitSize();
  void __fillList();

 public:
  explicit Block(int size);
  void addNumber(unsigned int index, unsigned int number);
  void process();
  unsigned int getReference() const;
  unsigned int getBitSize() const;
  int getSize() const;
  std::list<int> getList() const;
  unsigned int getNumber(unsigned int index);
  Block(const Block &other) = delete;
  Block& operator=(const Block &other) = delete;
  Block(Block&& other);
  Block & operator=(Block&& other);
  ~Block();
};

#endif
