#include "hwlib.hpp"
#include "note_player_print.hpp"

void note_player_print::play( const note & n ){
   	if( n.frequency == 0 ){
      	hwlib::wait_us( n.duration );
   	}else {
        hwlib::cout << "\nHz:" << n.frequency << " Duration:" << n.duration;
        hwlib::wait_us( n.duration );
   	}     
}