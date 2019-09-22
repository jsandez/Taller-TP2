cmake_minimum_required(VERSION 3.14)
project(Taller_TP2)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

include_directories(.)

add_executable(Taller_TP2
        Main.cpp Block.cpp Block.h InputStream.h Bits.cpp Bits.h OutputStream.cpp OutputStream.h InputFileStream.cpp InputFileStream.h InputStream.cpp Thread.cpp Thread.h BlockProcessMonitor.cpp BlockProcessMonitor.h BlockProducer.cpp BlockProducer.h ThreadSafeQueue.cpp ThreadSafeQueue.h)
