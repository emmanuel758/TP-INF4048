 
 // utilitaire.c
 /*By codeur16*/

 /*By Codeur16*/
#ifndef UTILITAIRE_H_INCLUDED
#define UTILITAIRE_H_INCLUDED

typedef struct Element {
    int valeur;
    struct Element* suivant;
} Element;

typedef struct Pile {
    int indexActuel;
    Element* liste;
    int taillePile;
} Pile;

typedef struct File {
    int indexActuel;
    Element* liste;
    int tailleFile;
} File;


// Fonction sur les listes chainnees

Element* nouveauElement(int val);
void ajouterDebut(Element** liste, int val);
void enleverDebut(Element ** liste);
void inverserListe(Element**liste);
void ajouterFin(Element** liste, int val);
void enleverFin(Element**liste);
int obtenirTete(Element* liste);
int obtenirQueue(Element* liste);
void afficherListe(Element * liste);

// Fonction sur les piles

void initialiserPile(Pile *p);
int obtenirTaillePile(Pile p);
void empilerElement(Pile*p, int val);
int depilerElement(Pile*p);
int estPileVide(Pile p);
int obtenirIndexPile(Pile p);
int obtenirSommet(Pile p);
// Fonction sur les files

void initialiserFile(File *f);
int obtenirTailleFile(File f);
void enfilerElement(File*f, int val);
int obtenirIndexFile(File f);
int defilerElement(File*f);
int estFileVide(File f);
int obtenirTeteFile(File f);
#endif 