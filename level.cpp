#include "level.hpp"

// Funzione per generare una piattaforma casuale all'interno di un'area definita da w
hitBox level::newRandomPlat (hitBox w, int de) {
    hitBox nw;
    nw.a.x = w.a.x + random(0,5);
    nw.a.y = w.a.y + random(0,3);
    nw.b.x = nw.a.x + random(15,37);    //(nw.a.x + 2) + (rand()%(w.b.x - nw.a.x - 6));  8 + rand()%(w.b.x - nw.a.x - 8)
    nw.b.y = nw.a.y + 1;
    return nw; 
}

// x dev'essere minore di numplat, altrimenti segmentation fault
hitBox level::hitBoxPlatX (int x) {
    node* lp = platforms;
    while (x>0) {
        lp=lp->next;
        x--;
    }
    return ((platform*)lp->obj)->getHitBox();
}

// Funzione che genera una lista di n piattaforme
void level::createNPlat (int np, hitBox ht, int len, int d) {
    for(int i=0; i<np; i++){
        hitBox hpl = newRandomPlat (ht, d);
        void* newObj = new platform(hpl.a.x, hpl.a.y, hpl.b.x, hpl.b.y, 'p');
        head = add(newObj, '#');
        ht.a.x += len;
        ht.b.x += len;
    }
}

node* level::dltNode(node* h, player* P, int* count){
    if( h==NULL ) return NULL;
    else  if( h->type=='c' ){
        int value = ((coin*)h->obj)->check(P->getHitBox());
        if(value!=-1){
            *count += value;
            node* tmp = h;

            // se l'oggetto eliminato è *head
            if( head==h ) head=h->next;
            if( coins==h ) coins=h->next;
            if( coins->type!='c' ) coins=NULL;

            delete (coin*)tmp->obj;
            delete tmp;
            return dltNode(h->next, P, count);
        }
    }else if( h->type=='k' || h->type=='s' || h->type=='y' ){
        if( ((entity*)h->obj)->getHealth()==0 ){
            node* tmp = h;

            // se l'oggetto eliminato è *head
            if( head==h ) head=h->next;
            if( enemies==h ) enemies=h->next;
            if( enemies->type=='y')
                ((yuck*)enemies->obj)->wakeUp();
            if( enemies->type=='#') // !=NULL può essere tolto quando le piattaforme vengono spostate in lista, anche in coins
                enemies=NULL;

            delete (entity*)tmp->obj;
            delete tmp;
            return dltNode(h->next, P, count);;
        }
    }
    h->next = dltNode(h->next, P, count);
    return h;
}

// aggiunge in testa
node* level::add(void* obj, char type){
    node* tmp = new node;
    tmp->obj = obj;
    tmp->type = type;
    tmp->next = head;
    return tmp;
}

