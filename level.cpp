#include <ncurses.h>
#include <iostream>
#include <chrono>
#include <time.h>
#include <stdlib.h>

#include "level.hpp"
using namespace std;

// Funzione per generare una piattaforma casuale all'interno di un'area definita da w
hitBox newRandomPlat (hitBox w, int de) {
    hitBox nw;
    nw.a.x = w.a.x + (rand()%5);  
    nw.a.y = w.a.y + (rand()%4);
    nw.b.x = nw.a.x + (15 + rand()%(35 - 12));    //(nw.a.x + 2) + (rand()%(w.b.x - nw.a.x - 6));  8 + rand()%(w.b.x - nw.a.x - 8)
    nw.b.y = nw.a.y + 1;

    return nw; 
}

// Funzione che genera una lista di n piattaforme in modo ricorsivo
lPlatform createnPlat (int np, hitBox ht, int len, int d) {
    if (np > 0) {
        lPlatform tmp1 = new Pplatform;
        hitBox hpl = newRandomPlat (ht, d);
        tmp1->plat = new platform(hpl.a.x, hpl.a.y, hpl.b.x, hpl.b.y);
        ht.a.x += len;
        ht.b.x += len;
        tmp1->next = createnPlat (np-1, ht, len, d);
        return tmp1;
    } else return NULL;
}

// Funzione che elimina i kuba morti
lKuba dltKuba (lKuba lk) {
    if (lk == NULL) return NULL;
    else if (lk->K->getHealth() == 0) {
        lKuba tmp = lk;
        lk = dltKuba (lk->next);
        delete tmp->K;
        delete tmp;
        tmp = NULL;
        return lk;
    } else {
        lk->next = dltKuba (lk->next);
        return lk;
    }
}

// Funzione che elimina gli shooters morti
lShooter dltShooters (lShooter ls) {
    if (ls == NULL) return NULL;
    else if (ls->S->getHealth() == 0) {
        lShooter tmp = ls;
        ls = dltShooters (ls->next);
        delete tmp->S;
        delete tmp;
        tmp = NULL;
        return ls;
    } else {
        ls->next = dltShooters (ls->next);
        return ls;
    }
}

lCoin dltCoin (lCoin lc, player* P, int* count) {
    if (lc==NULL) return NULL;
    else {
        int value = lc->C->check(P->getHitBox());
        if(value==-1){
		    lc->next = dltCoin(lc->next, P, count);
            return lc;
	    } else {
            *count += value;
            lCoin tmp = lc;
            lc=lc->next;
            delete tmp->C;
            delete tmp;
            tmp=NULL;
		    return dltCoin(lc, P, count);
	    }
    }
}

void print_platforms (lPlatform lsp) {
    for (int i = 0; i < 4 && lsp != NULL; i++) {          // Stampa delle pareti
        lsp->plat->printc('|');
	    lsp = lsp->next;
    }

    lsp->plat->printc('"');                 // stampa della base
    lsp = lsp->next;

    while (lsp != NULL) {                   // Stampa delle piattaforme sospese
        lsp->plat->printp();
	    lsp = lsp->next;
	}
    lsp = NULL;
    delete lsp;
}

hitBox hiboxPlatx (lPlatform lp, int x) {
    while (x!=0) {
        lp=lp->next;
        x--;
    }
    return lp->plat->getHitbox();
}

level::level (int nl, int d, bulletManager* B) {
    //generazione piattaforme inferiori
    this->nlevel = nl;                      // Assegno il numero del livello 
    this->diff = d;                         // Difficoltà
    int numPlatinf = (rand()%3) + 2;        // Genero un valore fra 2 e 4 che rappresenta il numero di piattaforme inferiori in quel livello
    int leninf = (COLS-10) / numPlatinf;    // Larghezza massima delle piattaforme in base al loro numero
    int blevel = LINES-WIN_HEIGHT-1;
    int heightinf = blevel - 7;             // Altezza massima delle piattaforme fissata alla massima capacità di salto del player
    hitBox p1;                              // Hitbox della prima piattaforma
    p1.a.x = 8;                             // valore arbitrario di distanza da tenere dal lato sinistro
    p1.a.y = heightinf - 4;
    p1.b.x = leninf + 5;
    p1.b.y = heightinf;                            // base - altezza del player
    int dens = 8 - numPlatinf;
    
    this->platforms = new Pplatform;
    this->platforms->plat = new platform (0, 0, 1, blevel - 5);// Parete sinistra
    this->platforms->next = new Pplatform;
    lPlatform bs = this->platforms->next;
    bs->plat = new platform (COLS-2, 0, COLS-1, blevel - 5);     // Parete destra
    bs->next = new Pplatform;
    bs = bs->next;
    bs->plat = new platform (-1, 0, -1, blevel);               // Porta sinistra
    bs->next = new Pplatform; 
    bs = bs->next;
    bs->plat = new platform (COLS, 0, COLS, blevel);         // Porta destra
    bs->next = new Pplatform; 
    bs = bs->next;
    bs->plat = new platform (0, blevel, COLS-1, blevel); // Base del livello
    
    bs->next = createnPlat (numPlatinf, p1, leninf, dens);
    
    // generazione piattaforme superiori
    int numPlatsup = (rand()%3) + 2;
    int lensup = (COLS-10) / numPlatsup;
    int heightsup = heightinf - 10;                   
    p1.a.x = 8; 
    p1.a.y = heightsup - 2;
    p1.b.x = lensup + 5;
    p1.b.y = heightsup;
    dens = 12 - numPlatsup;
    this->numplat = 5 + numPlatsup + numPlatinf;
    
    lPlatform tmp = this->platforms;
    while (tmp->next != NULL) {
	    tmp = tmp->next;
	}  
    tmp->next = createnPlat (numPlatsup, p1, lensup, dens);

    // Generazione nemici
    int weight = this->nlevel;
    // Yuck 
    if (this->nlevel % 4 == 0) {    
        this->Y = new yuck(COLS-6, blevel-1, this, B);
        weight -= 1;
    } else this->Y = NULL;
    // Shooters
    lShooter tmp1; this->shooters=NULL;
    for (int i=0; weight>1 && i<2; weight-=2, i++) { 
        hitBox ht = hiboxPlatx(this->platforms, this->numplat-1-i*2);
        tmp1 = new Pshooter;
        tmp1->S = new shooter(ht.a.x+4, ht.a.y-1, this, B);
        tmp1->next = this->shooters;
        this->shooters = tmp1;
    }
    tmp1 = NULL;
    // Kubas
    lKuba tmp2; this->kubas=NULL;
    for (int i=0, pt=4; weight>0 && i<3; i++, pt+=i, weight--) { 
        hitBox ht = hiboxPlatx(this->platforms, pt);     
        tmp2 = new Pkuba;
        tmp2->K = new kuba(ht.a.x+(ht.b.x-ht.a.x)/2, ht.a.y-1, this, B);
        tmp2->next = this->kubas;
        this->kubas = tmp2;
    }
    tmp2 = NULL;
    // Generazione monete
    lCoin tmp3; this->coins=NULL;
    for (int p=5, i=0; i<=this->nlevel/3&&i<3; i++, p+=i) {
        hitBox ht = hiboxPlatx(this->platforms, p);
        for(int j=0; j<3; j++) {
            tmp3 = new Pcoin;
            tmp3->C = new coin(ht.a.x+(ht.b.x-ht.a.x)/2-5+j*5, ht.a.y-2, this->nlevel); // Monete stampate sopra le piattaforme
            tmp3->next = this->coins;
            this->coins = tmp3;
        } 
    }
    tmp3=NULL;
}

