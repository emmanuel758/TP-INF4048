#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"

#define ETAT_INIT 0
#define ETAT_NOMBRE 1
#define ETAT_OPERATEUR 2
#define ETAT_FINAL 3

typedef int Etat;

int prioriteOperateur(int operateur) {
    int priorite = -1;

    switch (operateur) {
        case '+':
            priorite = 0;
            break;
        case '*':
            priorite = 1;
            break;
        // Ajoutez d'autres cas pour d'autres opérateurs si nécessaire
    }

    return priorite;
}

void afficher(int valeur, Etat etatCourant) {
    if (etatCourant == ETAT_NOMBRE)
        printf("<int:%d>", valeur);
    if (etatCourant == ETAT_OPERATEUR)
        printf("<oper:%c>", valeur);
}

int estOperateur(char car) {
    return (car == '+' || car == '*');
}

void evaluerGaucheDroite(Element* exp, File* sortie) {
    initialiserFile(sortie);
    Element* courant = exp;

    while (courant != NULL) {
        if (!estOperateur(courant->valeur)) {
            enfilerElement(sortie, courant->valeur);
        } else {
            int operande1 = defilerElement(sortie);
            int operande2 = defilerElement(sortie);
            int resultat;
            switch (courant->valeur) {
                case '+':
                    resultat = operande1 + operande2;
                    break;
                case '*':
                    resultat = operande1 * operande2;
                    break;
                default:
                    fprintf(stderr, "Erreur: opérateur non reconnu.\n");
                    return;
            }
            enfilerElement(sortie, resultat);
        }
        courant = courant->suivant;
    }
}

void evaluerAvecPriorite(Element* exp, File* sortie) {
    Pile pile;
    initialiserPile(&pile);
    initialiserFile(sortie);
    Element* courant = exp;

    while (courant != NULL) {
        if (!estOperateur(courant->valeur)) {
            enfilerElement(sortie, courant->valeur);
        } else {
            while (!estPileVide(pile) && obtenirSommet(pile) != '(' &&
                   prioriteOperateur(obtenirSommet(pile)) >= prioriteOperateur(courant->valeur)) {
                int val = depilerElement(&pile);
                enfilerElement(sortie, val);
            }
            empilerElement(&pile, courant->valeur);
        }
        courant = courant->suivant;
    }

    while (!estPileVide(pile)) {
        int val = depilerElement(&pile);
        enfilerElement(sortie, val);
    }
}

int main() {
    Etat etatCourant = ETAT_INIT;
    Element* expArith = NULL;

    // Simulation d'une expression arithmétique (lecture de l'expression)
    char expression[] = "3+5*2";
    printf("Expression arithmétique : %s\n", expression);

    for (int i = 0; expression[i] != '\0'; i++) {
        char car = expression[i];

        if (car >= '0' && car <= '9') {
            int valeur = car - '0';
            afficher(valeur, ETAT_NOMBRE);
            ajouterFin(&expArith, valeur);
            etatCourant = ETAT_NOMBRE;
        } else if (estOperateur(car)) {
            int valeur = car;
            afficher(valeur, ETAT_OPERATEUR);
            ajouterFin(&expArith, valeur);
            etatCourant = ETAT_OPERATEUR;
        }
    }

    printf("\n");

    printf("Expression en postfixe sans priorité : ");
    File expPostfixeSansPriorite;
    initialiserFile(&expPostfixeSansPriorite);
    evaluerGaucheDroite(expArith, &expPostfixeSansPriorite);
    afficherListe(expPostfixeSansPriorite.liste);

    printf("Résultat de l'expression sans priorité : %d\n", obtenirTeteFile(expPostfixeSansPriorite));

    printf("\n");

    printf("Expression en postfixe avec priorité : ");
    File expPostfixeAvecPriorite;
    initialiserFile(&expPostfixeAvecPriorite);
    evaluerAvecPriorite(expArith, &expPostfixeAvecPriorite);
    afficherListe(expPostfixeAvecPriorite.liste);

    printf("Résultat de l'expression avec priorité : %d\n", obtenirTeteFile(expPostfixeAvecPriorite));

    return 0;
}
