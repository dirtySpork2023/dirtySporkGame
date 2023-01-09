#ifndef BULLET_HPP
#define BULLET_HPP

struct node {
	double x ;
	double y ;
	double speed ;
	node* next ;
};

class bullet {
protected:
	node* head ; //lista di proiettili
	node* tail ; //proiettile più recente
	int num ; //numero di proiettili
	char texture ;
	void remove() ;

public:
	bullet();
	void add(int x, int y, double speed );
	void update(long int deltaTime);
	void print();
};

#endif //BULLET_HPP