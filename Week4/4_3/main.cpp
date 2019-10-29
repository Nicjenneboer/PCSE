#include <iostream>
#include <fstream>

#include "compressor.hpp"

int main( void ){	
   lz_compressor< 4096 > compressor;
 
   std::ifstream f1;
   f1.open( "wilhelmus.txt" );
   if( ! f1.is_open()){
      std::cerr << "input file not opened";
      return -1;      
   }
   
   std::ofstream f2;
   f2.open( "compressed.asm" );
   if( ! f2.is_open()){
      std::cerr << "output file not opened";
      return -1;      
   }else{
      f2 << ".cpu cortex-m0\n"
         << ".data\n"
         << ".align 4\n"
         << ".global COMPRESSED_TEXT"
         << "COMPRESSED_TEXT:\n\t"
         << ".asciz \"";
   }
   
   compressor.compress( 
      [ &f1 ]()-> int { auto c = f1.get(); return f1.eof() ? '\0' : c; },
      [ &f2 ]( char c ){ f2.put( c ); }
  );
   
   f2 << "\"";

   f1.close();
   f2.close();
}