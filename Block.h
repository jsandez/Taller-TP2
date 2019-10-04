#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <list>
#include <vector>

/*
 * Clase que representa un bloque que sera extraido del stream
 * y procesado
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
  /*
   * Metodos privados para su uso interno
   */
  unsigned int __getMax();
  void __setReference();
  void __setMaxBitSize();
  void __fillList();

 public:
  /*
   * Construye un bloque con una cantidad de numeros
   * limitada por size
   */
  explicit Block(int size);

  /*
   * Agrega un numero al bloque en la posicion de index
   */
  void addNumber(unsigned int index, unsigned int number);

  /*
   * Procesa al bloque, esto es, busca la referencia,
   * hace la resta sobre todos los elementos del vector,
   * busca el menor, se fija la cantidad de bits que necesita
   * para procesarlo y pasa toda la el bloque a bits
   */
  void process();

  /*
   * Getters para su uso tanto en el stream de escritura como
   * para obtener el tamaño del bloque
   */
  unsigned int getReference() const;
  unsigned int getBitSize() const;
  int getSize() const;
  std::list<int> getList() const;
  unsigned int getNumber(unsigned int index) const;

  /*
   * Constructor y asignacion por copia eliminada.
   * Se reemplaza con move semantics
   */
  Block(const Block &other) = delete;
  Block& operator=(const Block &other) = delete;
  Block(Block&& other);
  Block & operator=(Block&& other);
  ~Block();
};

#endif
