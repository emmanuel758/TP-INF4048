#include <stdlib.h>
#include "utilitaire.h"
#include <stdio.h>

// Fonction sur les listes chainnees

Element* nouveauElement(int val) {
    Element* elem = (Element*)malloc(sizeof(Element));
    elem->valeur = val;
    elem->suivant = NULL;
    return elem;
}

void ajouterDebut(Element** liste, int val) {
    Element* elem = nouveauElement(val);
    elem->suivant = *liste;
    *liste = elem;
}

void inverserListe(Element** liste) {
    Element* l = NULL;
    Element* q = *liste;
    Element* p;
    while (q != NULL) {
        ajouterDebut(&l, q->valeur);
        p = q;
        q = q->suivant;
        free(p);
    }
    *liste = l;
}

void ajouterFin(Element** liste, int val) {
    inverserListe(liste);
    ajouterDebut(liste, val);
    inverserListe(liste);
}

void enleverDebut(Element** liste) {
    Element* elem = *liste;
    *liste = (*liste)->suivant;
    free(elem);
}

void enleverFin(Element** liste) {
    inverserListe(liste);
    enleverDebut(liste);
    inverserListe(liste);
}

int obtenirTete(Element* liste) {
    return liste->valeur;
}

int obtenirQueue(Element* liste) {
    int val;
    inverserListe(&liste);
    val = liste->valeur;
    inverserListe(&liste);
    return val;
}

void afficherListe(Element* liste) {
    Element* elem = liste;
    printf("\n");
    while (elem != NULL) {
        printf("%d", elem->valeur);
        elem = elem->suivant;
    }
    printf("\n");
}

// Fonction sur les listes piles

void initialiserPile(Pile* p) {
    p->indexActuel = -1;
    p->liste = NULL;
    p->taillePile = 0;
}

int estPileVide(Pile p) {
    return p.taillePile == 0;
}

void empilerElement(Pile* p, int val) {
    ajouterDebut(&(p->liste), val);
    p->indexActuel++;
    p->taillePile++;
}

int depilerElement(Pile* p) {
    int val = -1;
    if (!estPileVide(*p)) {
        val = obtenirTete(p->liste);
        enleverDebut(&(p->liste));
        p->indexActuel--;
        p->taillePile--;
    }
    return val;
}

int obtenirSommet(Pile p) {
    return estPileVide(p) ? -1 : p.liste->valeur;
}

int obtenirTaillePile(Pile p) {
    return p.taillePile;
}

int obtenirIndexPile(Pile p) {
    return p.indexActuel;
}

// Fonction sur les diles

void initialiserFile(File* f) {
    f->indexActuel = -1;
    f->liste = NULL;
    f->tailleFile = 0;
}

int estFileVide(File f) {
    return f.tailleFile == 0;
}

void enfilerElement(File* f, int val) {
    ajouterFin(&(f->liste), val);
    f->indexActuel++;
    f->tailleFile++;
}

int defilerElement(File* f) {
    int val = -1;
    if (!estFileVide(*f)) {
        val = obtenirTete(f->liste);
        enleverDebut(&(f->liste));
        f->indexActuel--;
        f->tailleFile--;
    }
    return val;
}

int obtenirTeteFile(File f) {
    return estFileVide(f) ? -1 : f.liste->valeur;
}

int obtenirTailleFile(File f) {
    return f.tailleFile;
}

int obtenirIndexFile(File f) {
    return f.indexActuel;
}

