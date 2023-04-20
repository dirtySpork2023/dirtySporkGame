#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "lib.hpp"
#include "entity.hpp"
#include "platform.hpp"
#include "bulletManager.hpp"

// Lista delle piattaforme presenti in un livello
struct platforms{
    platform pl;
    platforms* next;
};

typedef platforms* lPlatforms; 

// Lista dei nemici presenti in un livello
struct enemy{
    entity ent;
    char type;      // tipologia del nemico [k = kuba || s = shooter]
    enemy* next;
};

typedef enemy* lEnemies;

// Struct da restituire nella funzione check
struct infoCrash {
    char type;                // Tipo di oggetto con cui ci si scontra (p: platform || k: kuba || u: upgrades || n: nothing)
    int i;                    // Indice in cui è posizionato l'oggetto all'interno della sua lista
}; 

class level {
    private:
    int nlevel;                // Numero del livello
    lPlatforms plat;           // Lista delle piattaforme del livello
    lEnemies enemies;            // Lista dei nemici del livello

    public:
    level (int nl, bulletManager bM);
    void print_platforms ();
    infoCrash check (hitBox ht, char d);  // d è la direzione in cui si sposta il giocatore:
    int lnumber ();                       // a: sinistra || w: sopra || d: destra || s: sotto 
};                                        

#endif //LEVEL_HPP
