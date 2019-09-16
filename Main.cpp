#include <iostream>
#include <iomanip>
#include <list>
#include <InputStream.h>
#include <netinet/in.h>
#include <bitset>
#include <fstream>
#include <cstring>
#include <Block.h>
#include <Bits.h>

int main() {
  // CARGO EL ARCHIVO Y OBTENGO NUMEROS DE 4 BYTES SIN SIGNO Y ENDIAN DE LA MAQUINA
  // ACORDARSE QUE CADA BLOQUE MIDE 4 EN ESTE CASO NADA MAS
  InputStream file("oneblk");

  Block block(4);
  block.setNumbers(file);
  std::cout << "size " << file.size() << std::endl;

  // BUSCO EL MINIMO DE LOS VALORES, ES DECIR LA REFERENCIA
  // TODO: REVISAR IMPLEMENTACION; TAL VEZ SE PUEDE HACER MAS EFICIENTE
  block.setReference();
  unsigned int reference = block.getReference();

  block.numbersDifference();

  // TODO: DEBERIA ARMAR UNA NUEVA CLASE PARA ESTO??
  // TODO: DE MOMENTO LO DEJO EN BLOCK
  unsigned int max_bit_size = block.getMaxBitSize();

  std::list<int> list_bits;
  for (int i = 0; i < 4; i++) {
    Bits bit_representation(max_bit_size);
    bit_representation.represent(block.getNumber(i));
    for (int i = max_bit_size - 1; i >= 0; i--) {
      block.addList(bit_representation.get(i));
    }
  }

  // TODO: ESTO ES OUTPUTSTREAM
  std::bitset<8> bit_set;
  std::ofstream os("myfile", std::ofstream::binary);

  int jota = 7;
  for (int entero : block.getList()) {
    bit_set[jota] = entero;
    jota--;
  }

  char arr_ref[4];
  unsigned int referenceOut = htonl(reference);
  memcpy(arr_ref, &referenceOut, 4);

  os << arr_ref[0];
  os << arr_ref[1];
  os << arr_ref[2];
  os << arr_ref[3];
  os << (char) max_bit_size;
  os << (char) bit_set.to_ulong();
  os.close();

  char byte;
  byte = (char) bit_set.to_ulong();
  std::cout << "bit_set_size:  " << bit_set.size() << std::endl;
  std::cout << "As byte:  " << bit_set << std::endl;
  std::cout << "Division " << 4 / 8 << std::endl;
  std::cout << "Resto " << 4 % 8 << std::endl;
  std::cout << max_bit_size << std::endl;
  return 0;
}
