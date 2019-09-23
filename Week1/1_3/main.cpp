#include "hwlib.hpp"

extern "C" void print_asciz( const char * s );

extern "C" void uart_put_char( char c ){
   hwlib::cout << c;
}

extern "C" void convert_char( char c ){
	if(c>'A' && c<'Z'){
		uart_put_char(c+('a'-'A'));
	}else if(c>'a' && c<'z'){
		uart_put_char(c-('a'-'A'));
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