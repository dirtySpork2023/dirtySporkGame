struct list {
	double x ;
	double y ;
	double speed ;
	list* next ;
};


class bullet {
protected:
	list* head ; //lista di proiettili

public:
	bullet();
	void add(double x, double y, double speed );
	void remove();
	void update(long int deltaTime);
};
