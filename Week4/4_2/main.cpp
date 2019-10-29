#include <iostream>
#include <fstream>

#include "compressor.hpp"
#include "decompressor.hpp"

int main( void ){	
   lz_compressor< 4096 > compressor;
 
   std::ifstream f1;
   f1.open( "wilhelmus.txt" );
   if( ! f1.is_open()){
      std::cerr << "input file not opened";
      return -1;      
   }
   
   std::ofstream f2;
   f2.open( "compressed.txt" );
   if( ! f2.is_open()){
      std::cerr << "output file not opened";
      return -1;      
   }
   
   compressor.compress( 
      [ &f1 ]()-> int { auto c = f1.get(); return f1.eof() ? '\0' : c; },
      [ &f2 ]( char c ){ f2.put( c ); } 
   );
   
   f1.close();
   f2.close();

   std::ifstream f3;
   f3.open( "compressed.txt" );
   if( ! f3.is_open()){
      std::cerr << "output file not opened";
      return -1;      
   }

   lz_decompressor decompressor;
   decompressor.decompress( 
      [ &f3 ]()-> int { auto c = f3.get(); return f3.eof() ? '\0' : c; },
      []( char c ){ std::cout << c; }
   );

   f3.close();

}