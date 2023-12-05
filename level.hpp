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

struct node{
    void* obj;
    char type;
    node* next;
};

struct Pplatform
{
    platform *plat;
    Pplatform *next;
};
typedef Pplatform *lPlatform;

hitBox newRandomPlat(hitBox where, int de);

lPlatform createnPlat(int np, hitBox ht, int len, int d);

lCoin dltCoin (lCoin lc, player* P, int* money);

void print_platforms (lPlatform lsp);       // Funzione stampa lista di piattaforme
hitBox hiboxPlatx (lPlatform lp, int x);   // Restituisce la hitBox della piattaforma x

// Struct da restituire nella funzione check
struct infoCrash
{
    char type; // Tipo di oggetto con cui ci si scontra
    void *obj; // Puntatore void all'oggetto
};

class level
{
protected:
    int nlevel;                 // Numero del livello
    int diff;                   // Difficoltà
    int numplat;
    bulletManager* B;
    node* head;
    node* coins;
    node* kubas;
    node* shooters;
    node* yucks;
    lPlatform platforms;        // Lista delle piattaforme del livello

    node* dltNode(node* h);
    node* add(void* obj, char type);

public:
    level (int nl, int d);
    void printAll (timeSpan deltaTime);
    infoCrash check (hitBox ht, char d);  // d è la direzione in cui si sposta il giocatore:
    int number ();                       // a: sinistra || w: sopra || d: destra || s: sotto 
    int getDiff ();
    void update (player* P, timeSpan deltaTime);
    int updateCoin (player* P);
    bool completed();
    bulletManager* getBM ();
};

#endif // LEVEL_HPP
