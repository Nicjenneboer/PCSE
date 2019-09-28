#include "note_player_print.hpp"
#include <fstream>

void note_player_print::play( const note & n ){
	melody << "\tp.play( note{ " << n.frequency << ", " << n.duration << " } );\n";   
}