void level::printAll (timeSpan deltaTime) {
    print_platforms (this->platforms);

    lCoin tmpc = this->coins;
    while (tmpc != NULL) {
        tmpc->C->print(deltaTime);
        tmpc = tmpc->next;
    }
    delete tmpc;
    lKuba tmpk = this->kubas;
    while (tmpk != NULL) {
        tmpk->K->print(deltaTime);
        tmpk = tmpk->next;
    }
    delete tmpk;
    lShooter tmps = this->shooters;
    while (tmps != NULL) {
        tmps->S->print(deltaTime);
        tmps = tmps->next;
    }
    delete tmps;
    if (this->Y != NULL) this->Y->print(deltaTime);
}

/*
    ' ' : void
    k   : kuba
    s   : shooter
    y   : yuck
    #   : platform
*/
infoCrash level::check (hitBox pl, char d) {
    infoCrash info;      // Variabile da restituire                             
    bool here = false;   // True se trovo qualcosa

    lPlatform tmp1 = this->platforms;
    while (tmp1 != NULL && !here) {
        if (isTouching (pl, tmp1->plat->getHitbox(), d)) {
            here = true;
            info.type = '#';
            info.obj = tmp1->plat;
        }
        tmp1 = tmp1->next;
    }
    tmp1 = NULL;
    delete tmp1;

    lKuba tmp2 = this->kubas;
    while (tmp2 != NULL && !here) {
        if (isTouching (pl, tmp2->K->getHitBox(), d)) {
            here = true;
            info.type = 'k';
            info.obj = tmp2->K;
        }
        tmp2 = tmp2->next;
    }
    tmp2 = NULL;
    delete tmp2;

    lShooter tmp3 = this->shooters;
    while (tmp3 != NULL && !here) {
        if (isTouching (pl, tmp3->S->getHitBox(), d)) {
            here = true;
            info.type = 's';
            info.obj = tmp3->S;
        }
        tmp3 = tmp3->next;
    }
    tmp3 = NULL;
    delete tmp3;

    if (this->Y != NULL && isTouching (pl, this->Y->getHitBox(), d) && !here) {
        here = true;
        info.type = 'y';
        info.obj = this->Y;
    }

    if (!here) {
        info.type = ' ';
        info.obj = NULL;
    }

    return info;
}

int level::number () {
    return this->nlevel;
}

int level::getDiff () {
    return this->diff;
}

void level::update (player* P, timeSpan deltaTime) {
    // Update nemici
    if(this->kubas!=NULL) {
        lKuba tmpk = this->kubas;
        while (tmpk != NULL) {
            tmpk->K->update(P, deltaTime);
            tmpk = tmpk->next;
        }
        delete tmpk;
    }
    if (this->shooters != NULL) {
        lShooter tmps = this->shooters;
        while (tmps != NULL) {
            tmps->S->update(P->getPos(), deltaTime);
            tmps = tmps->next;
        }
        delete tmps;
    }
	if(this->Y!=NULL) this->Y->update(P->getPos(), deltaTime);

	// Eliminazione entità morte
	this->kubas = dltKuba (this->kubas);
    this->shooters = dltShooters (this->shooters);
	
    if(this->shooters==NULL && this->kubas==NULL && this->Y!=NULL){
		this->Y->wakeUp();
	}
	if(this->Y!=NULL && this->Y->getHealth()==0){
		delete this->Y;
		this->Y = NULL;
	}
}

int level::updateCoin (player* P) {
    int count=0;
    this->coins = dltCoin (this->coins, P, &count);
    return count;
}

bool level::completed() {
    if(this->kubas==NULL && this->shooters==NULL && this->Y==NULL) return true;
    else return false;
}