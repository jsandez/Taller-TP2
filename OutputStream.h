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
  std::ofstream ofs;

 public:
  /*
   * Constructor del stream que recibe
   * el nombre del archivo que se creara
   */
  explicit OutputStream(const char *name);

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
  void setBits(std::list<int> list);
  ~OutputStream();
};

#endif
