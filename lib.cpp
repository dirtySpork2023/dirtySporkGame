#ifndef LIB_CPP
#define LIB_CPP

#include "lib.hpp"

bool collisionHH(hitBox B, hitBox T){
	// estremamente inefficiente, ma sicuro funziona
	// per ogni punto della hitbox T-iny, controllo se collide con la hitbox B-ig
	bool found = false ;
	int x = T.a.x ;
	int y = T.a.y ;
	while( x<=T.b.x && !found ){
		while( y<=T.b.y && !found ){
			point tmp ;
			tmp.x = x ;
			tmp.y = y ;
			if( collisionHP(B, tmp) )
				found = true ;
			y++ ;
		}
		x++ ;
	}
	return found ;
}

bool collisionHP(hitBox box, point p){
	if( (box.a.x < p.x && p.x < box.b.x) &&
		(box.a.y < p.y && p.y < box.b.y) )
		return true ;
	else
		return false ;
}

bool collisionHV(hitBox box, vector p){
	if( (box.a.x < p.x && p.x < box.b.x) &&
		(box.a.y < p.y && p.y < box.b.y) )
		return true ;
	else
		return false ;
}

bool collisionPP(point A, point B){
	if( A.x==B.x && A.y==B.y ) return true ;
	else return false ;
}

#endif //LIB_CPP