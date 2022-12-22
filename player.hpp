
struct point {
	int x ;
	int y ;
};

struct hitBox {
	point a ; // top left
	point b ; // bottom right
};

class player{
public:
	point pos ; // relativa alla casella centrale, torso
	double ySpeed ;
	double yMod ;
	hitBox box ;
	char texture[3][3] = {
			{' ','O',' '},
			{'/','W','\\'},
			{'/','"','\\'},
	};

public:
	player(int x, int y) ;
	void print() ;
	void move(char input) ;
};
