#include "level.hpp"

using namespace std;

level::level (int nl, int d) {

    this->nlevel = nl;  // Numero del livello 
    this->diff = d;  // Difficoltà
    this->B = new bulletManager();
    int bLevel = LINES-WIN_HEIGHT-1;
    
    this->platforms = new Pplatform;
    this->platforms->plat = new platform (0, 0, 1, bLevel - 5); // Parete sinistra
    this->platforms->next = new Pplatform;
    lPlatform tmp = this->platforms->next;
    tmp->plat = new platform (COLS-2, 0, COLS-1, bLevel - 5); // Parete destra
    tmp->next = new Pplatform;
    tmp = tmp->next;
    tmp->plat = new platform (-1, -5, -1, bLevel); // Porta sinistra
    tmp->next = new Pplatform; 
    tmp = tmp->next;
    tmp->plat = new platform (COLS, -5, COLS, bLevel); // Porta destra
    tmp->next = new Pplatform; 
    tmp = tmp->next;
    tmp->plat = new platform (0, bLevel, COLS-1, bLevel); // Base del livello
    
    // Generazione piattaforme inferiori
    int numPlatInf = rand()%3 + 2;       // Numero di piattaforme inferiori del livello [2 - 4]
    int lenInf = (COLS-12) / numPlatInf; // Larghezza massima delle piattaforme in base al loro numero
    int heightInf = bLevel - 7;          // Altezza massima delle piattaforme fissata alla massima capacità di salto del player
    hitBox p1;
    p1.a.x = 8;
    p1.a.y = heightInf - 4;
    p1.b.x = lenInf;
    p1.b.y = heightInf;
    tmp->next = createnPlat (numPlatInf, p1, lenInf); // Generazione random delle piattaforme
    
    // Generazione piattaforme superiori
    int numPlatsup = rand()%3 + 2;
    int lensup = (COLS-12) / numPlatsup;
    int heightsup = heightInf - 11;                   
    p1.a.x = 10; 
    p1.a.y = heightsup - 2;
    p1.b.x = lensup;
    p1.b.y = heightsup;
    this->numplat = 5 + numPlatsup + numPlatInf;
    
    while (tmp->next != NULL) {
	    tmp = tmp->next;
	}  
    tmp->next = createnPlat (numPlatsup, p1, lensup); 

    // Generazione nemici
    int weight = this->nlevel+this->diff/2;
    // Yuck 
    if (this->nlevel % 4 == 0) {
        this->Y = new yuck(COLS-10, bLevel-1, this);
        weight -= 1;
    } else this->Y = NULL;
    // Shooters
    lShooter tmp1; this->shooters=NULL;
    for (int i=0; weight>1 && i<2; weight-=2, i++) { 
        hitBox ht = hiboxPlatx(this->platforms, this->numplat-1-i*2);
        tmp1 = new Pshooter;
        tmp1->S = new shooter(ht.a.x+4, ht.a.y-1, this);
        tmp1->next = this->shooters;
        this->shooters = tmp1;
    }
    tmp1 = NULL;
    // Kubas
    lKuba tmp2; this->kubas=NULL;
    for (int i=0, pt=4; weight>0 && i<3; i++, pt+=i, weight--) { 
        hitBox ht = hiboxPlatx(this->platforms, pt);     
        tmp2 = new Pkuba;
        tmp2->K = new kuba(ht.a.x+(ht.b.x-ht.a.x)/2, ht.a.y-1, this);
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
            tmp3->C = new coin(ht.a.x+(ht.b.x-ht.a.x)/2-5+j*5, ht.a.y-2, 10); // Monete stampate sopra le piattaforme
            tmp3->next = this->coins;
            this->coins = tmp3;
        } 
    }
    tmp3=NULL;
}

// Funzione per generare una piattaforma casuale all'interno di un'area definita da w
hitBox level::newRandomPlat (hitBox p1) {
    hitBox nw;
    nw.a.x = p1.a.x + (rand()%5);  
    nw.a.y = p1.a.y + (rand()%4);
    nw.b.x = nw.a.x + 18 + (rand()%(p1.b.x-nw.a.x-19));   // Lunghezza compresa fra nw.a.x + 18 e p1.b.x
    nw.b.y = nw.a.y + 1;

    return nw;
}

// Funzione che genera una lista di n piattaforme in modo ricorsivo
lPlatform level::createnPlat (int np, hitBox p1, int len) {
    if (np > 0) {
        lPlatform tmp1 = new Pplatform;
        hitBox hpl = newRandomPlat (p1);
        tmp1->plat = new platform(hpl.a.x, hpl.a.y, hpl.b.x, hpl.b.y);
        p1.a.x = max(hpl.b.x+4, p1.a.x+len);
        p1.b.x += len;
        tmp1->next = createnPlat (np-1, p1, len);
        return tmp1;
    } else return NULL;
}

// Funzione che elimina i kuba morti
lKuba level::dltKuba (lKuba lk, int* points) {
    if (lk == NULL) return NULL;
    else if (lk->K->getHealth() == 0) {
        lKuba tmp = lk;
        lk = dltKuba (lk->next, points);
        delete tmp->K;
        delete tmp;
        tmp = NULL;
        *points += 1;
        return lk;
    } else {
        lk->next = dltKuba (lk->next, points);
        return lk;
    }
}

// Funzione che elimina gli shooters morti
lShooter level::dltShooter (lShooter ls, int* points) {
    if (ls == NULL) return NULL;
    else if (ls->S->getHealth() == 0) {
        lShooter tmp = ls;
        ls = dltShooter (ls->next, points);
        delete tmp->S;
        delete tmp;
        tmp = NULL;
        *points += 1;
        return ls;
    } else {
        ls->next = dltShooter (ls->next, points);
        return ls;
    }
}

// Eliminazione delle monete acquisite con aggiornamento del valore
lCoin level::dltCoin (lCoin lc, player* P, int* count, int* points) {
    if (lc==NULL) return NULL;
    else {
        int value = lc->C->check(P->getHitBox());
        if(value==-1){
		    lc->next = dltCoin(lc->next, P, count, points);
            return lc;
	    } else {
            *count += value;
            *points += 1;
            lCoin tmp = lc;
            lc=lc->next;
            delete tmp->C;
            delete tmp;
            tmp=NULL;
		    return dltCoin(lc, P, count, points);
	    }
    }
}

void level::print_platforms (lPlatform lsp) {
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

hitBox level::hiboxPlatx (lPlatform lp, int x) {
    while (x!=0) {
        lp=lp->next;
        x--;
    }
    return lp->plat->getHitbox();
}

// Stampa degli elementi del livello
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
    B->print();
}

// Indica se 'pl' si sta scontrando con qualcosa muovendosi nella direzione 'd'
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

void level::update (player* P, timeSpan deltaTime, int* money, int* points) {
    B->update(deltaTime);
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
	this->kubas = dltKuba (this->kubas, points);
    this->shooters = dltShooter (this->shooters, points);
	
    if(this->shooters==NULL && this->kubas==NULL && this->Y!=NULL){
		this->Y->wakeUp();
	}
	if(this->Y!=NULL && this->Y->getHealth()==0){
		delete this->Y;
		this->Y = NULL;
        *points += 10;
	}
    // update delle monete
    this->coins = dltCoin (this->coins, P, money, points);
}

bool level::completed() {
    if(this->kubas==NULL && this->shooters==NULL && this->Y==NULL) return true;
    else return false;
}

bulletManager* level::getBM(){
    return B;
}