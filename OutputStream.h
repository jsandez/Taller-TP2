#ifndef _OUTPUTFILE_H_
#define _OUTPUTFILE_H_
#include <stdio.h>
#include <fstream>
#include <list>

/*
 * Clase que representa un stream
 * de salida
 */
class OutputStream {
 private:
  std::ostream *os;

 public:
  /*
   * Constructor del stream que recibe
   * el tipo de stream en donde se enviaran
   * los numeros comprimidos
   */
  explicit OutputStream(std::ostream *ostream);

  /*
   * Escribe la referencia del bloque
   */
  void setReference(unsigned int reference);

  /*
   * Escribe la cantidad de bits que se
   * utilizan para reprsentar la maximo
   * valor
   */
  void setBitAmount(unsigned int c);

  /*
   * Escribe la lista de bits en el
   * stream de salida
   */
  void setBits(std::list<int> &list);
};

#endif
