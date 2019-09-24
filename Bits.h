#ifndef _BITARRAY_H_
#define _BITARRAY_H_

/*
 * Clase que representa un numero entero en binario
 * con una cantidad determinada de bits
 */
#include <vector>
class Bits {
 private:
  std::vector<int> data;

 public:
  /*
   * Constructor de Bits.
   * Recibe un tamanio que es la cantidad de bits
   * que se utilizaran para representar a un
   * numero
   */
  explicit Bits(int size);

  /*
   * Representa a un determinado numero entero y sin signo
   */
  void represent(unsigned int number);

  /*
   * Obtiene el bit en la posicion pos
   */
  bool get(int pos) const;
  ~Bits();
};

#endif
