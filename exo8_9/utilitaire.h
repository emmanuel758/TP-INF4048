#ifndef UTILITAIRE_H
#define UTILITAIRE_H

// Declaration des structures  de donneees: 

typedef struct Noeud{  //noeud
    int val;
    struct Noeud * suivant;
} Noeud;

typedef struct File{  // File
 Noeud* liste;
} File ;

typedef struct Pile{  // pile
    Noeud* liste;
} Pile;

// Operations sur les Noeuds

// liste chaine
Noeud* creerNoeud(int valeur);
void insererFin(Noeud* listeChaine, int valeur);
void supprimerNoeud(Noeud* listeChaine, int valeur);
void supprimerQueue(Noeud ** listeChaine);
void supprimerTete(Noeud ** listeChaine);
void insererDebut(Noeud* listeChaine, int valeur);
void afficherListe(Noeud* listeChaine);
void detruireListe(Noeud* listeChaine);

// file
File* creerFile();
void initialiserFileVide(File* f);
int defiler(File* f);
void enfiler(File* f, int val);
int teteFile(File* f);

// pile
Pile* creerPile();
void initialiserPileVide(Pile* p);
int depiler(Pile*p);
void empiler(Pile* p, int val);
int estPileVide(Pile* p);
int tetePile(Pile*p);

#endif