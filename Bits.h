#ifndef _BITARRAY_H_
#define _BITARRAY_H_

#include <vector>
class Bits {
 private:
  std::vector<int> data;

 public:
  Bits(int size);
  void represent(unsigned int number);
  bool get(int pos) const;
  ~Bits();
};

#endif
