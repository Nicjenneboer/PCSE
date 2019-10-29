#include "hwlib.hpp"

extern "C" void cout_char( char c ){
      hwlib::cout << c;
   }

extern "C" void decompressor();

int main(){
	hwlib::wait_ms(100);
	decompressor();
}