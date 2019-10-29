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

	friend bool operator>(const std::array< char, 3 > & lhs, const std::array< char, 3 > & rhs){
        char tmp_l=0;
        char tmp_r=0;
        for(char l : lhs ){
        	tmp_l += l;
        }
        for(char r : rhs ){
        	tmp_r += r;
        }
        return tmp_l > tmp_r;
    }

};



set< std::array< char, 3 >, 3 > list;

TEST_CASE( "find max array< char, 3 >" ){
	list.add(std::array< char, 3 > { 'a','h','z' });
	list.add(std::array< char, 3 > { 'q','u','i' });
	list.add(std::array< char, 3 > { 'b','f','e' });
	REQUIRE( list.max() == std::array< char, 3 > { 'q','u','i' } );   
}

TEST_CASE( "!1 find max array< char, 3 >" ){
	REQUIRE( list.max() != std::array< char, 3 > { 'a','h','z' } );   
}

TEST_CASE( "!2 find max array< char, 3 >" ){
	REQUIRE( list.max() != std::array< char, 3 > { 'b','f','e' } );   
}


