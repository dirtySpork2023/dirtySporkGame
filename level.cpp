#include "level.hpp"

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

node* dltNode(node* h){
    if( h==NULL ) return NULL;
    else if(h->type=='k' || h->type=='s' || h->type=='y'){
        if( ((entity*)h->obj)->getHealth()==0 ){
            node* tmp = h;
            h = dltNode( h->next );
            delete tmp->obj;
            delete tmp;
            return h;
        }
    }
    h->next = dltNode( h->next );
    return h;
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

// aggiunge in testa
node* level::add(void* obj, char type){
    node* tmp = new node;
    tmp->obj = obj;
    tmp->type = type;
    tmp->next = head;
    head = tmp;
}

level::level (int nl, int d) {
    //generazione piattaforme inferiori
    this->nlevel = nl;                      // Assegno il numero del livello 
    this->diff = d;                         // Difficoltà
    this->B = new bulletManager();
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
    lPlatform bs2 = this->platforms->next;
    bs2->plat = new platform (COLS-2, 0, COLS-1, blevel - 5);     // Parete destra
    bs2->next = new Pplatform;
    bs2 = bs2->next;
    bs2->plat = new platform (-1, 0, -1, blevel);               // Porta sinistra
    bs2->next = new Pplatform; 
    bs2 = bs2->next;
    bs2->plat = new platform (COLS, 0, COLS, blevel);         // Porta destra
    bs2->next = new Pplatform; 
    bs2 = bs2->next;
    bs2->plat = new platform (0, blevel, COLS-1, blevel); // Base del livello
    
    bs2->next = createnPlat (numPlatinf, p1, leninf, dens);
    
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
    
    lPlatform tmpp = this->platforms;
    while (tmpp->next != NULL) {
	    tmpp = tmpp->next;
	}  
    tmpp->next = createnPlat (numPlatsup, p1, lensup, dens);

    // Generazione nemici
    head = NULL;
    void* tmp;

    int weight = this->nlevel;
    // Yuck 
    if (this->nlevel % 4 == 0) {    
        tmp = new yuck(COLS-10, blevel-1, this);
        head = add(tmp, 'y');
        yuck = head;
        weight -= 1;
    }
    // Shooters
    for (int i=0; weight>1 && i<2; weight-=2, i++) { 
        hitBox ht = hiboxPlatx(this->platforms, this->numplat-1-i*2);
        tmp = new shooter(ht.a.x+4, ht.a.y-1, this);
        head = add(tmp, 's');
    }
    shooters = head;
    // Kubas
    for (int i=0, pt=4; weight>0 && i<3; i++, pt+=i, weight--) { 
        hitBox ht = hiboxPlatx(this->platforms, pt);     
        tmp = new kuba(ht.a.x+(ht.b.x-ht.a.x)/2, ht.a.y-1, this);
        head = add(tmp, 'k');
    }
    kubas = head;
    // Generazione monete
    for (int p=5, i=0; i<=this->nlevel/3&&i<3; i++, p+=i) {
        hitBox ht = hiboxPlatx(this->platforms, p);
        for(int j=0; j<3; j++) {
            tmp = new coin(ht.a.x+(ht.b.x-ht.a.x)/2-5+j*5, ht.a.y-2, this->nlevel); // Monete stampate sopra le piattaforme
            head = add(tmp, 'c');
        } 
    }
    coins = head;

    // coins --> kubas --> shooters --> yuck --> NULL
}

void level::printAll (timeSpan deltaTime) {
    print_platforms (this->platforms);

    node* tmp = head;
    while( tmp!=NULL ){
        if( tmp->type=='c' )
            ((coin*)tmp->obj)->print(deltaTime);
        if( tmp->type=='k' )
            ((kuba*)tmp->obj)->print(deltaTime);
        if( tmp->type=='s' )
            ((shooter*)tmp->obj)->print(deltaTime);
        if( tmp->type=='y' )
            ((yuck*)tmp->obj)->print(deltaTime);
    }

    B->print();
}

/*
    ' ' : void
    k   : kuba
    s   : shooter
    y   : yuck
    #   : platform
    c   : coin
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

    node* tmp = head;
    while(tmp!=NULL && !here){
        if(tmp->type=='k' || tmp->type=='s' || tmp->type=='y'){
            if( isTouching(pl,((entity*)tmp->obj)->getHitBox(),d) ){
                here = true;
                info.type = tmp->type;
                info.obj = tmp->obj;
            }
        }
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
    B->update(deltaTime);
    // Update nemici

    node* tmp = head;
    while( tmp!=NULL ){
        if( tmp->type=='k' )
            ((kuba*)tmp->obj)->update(P, deltaTime);
        if( tmp->type=='s' )
            ((shooter*)tmp->obj)->update(P->getPos(), deltaTime);
        if( tmp->type=='y' )
            ((yuck*)tmp->obj)->update(P->getPos(), deltaTime);
    }

	// Eliminazione entità morte
	head = dltNode(head);

    tmp = head;
    bool found = false;
    while( tmp!=NULL && !found ){
        if(tmp->type=='k' || tmp->type=='s')
            found = true;
    }
    if(!found){
		tmp = head;
        while( tmp!=NULL && !found ){
            if(tmp->type=='y')
                ((yuck*)tmp->obj)->wakeUp();
        }
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

bulletManager* level::getBM(){
    return B;
}