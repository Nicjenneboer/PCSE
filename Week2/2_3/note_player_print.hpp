#ifndef _NOTE_PLAYER_PRINT_HPP
#define _NOTE_PLAYER_PRINT_HPP

#include "note_player.hpp"

class note_player_print : public note_player {
public: 
   void play( const note & n ) override;
};

#endif
