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

lKuba dltKuba (lKuba lk);
lShooter dltShooter (lShooter ls);

void print_platforms (lPlatform lsp);       // Funzione stampa lista di piattaforme

// Struct da restituire nella funzione check
struct infoCrash {
    char type;                // Tipo di oggetto con cui ci si scontra (p: platform || k: kuba || u: upgrades || n: nothing)
    void* obj;                // Puntatore void all'oggetto
};

class level {
protected:
    int nlevel;                 // Numero del livello
    int diff;                   // Difficoltà
    lPlatform platforms;        // Lista delle piattaforme del livello
    lKuba kubas;                // Lista di kuba
    lShooter shooters;          // Lista di shooters
    yuck* Y;                    // Yuck è al massimo 1

public:
    level (int nl, int d, bulletManager* bM);
    void printAll (timeSpan deltaTime);
    infoCrash check (hitBox ht, char d);  // d è la direzione in cui si sposta il giocatore:
    int number ();                       // a: sinistra || w: sopra || d: destra || s: sotto 
    int getDiff ();
    void update (player P, timeSpan deltaTime);
};

#endif //LEVEL_HPP
