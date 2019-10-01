#include "hwlib.hpp"
#include <array>

template< typename T, int N >
class create_table {
private:
	std::array< T, N > values = {};

public:
	template< typename F >
	constexpr create_table( F function ){
		for( int i=0; i < N; i++ ){
			values[ i ] = function( i );
		}
	}

	constexpr T get( double n ) const {
		return values[ n ];
	}
};

constexpr double pi(){
	double result = 3;
	for(int i=2; i<=1000; i+=2){
		if(i%4==0){
			result -= 4./(i*(i+1)*(i+2));
		}else{
			result += 4./(i*(i+1)*(i+2));
		}
	}
	return result;
}

constexpr double convert(int deg){
	return double(deg) * (pi() / 180);
}

constexpr double factorial(double x){
	if(x>0){
		return x*factorial(x-1);
	}else{
		return 1;
	}
}

constexpr double exponent(double x, int y){
	if(y>0){
		return x*exponent(x, y-1);
	}else{
		return 1;
	}
}

constexpr double sin(double x){
	double result = 0;
	for(int i=0; i<80; i++){
		if(i%2==0){
			result += 1/factorial(i*2+1)*exponent(convert(x), i*2+1);
		}else{
			result -= (1/factorial(i*2+1))*exponent(convert(x), i*2+1);
		}
	}
	return result;
}

// constexpr double cos(double x){
// 	double result = 1;
// 	for(int i=1; i<25; i++){
// 		if(i%2==1){
// 			result -= 1/factorial(i*2)*exponent(convert(x), i*2);
// 		}else{
// 			result += (1/factorial(i*2))*exponent(convert(x), i*2);
// 		}
// 	}
// 	return result;
// }

constexpr auto t_sin = create_table< double, 360>( sin );

hwlib::xy circle_xy(hwlib::xy pos, int deg, int radius){
	return hwlib::xy(t_sin.get(deg)*radius+pos.x, t_sin.get((deg+90)%360)*-radius+pos.y);
}

std::array< char, 2 > int_to_char_array(const int & number){
	std::array< char, 2 > result;
	result[0] = (number % 10) + 0x30;
	result[1] = (number / 10) + 0x30;
	return result;
}

class timer{
public:

	long unsigned int time;
	int sec = 0;
	int min = 0;
	int hour = 0;
	int a_sec = 0;

	void update_time(int n_sec=0){
		a_sec+=n_sec%86400;
		time = ((hwlib::now_us()/1000000)+a_sec)%86400;
		sec = time%60;
		min = (time/60)%60;
		hour = (time/3600)%24;
	}
};

class drawable {
protected:
	hwlib::glcd_oled & display;
	hwlib::xy pos;

public:
	drawable( hwlib::glcd_oled & display, const hwlib::xy & pos):
		display( display ),
		pos( pos )
	{}

	virtual void draw() = 0;
	virtual void update(){}
};

class clock_face : public drawable{
private:
	int radius;
public:
	clock_face( hwlib::glcd_oled & display, const hwlib::xy & pos,const int & radius ):
		drawable( display, pos ),
		radius( radius )
	{}

	void draw() override{
		for(int i=0; i<12; i++){
			for(int j=0; j<4; j++){
				hwlib::circle c( circle_xy( pos, i*30, radius), j );
				c.draw( display );
			}
		}
		hwlib::circle c( pos , 2 );
		c.draw( display );
	}
};

class line : public drawable {
private:
	int radius;

public:
	int deg = 0;

	line( hwlib::glcd_oled & display, const hwlib::xy & pos, const int & radius):
		drawable( display, pos ),
		radius( radius )
	{}

	void draw() {
		hwlib::line l(pos, circle_xy(pos, deg, radius));
		l.draw( display );
	}
};

class clock_hands : public drawable{
private:
	line h_sec;
	line h_min;
	line h_hour;
	timer & time;

public:
	clock_hands( hwlib::glcd_oled & display, const hwlib::xy & pos, const int & radius, timer & time ):
		drawable( display, pos),
		h_sec( display, pos, radius ),
		h_min( display, pos, radius-7 ),
		h_hour( display, pos, radius-13 ),
		time( time )
	{}

	void draw() override{
		h_sec.draw();
		h_min.draw();
		h_hour.draw();
	}

	void update(){
		time.update_time();
		h_sec.deg=time.sec*6;
		h_min.deg=time.min*6;
		h_hour.deg=int((time.hour*30)+time.min*0.5)%360;
	}
};



class digital_clock : public drawable{
private:
	timer & time;

public:
	digital_clock( hwlib::glcd_oled & display, const hwlib::xy & pos, timer & time ):
		drawable( display, pos ),
		time( time )
	{}

	void draw() override{
		time.update_time();

		auto font = hwlib::font_default_8x8();

		std::array< char, 2 > f_min = int_to_char_array(time.min);
		std::array< char, 2 > f_hour = int_to_char_array(int(time.hour));

		display.write(hwlib::xy(pos.x-14, pos.y), hwlib::image_invert_t(font[':']));

		for(int i=0; i<2; i++){
			display.write(hwlib::xy(pos.x-i*8, pos.y),  hwlib::image_invert_t(font[f_min[i]]));
		}
		for(int i=0; i<2; i++){
			display.write(hwlib::xy(pos.x-20-i*8, pos.y),  hwlib::image_invert_t(font[f_hour[i]]));
		}
	}

	void update(){
		time.update_time();
	}
};


int main( void ){

    hwlib::wait_ms(100);

   	auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
   	auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
   	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   	auto display = hwlib::glcd_oled( i2c_bus, 0x3c );  

   	display.clear();

   	hwlib::xy midpoint(64, 32);

   	timer time = timer();

   	auto b_min = hwlib::target::pin_in(hwlib::target::pins::d2);
   	auto b_hour = hwlib::target::pin_in(hwlib::target::pins::d3);

   	auto clock_f = clock_face(display, midpoint, 29);
	auto clock_h = clock_hands(display, midpoint, 28, time);
	auto clock_d = digital_clock(display, hwlib::xy(120,0), time);

	std::array< drawable*, 3 > clock = { &clock_f, &clock_h, &clock_d };

	for(;;){
		display.clear();
		for(auto c : clock){
			c->draw();
			c->update();
		}
		display.flush();
		if(b_min.read()==0){
			time.update_time(60);
		}if(b_hour.read()==0){
			time.update_time(3600);
		}
   }
}
