#include "ostream"
#include <array>

#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
template< typename T, int N >
class set{
private:
	std::array< T, N > data;
	int used;

public:
	set():
	used( 0 ){}

	void add( const T & x ){
		if( !contains( x ) ){
			if(used < N ){
				data[used] = x;
				used++;
			}
		}
	}

	void remove( const T & x ){
		int tmp = 0;
		for(int i=0; i<used; i++){
			if( data[i] != x ){
				data[tmp] = data[i];
				tmp++;
			}
		}
		used = tmp;
	}

	bool contains( const T & x ){
		for(int i=0; i<used; i++){
			if( data[i] == x ){
				return true;
			}
		}
		return false;
	}

	T max(){
		T tmp = data[0];
		for(int i=1; i<used; i++){
			if( data[i] > tmp ){
				tmp = data[i];
			}
		}
		return tmp;
	}

};



set< int, 10 > list_i;

TEST_CASE( "find max int" ){
	list_i.add(1);
	list_i.add(2);
	list_i.add(9);
	list_i.add(4);
	list_i.add(5);
	list_i.add(3);
	std::stringstream s;
	s << list_i;
	REQUIRE( list_i.max() == 9 );   
}



set< char, 7 > list_n;

TEST_CASE( "find max char" ){
	list_n.add('b');
	list_n.add('l');
	list_n.add('e');
	list_n.add('a');
	std::stringstream s;
	s << list_n;
	REQUIRE( list_n.max() == 'l' );   
}
