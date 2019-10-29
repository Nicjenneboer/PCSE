SOURCES := decompressor.asm compressed.asm 

compressed.asm: compressed.asm compressor
	./compressor

compressor: compressor.cpp match.hpp compressor.hpp wilhelmus.txt
	g++ -std=c++17 compressor.cpp -o compressor

RELATIVE := $(RELATIVE)../../
include $(RELATIVE)Makefile.due
