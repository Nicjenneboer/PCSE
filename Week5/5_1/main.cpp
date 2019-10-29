#include "ostream"
#include <array>

#define CATCH_CONFIG_MAIN  
#include "catch.hpp"

class set{
private:
	const static int set_size = 10;
	std::array< int, set_size > data;
	int used;

public:
	set():
	used( 0 ){}

	void add( const int & x ){
		if( !contains( x ) ){
			if(used < set_size){
				data[used] = x;
				used++;
			}
		}
	}

	void remove( const int & x ){
		int tmp = 0;
		for(int i=0; i<used; i++){
			if( data[i] != x ){
				data[tmp] = data[i];
				tmp++;
			}
		}
		used = tmp;
	}

	bool contains( const int & x ){
		for(int i=0; i<used; i++){
			if( data[i] == x ){
				return true;
			}
		}
		return false;
	}

	friend std::ostream& operator<<(std::ostream & lhs, const set & rhs){
		lhs << "(" << rhs.data[0];
    	for(int i=1; i<rhs.used; i++){
    		lhs << "," << rhs.data[i];
    	}
    	lhs << ")";
	}

};

set list;

TEST_CASE( "add int to list" ){
	list.add(3);
	std::stringstream s;
	s << list;
	REQUIRE( s.str() == "(3)" );   
}


TEST_CASE( "add more int to list" ){
	list.add(1);
	list.add(9);
	list.add(7);
	std::stringstream s;
	s << list;
	REQUIRE( s.str() == "(3,1,9,7)" );   
}

TEST_CASE( "add same int" ){
	list.add(9);
	std::stringstream s;
	s << list;
	REQUIRE( s.str() == "(3,1,9,7)" );   
}

TEST_CASE( "contains int" ){
	REQUIRE( list.contains(7) == true );   
}

TEST_CASE( "contains int check" ){
	REQUIRE( list.contains(8) == false );   
}

TEST_CASE( "remove int" ){
	list.remove(9);
	std::stringstream s;
	s << list;
	REQUIRE( s.str() == "(3,1,7)" );   
}

TEST_CASE( "remove int not included" ){
	list.remove(4);
	std::stringstream s;
	s << list;
	REQUIRE( s.str() == "(3,1,7)" );   
}

TEST_CASE( "set 10 values in list" ){
	list.add(2);
	list.add(4);
	list.add(5);
	list.add(6);
	list.add(8);
	list.add(9);
	list.add(10);
	std::stringstream s;
	s << list;
	REQUIRE( s.str() == "(3,1,7,2,4,5,6,8,9,10)" );   
}

TEST_CASE( "add 11e int" ){
	list.add(12);
	std::stringstream s;
	s << list;
	REQUIRE( s.str() == "(3,1,7,2,4,5,6,8,9,10)" );   
}