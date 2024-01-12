#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "lib.hpp"
#include "bulletManager.hpp"
#include "shooter.hpp"
#include "yuck.hpp"
#include "player.hpp"
#include "kuba.hpp"
#include "platform.hpp"
#include "coin.hpp"

struct Pplatform
{
    platform *plat;
    Pplatform *next;
};
typedef Pplatform *lPlatform;

struct Pkuba {
    kuba *K;
    Pkuba *next;
};
typedef Pkuba *lKuba;

struct Pshooter {
    shooter *S;
    Pshooter *next;
};
typedef Pshooter *lShooter;

struct Pcoin {
    coin* C;
    Pcoin* next;
};
typedef Pcoin* lCoin;

// Struct da restituire nella funzione check
struct infoCrash
{
    char type; // Tipo di oggetto con cui ci si scontra
    void *obj; // Puntatore void all'oggetto
};

class level {

protected:
    int nlevel;                 // Numero del livello
    int diff;                   // Difficoltà
    int numplat;
    bulletManager* B;
    lPlatform platforms;        // Lista delle piattaforme del livello
    lKuba kubas;                // Lista di kuba
    lShooter shooters;          // Lista di shooters
    yuck* Y;                    // Yuck è al massimo 1
    lCoin coins;

    hitBox newRandomPlat(hitBox where);
    lPlatform createnPlat(int np, hitBox p1, int len);
    lKuba dltKuba (lKuba lk, int* points);
    lShooter dltShooter (lShooter ls, int* points);
    lCoin dltCoin (lCoin lc, player* P, int* money, int* points);
    void print_platforms (lPlatform lsp);
    hitBox hiboxPlatx (lPlatform lp, int x); // hitbox della piattaforma x

public:
    level (int nl, int d);
    void printAll (timeSpan deltaTime);
    infoCrash check (hitBox ht, char d);  // d -> direzione in cui si sposta il giocatore (awsd)
    int number (); // numero del livello
    int getDiff (); // difficoltà del livello
    void update (player* P, timeSpan deltaTime, int* money, int* points);
    bool completed(); // true -> livello completato
    bulletManager* getBM ();
};

#endif // LEVEL_HPP