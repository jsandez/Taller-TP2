#include <InputStream.h>
#include <Block.h>
#include <iostream>
#include "OutputStream.h"

int main(int argc, char **argv) {
    int block_size = atoi(argv[1]);
    int max_elements_by_queue = atoi(argv[2]);
    int number_of_threads = atoi(argv[3]);
    const char *in_file_name = argv[4];
    const char *out_file_name = argv[5];

    InputStream input_stream(in_file_name);
    if (input_stream.getFailBit()) {
        std::cout << "Error intentando abrir archivo de entrada" << std::endl;
        return 1;
    }
    OutputStream output_stream(out_file_name);
    if (output_stream.getFailBit()) {
        std::cout << "Error intentando abrir archivo de salida" << std::endl;
        return 1;
    }

    int size_file = input_stream.size();
    if (size_file == 0) {
        std::cout << "Empty File!!" << std::endl;
        return -1;
    }
    int cant_bloques = size_file / block_size;
    if (size_file % block_size != 0) {
        cant_bloques++;
    }

    for (int i = 0; i < cant_bloques; i++) {
        Block block(block_size);
        block.fillNumbers(input_stream);
        block.resizeNumbers();

        output_stream.setReference(block.getReference());
        output_stream.setBitAmount(block.getBitSize());
        if (block.getBitSize() != 0) {
            block.fillList();
            output_stream.setBits(block.getList());
        }
    }
    return 0;
}
