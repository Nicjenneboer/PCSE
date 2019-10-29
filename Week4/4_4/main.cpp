#include <fstream>
#include "hwlib.hpp"

extern "C" void decompressor();

extern "C" void cout_char( char c ){
   hwlib::cout << c ;
}

int main( void ){	
  
   hwlib::wait_ms(500);

   decompressor();
   hwlib::cout << "\nexit";

}