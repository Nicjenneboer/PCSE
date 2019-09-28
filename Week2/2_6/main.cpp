#include "hwlib.hpp"
#include "note_player_gpio.hpp"
#include "melody.hpp"
#include "rtttl_player.hpp"

int main( void ){	
   
   namespace target = hwlib::target;   
   auto lsp = target::pin_out( target::pins::d7 );
   auto p = note_player_gpio( lsp );
   hwlib::wait_ms( 10 );
   
   HWLIB_TRACE;
   
   auto fe = melody();
   fe.play( p );

}
