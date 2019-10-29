HEADERS += note.hpp
HEADERS += note_player.hpp

HEADERS += melody.hpp
SOURCES += melody.cpp

HEADERS += note_player_gpio.hpp
SOURCES += note_player_gpio.cpp

run: melody.cpp

melody.cpp: melody.cpp generator
	./generator

generator: generator.o rtttl_player.o note_player_print.o
	g++ -std=c++17 generator.o rtttl_player.o note_player_print.o -o generator

generator.o: generator.cpp note_player_print.hpp rtttl_player.hpp
	g++ -std=c++17 -c generator.cpp -o generator.o

rtttl_player.o: rtttl_player.cpp rtttl_player.hpp note_player.hpp
	g++ -std=c++17 -c rtttl_player.cpp -o rtttl_player.o

note_player_print.o: note_player_print.cpp note_player_print.hpp note_player.hpp 
	g++ -std=c++17 -c note_player_print.cpp -o note_player_print.o


RELATIVE := $(RELATIVE)../../
include $(RELATIVE)Makefile.due
