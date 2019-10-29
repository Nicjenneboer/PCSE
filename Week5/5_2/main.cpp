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

	friend std::ostream& operator<<(std::ostream & lhs, const set & rhs){
		lhs << "(" << rhs.data[0];
    	for(int i=1; i<rhs.used; i++){
    		lhs << "," << rhs.data[i];
    	}
    	lhs << ")";
	}

};

// TEST LIST WITH INT 10

set< int, 10 > list_i;

TEST_CASE( "add int to list" ){
	list_i.add(3);
	std::stringstream s;
	s << list_i;
	REQUIRE( s.str() == "(3)" );   
}


TEST_CASE( "add more int to list" ){
	list_i.add(1);
	list_i.add(9);
	list_i.add(7);
	std::stringstream s;
	s << list_i;
	REQUIRE( s.str() == "(3,1,9,7)" );   
}

TEST_CASE( "add same int" ){
	list_i.add(9);
	std::stringstream s;
	s << list_i;
	REQUIRE( s.str() == "(3,1,9,7)" );   
}

TEST_CASE( "contains int" ){
	REQUIRE( list_i.contains(7) == true );   
}

TEST_CASE( "contains int check" ){
	REQUIRE( list_i.contains(8) == false );   
}

TEST_CASE( "remove int" ){
	list_i.remove(9);
	std::stringstream s;
	s << list_i;
	REQUIRE( s.str() == "(3,1,7)" );   
}

TEST_CASE( "remove int not included" ){
	list_i.remove(4);
	std::stringstream s;
	s << list_i;
	REQUIRE( s.str() == "(3,1,7)" );   
}

TEST_CASE( "set 10 int values in list" ){
	list_i.add(2);
	list_i.add(4);
	list_i.add(5);
	list_i.add(6);
	list_i.add(8);
	list_i.add(9);
	list_i.add(10);
	std::stringstream s;
	s << list_i;
	REQUIRE( s.str() == "(3,1,7,2,4,5,6,8,9,10)" );   
}

TEST_CASE( "add 11e int" ){
	list_i.add(12);
	std::stringstream s;
	s << list_i;
	REQUIRE( s.str() == "(3,1,7,2,4,5,6,8,9,10)" );   
}

// TEST LIST WITH CHAR 7

set< char, 7 > list_n;

TEST_CASE( "add char to list" ){
	list_n.add('c');
	std::stringstream s;
	s << list_n;
	REQUIRE( s.str() == "(c)" );   
}


TEST_CASE( "add more char to list" ){
	list_n.add('a');
	list_n.add('i');
	list_n.add('g');
	std::stringstream s;
	s << list_n;
	REQUIRE( s.str() == "(c,a,i,g)" );   
}

TEST_CASE( "add same char" ){
	list_n.add('i');
	std::stringstream s;
	s << list_n;
	REQUIRE( s.str() == "(c,a,i,g)" );   
}

TEST_CASE( "contains char" ){
	REQUIRE( list_n.contains('g') == true );   
}

TEST_CASE( "contains char check" ){
	REQUIRE( list_n.contains('b') == false );   
}

TEST_CASE( "remove char" ){
	list_n.remove('i');
	std::stringstream s;
	s << list_n;
	REQUIRE( s.str() == "(c,a,g)" );   
}

TEST_CASE( "remove char not included" ){
	list_n.remove('d');
	std::stringstream s;
	s << list_n;
	REQUIRE( s.str() == "(c,a,g)" );   
}

TEST_CASE( "set N = (7) char values in list" ){
	list_n.add('b');
	list_n.add('d');
	list_n.add('e');
	list_n.add('f');
	std::stringstream s;
	s << list_n;
	REQUIRE( s.str() == "(c,a,g,b,d,e,f)" );   
}

TEST_CASE( "add 8e char" ){
	list_n.add(12);
	std::stringstream s;
	s << list_n;
	REQUIRE( s.str() == "(c,a,g,b,d,e,f)" );   
}
