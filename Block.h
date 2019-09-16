#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <list>
#include "InputStream.h"

class Block {
 private:
  int size;
  unsigned int *numbers;
  unsigned int reference;
  std::list<int> list_int;

 public:
  Block(int size);
  // TODO: OJO ESTE SETNUMBERS; VERIFICAR QUE PASA CUANDO NO LEE NADA
  void setNumbers(InputStream &input_stream);
  // TODO: VER SI ESTO ES NECESARIO SEPARARLO O SE HACE EN EL CONSTRUCTOR
  void setReference();
  unsigned int getReference() const;
  // TODO: DEBERIA HABER UN NUEVO BLOQUE PARA ESTO??
  void numbersDifference();
  unsigned int getMaxBitSize();
  // TODO: DEBERIA SER PRIVADO??
  unsigned int getMax();
  unsigned int getNumber(int pos) const;
  void addList(int value);
  std::list<int> getList() const;
  ~Block();
};

#endif