level::level (int nl, int d) {
    this->nlevel = nl; // Assegno il numero del livello 
    this->diff = d; // Difficoltà
    this->B = new bulletManager();
    
    int blevel = LINES-WIN_HEIGHT-1;
    this->head = NULL;
    void* newObj;

    newObj = new platform (0, 0, 1, blevel - 5, '|'); // Parete sinistra
    head = add(newObj, '#');
    newObj = new platform (COLS-2, 0, COLS-1, blevel - 5, '|'); // Parete destra
    head = add(newObj, '#');
    newObj = new platform (-1, 0, -1, blevel, 'X'); // Porta sinistra
    head = add(newObj, '#');
    newObj = new platform (COLS, 0, COLS, blevel, 'X'); // Porta destra
    head = add(newObj, '#');
    newObj = new platform (0, blevel, COLS-1, blevel, '"'); // Base del livello
    head = add(newObj, '#');

    //generazione piattaforme inferiori
    int numPlatinf = random(2,4);           // Genero un valore fra 2 e 4 che rappresenta il numero di piattaforme inferiori in quel livello
    int leninf = (COLS-10) / numPlatinf;    // Larghezza massima delle piattaforme in base al loro numero
    int heightinf = blevel - 7;             // Altezza massima delle piattaforme fissata alla massima capacità di salto del player
    hitBox p1;                              // Hitbox della prima piattaforma
    p1.a.x = 8;                             // valore arbitrario di distanza da tenere dal lato sinistro
    p1.a.y = heightinf - 4;
    p1.b.x = leninf + 5;
    p1.b.y = heightinf;                            // base - altezza del player
    int dens = 8 - numPlatinf;
    createNPlat (numPlatinf, p1, leninf, dens);
    
    // generazione piattaforme superiori
    int numPlatsup = random(2,4);
    int lensup = (COLS-10) / numPlatsup;
    int heightsup = heightinf - 10;                   
    p1.a.x = 8; 
    p1.a.y = heightsup - 2;
    p1.b.x = lensup + 5;
    p1.b.y = heightsup;
    dens = 12 - numPlatsup;
    createNPlat (numPlatsup, p1, lensup, dens);
    this->numplat = 5 + numPlatsup + numPlatinf;
    platforms = head;

    //head -> superiori -> inferiori -> base -> 4 pareti -> NULL

    // Generazione nemici
    int weight = nlevel;
    // Yuck 
    if (nlevel % 4 == 0) {    
        newObj = new yuck(COLS-10, blevel-1, this);
        head = add(newObj, 'y');
        weight--;
    }
    // Shooters
    for (int i=0; weight>1 && i<2; i++) {
        hitBox ht = hitBoxPlatX(1+i*2);
        newObj = new shooter(ht.b.x-4, ht.a.y-1, this);
        head = add(newObj, 's');
        weight -= 2;
    }
    // Kubas
    for (int i=0, pt=5; weight>0 && i<3; i++, pt+=i) { 
        hitBox ht = hitBoxPlatX(numplat-pt);
        newObj = new kuba(ht.a.x+(ht.b.x-ht.a.x)/2, ht.a.y-1, this);
        head = add(newObj, 'k');
        weight--;
    }
    enemies = head;
    // Generazione monete
    for (int p=6, i=0; i<=nlevel/3 && i<3; i++, p+=i) {
        hitBox ht = hitBoxPlatX(numplat-p);
        for(int j=0; j<3; j++) {
            newObj = new coin(ht.a.x+(ht.b.x-ht.a.x)/2-5+j*5, ht.a.y-2, nlevel); // Monete stampate sopra le piattaforme
            head = add(newObj, 'c');
        } 
    }
    coins = head;
    // head ---> coins ---> kubas ---> shooters ---> yucks ---> platforms ---> NULL
}

void level::update (player* P, int* money, timeSpan deltaTime) {
    B->update(deltaTime);

    // Update nemici
    node* tmp = enemies;
    while( tmp!=NULL && tmp->type!='#'){
        if( tmp->type=='k' )
            ((kuba*)tmp->obj)->update(P, deltaTime);
        if( tmp->type=='s' )
            ((shooter*)tmp->obj)->update(P->getPos(), deltaTime);
        if( tmp->type=='y' )
            ((yuck*)tmp->obj)->update(P->getPos(), deltaTime);
        tmp = tmp->next;
    }

	// Pulizia lista
	head = dltNode(head, P, money);
}

infoCrash level::check (hitBox pl, char d) {
    infoCrash info; // Variabile da restituire
    bool here = false; // True se trovo qualcosa

    node* tmp = head;
    while(tmp!=NULL && !here){
        if(tmp->type=='k' || tmp->type=='s' || tmp->type=='y'){
            if( isTouching(pl,((entity*)tmp->obj)->getHitBox(),d) ){
                here = true;
                info.type = tmp->type;
                info.obj = tmp->obj;
            }
        }else if(tmp->type=='#'){
            if( isTouching(pl,((platform*)tmp->obj)->getHitBox(),d) ){
                here = true;
                info.type = tmp->type;
                info.obj = tmp->obj;
            }
        }
        tmp = tmp->next;
    }
    if (!here) {
        info.type = ' ';
        info.obj = NULL;
    }
    return info;
}

void level::printAll (timeSpan deltaTime) {
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
        if( tmp->type=='#' )
            ((platform*)tmp->obj)->print();
        
        tmp = tmp->next;
    }
    
    B->print();
}

int level::number () {
    return this->nlevel;
}

int level::getDiff () {
    return this->diff;
}

bool level::completed() {
    if( enemies==NULL ) return true;
    else return false;
}

bulletManager* level::getBM(){
    return this->B;
}