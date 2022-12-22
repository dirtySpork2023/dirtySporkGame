
struct point {
	int x ;
	int y ;
};

struct hitBox {
	point NE ; //nord-est
	point SO ; //sud-ovest
};

class player{
public:
	point pos ;
	hitBox box ;
	int health ;
	char texture[3][3] = {
			{' ','O',' '},
			{'>','W','-'},
			{'/','"','|'},
	};

public:
	player(int x, int y) ;
	void print() ;
};
