#include "hwlib.hpp"

extern "C" void print_asciz( const char * s );

extern "C" void uart_put_char( char c ){
   hwlib::cout << c;
}

extern "C" void convert_char( char c ){
	if(c>64 && c<91){
		uart_put_char( c+32 );
	}else if(c>96 && c<123){
		uart_put_char( c-32 );
	}else{
		uart_put_char( c );
	}
}

extern "C" void application( const char * s );

int main( void ){	
   namespace target = hwlib::target;   
    
      // wait for the PC console to start
   hwlib::wait_ms( 2000 );

   application( "Hello world, the ANSWER is 42! @[]`{}~\n");
}