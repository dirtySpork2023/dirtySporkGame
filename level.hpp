#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "lib.hpp"
#include "bulletManager.hpp"
#include "entity.hpp"
#include "shooter.hpp"
#include "yuck.hpp"
#include "player.hpp"
#include "kuba.hpp"
#include "platform.hpp"


struct Pplatform {
    platform* plat;
    Pplatform* next;
};
typedef Pplatform* lPlatform;

hitBox newRandomPlat (hitBox where, int de);

lPlatform createnPlat (int np, hitBox ht, int len, int d);

struct Pkuba {
    kuba* K;
    Pkuba* next;
};
typedef Pkuba* lKuba;

struct Pshooter {
    shooter* S;
    Pshooter* next;
};
typedef Pshooter* lShooter;


// Struct da restituire nella funzione check
struct infoCrash {
    char type;                // Tipo di oggetto con cui ci si scontra (p: platform || k: kuba || u: upgrades || n: nothing)
    int i;                    // Indice in cui è posizionato l'oggetto all'interno della sua lista
};

class level {
protected:
    int nlevel;                 // Numero del livello
    int diff;                   // Difficoltà
    lPlatform platforms;        // Lista delle piattaforme del livello
    lKuba kubas;                // Lista di kuba
    lShooter shooters;          // Lista di shooters

public:
    level (int nl, int d, bulletManager* bM);
    int givenplat();
    void print_platforms ();
    infoCrash check (hitBox ht, char d);  // d è la direzione in cui si sposta il giocatore:
    int number ();                       // a: sinistra || w: sopra || d: destra || s: sotto 
    int givediff ();
    hitBox coordinate(int i);
};

#endif //LEVEL_HPP
