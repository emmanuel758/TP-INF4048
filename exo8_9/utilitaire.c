#include "utilitaire.h"
#include <stdio.h>
#include <stdlib.h>


/* 1) Fonction sur les listes*/


// Fonctions pour les Noeuds

Noeud* creerNoeud(int valeur) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    if (nouveauNoeud == NULL) {
        perror("Erreur de création du noeud");
        exit(EXIT_FAILURE);
    }
    nouveauNoeud->val = valeur;
    nouveauNoeud->suivant = 0;
    return nouveauNoeud;
}

void insererFin(Noeud** listeChaine, int valeur) {
    Noeud* nouveauNoeud = creerNoeud(valeur);
    if (*listeChaine == NULL) {
        *listeChaine = nouveauNoeud;
    } else {
        Noeud* temp = *listeChaine;
        while (temp->suivant != NULL) {
            temp = temp->suivant;
        }
        temp->suivant = nouveauNoeud;
    }
}

void supprimerNoeud(Noeud** listeChaine, int val) {
    Noeud* temp = *listeChaine;
    Noeud* prev = NULL;
    while (temp != NULL && temp->val != val) {
        prev = temp;
        temp = temp->suivant;
    }
    if (temp == NULL) return; // Noeud non trouvé
    if (prev == NULL) {
        *listeChaine = temp->suivant;
    } else {
        prev->suivant = temp->suivant;
    }
    free(temp);
}

void supprimerQueue(Noeud** listeChaine) {
    if (*listeChaine == NULL) return;
    if ((*listeChaine)->suivant == NULL) {
        free(*listeChaine);
        *listeChaine = NULL;
        return;
    }
    Noeud* temp = *listeChaine;
    while (temp->suivant->suivant != NULL) {
        temp = temp->suivant;
    }
    free(temp->suivant);
    temp->suivant = NULL;
}

void supprimerTete(Noeud** listeChaine) {
    if (*listeChaine == NULL) return;
    Noeud* temp = *listeChaine;
    *listeChaine = (*listeChaine)->suivant;
    free(temp);
}

void insererDebut(Noeud** listeChaine, int val) {
    Noeud* nouveauNoeud = creerNoeud(val);
    nouveauNoeud->suivant = *listeChaine;
    *listeChaine = nouveauNoeud;
}

Noeud* rechercherNoeud(Noeud* listeChaine, int val) {
    Noeud* temp = listeChaine;
    while (temp != NULL) {
        if (temp->val == val) return temp;
        temp = temp->suivant;
    }
    return NULL;
}



void insererFin(Noeud *listeChaine, char donnee)
{
}

void supprimerNoeud(Noeud *listeChaine, char donnee)
{
}

void insererDebut(Noeud *listeChaine, char donnee)
{
}

void afficherListe(Noeud *listeChaine)
{
    Noeud* temp = listeChaine;
    while (temp != NULL) {
        printf("%d -> ", temp->val);
        temp = temp->suivant;
    }
    printf("NULL\n");
}

void detruireListe(Noeud *listeChaine)
{
}

void detruireListe(Noeud** listeChaine) {
    Noeud* temp = *listeChaine;
    while (temp != NULL) {
        Noeud* suivant = temp->suivant;
        free(temp);
        temp = suivant;
    }
    *listeChaine = NULL;
}

// Fonctions pour la File

File* creerFile() {
    File* f = (File*)malloc(sizeof(File));
    if (f == NULL) {
        perror("Erreur de création de la file");
        exit(EXIT_FAILURE);
    }
    f->liste = NULL;
    return f;
}

void initialiserFileVide(File* f) {
    f->liste = NULL;
}

int defiler(File* f) {
    if (f->liste == NULL) return -1;
    Noeud* temp = f->liste;
    int val = temp->val;
    f->liste = f->liste->suivant;
    free(temp);
    return val;
}

void enfiler(File* f, int val) {
    Noeud* nouveauNoeud = creerNoeud(val);
    if (f->liste == NULL) {
        f->liste = nouveauNoeud;
    } else {
        Noeud* temp = f->liste;
        while (temp->suivant != NULL) {
            temp = temp->suivant;
        }
        temp->suivant = nouveauNoeud;
    }
}

int teteFile(File* f) {
    if (f->liste == NULL) return -1;
    return f->liste->val;
}

// Fonctions pour la Pile

Pile* creerPile() {
    Pile* p = (Pile*)malloc(sizeof(Pile));
    if (p == NULL) {
        perror("Erreur de création de la pile");
        exit(EXIT_FAILURE);
    }
    p->liste = NULL;
    return p;
}

void initialiserPileVide(Pile* p) {
    p->liste = NULL;
}

int depiler(Pile* p) {
    if (p->liste == NULL) return -1;
    Noeud* temp = p->liste;
    int val = temp->val;
    p->liste = p->liste->suivant;
    free(temp);
    return val;
}

void empiler(Pile* p, int val) {
    Noeud* nouveauNoeud = creerNoeud(val);
    nouveauNoeud->suivant = p->liste;
    p->liste = nouveauNoeud;
}

int estPileVide(Pile* p) {
    return p->liste == NULL;
}

int tetePile(Pile* p) {
    if (p->liste == NULL) return -1;
    return p->liste->val;
}
