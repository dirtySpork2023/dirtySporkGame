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


/*
Da migliorare :::

// Lista dei nemici presenti in un livello
struct enemy{
    entity* ent;
    char type;      // tipologia del nemico [k = kuba || s = shooter]
    enemy* next;
};

typedef enemy* lEnemies;
*/

struct Pplatform {
    platform* plat;
    Pplatform* next;
};
typedef Pplatform* lPlatform;

hitBox newRandomPlat (hitBox where);

lPlatform createnPlat (int np, hitBox ht, int len);

// Struct da restituire nella funzione check
struct infoCrash {
    char type;                // Tipo di oggetto con cui ci si scontra (p: platform || k: kuba || u: upgrades || n: nothing)
    int i;                    // Indice in cui è posizionato l'oggetto all'interno della sua lista
};

class level {
protected:
    int nlevel;                // Numero del livello
    lPlatform platforms;           // Lista delle piattaforme del livello
    //lEnemies enemies;            // Lista dei nemici del livello
    //level* next;               // livello successivo, il costruttore lo setta a NULL

public:
    level (int nl, bulletManager* bM);
    int givenplat();
    //void setNext(level* l);
    void print_platforms ();
    infoCrash check (hitBox ht, char d);  // d è la direzione in cui si sposta il giocatore:
    int number ();                       // a: sinistra || w: sopra || d: destra || s: sotto 
    // prova
    hitBox coordinate(int i);
};

#endif //LEVEL_HPP
