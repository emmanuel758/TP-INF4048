
#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"

#define etatInitiale 0
#define etatDuNombre 1
#define Operateur 5
#define etatErreur 4
#define etatFinal 3

int prioriteOperateur(int operateur)
{
    switch (operateur)
    {
    case '+':
        return 0;
    case '*':
        return 1;
    default:
        return -1; // Opérateur non reconnu
    }
}

void afficher(int valeur, int etatactuel)
{
    if (etatactuel == etatDuNombre)
        printf("<int:%d>", valeur);
    else if (etatactuel == Operateur)
        printf("<oper:%c>", valeur);
}

int estOperateur(int caractere)
{
    int result = 0;
    if (caractere == '+' || caractere == '*' || caractere == '/' || caractere == '-' || caractere == '%')
        result = 1;
    return result;
}

int EffectuerCalcul(int operation, int operand1, int operand2)
{
    if (operation == '+')
    {
        return operand1 + operand2;
    }
    else if (operation == '*')
    {
        return operand1 * operand2;
    }
    else if (operation == '/')
    {
        return operand1 / operand2;
    }
    else if (operation == '-')
    {
        return operand1 - operand2;
    }
    else if (operation == '%')
    {
        return operand1 % operand2;
    }
    else
    {
        return 0; // Opérateur non reconnu
    }
}
// algorithme de Shunting-yard
void exp_post_fixe_avec_prio(Element *expression, File *expressionEnSortie)
{
    Pile pile;
    initialiserPile(&pile);
    initialiserFile(expressionEnSortie);
    Element *actuel = expression;

    while (actuel != NULL)
    {
        if (!estOperateur(actuel->valeur))
        {
            enfilerElement(expressionEnSortie, actuel->valeur);
        }
        else
        {
            while (!estPileVide(pile) && obtenirSommet(pile) != '(' &&
                   prioriteOperateur(obtenirSommet(pile)) >= prioriteOperateur(actuel->valeur))
            {
                int operande2 = defilerElement(expressionEnSortie);
                int operande1 = defilerElement(expressionEnSortie);
                int op = depilerElement(&pile);
                int resultat = EffectuerCalcul(op, operande1, operande2);
                enfilerElement(expressionEnSortie, resultat);
            }
            empilerElement(&pile, actuel->valeur);
        }
        actuel = actuel->suivant;
    }

    while (!estPileVide(pile))
    {
        int val = depilerElement(&pile);
        enfilerElement(expressionEnSortie, val);
    }
}

// void exp_post_fixe_sans_prio(Element* expression, File* expressionEnSortie) {
//     initialiserFile(expressionEnSortie);
//     Element* actuel = expression;
//     Pile pile;
//     initialiserPile(&pile);  // Initialiser correctement la pile

//     while (actuel != NULL) {
//         if (!estOperateur(actuel->valeur)) {
//             enfilerElement(expressionEnSortie, actuel->valeur);
//         } else {
//             while (!estPileVide(pile)) {
//                 int operande2 = depilerElement(&pile);
//                 int operande1 = depilerElement(&pile);
//                 int resultat = EffectuerCalcul(actuel->valeur, operande1, operande2);
//                 enfilerElement(expressionEnSortie, resultat);
//             }
//             empilerElement(&pile, actuel->valeur);
//         }
//         actuel = actuel->suivant;
//     }

//     while (!estPileVide(pile)) {
//         int val = depilerElement(&pile);
//         enfilerElement(expressionEnSortie, val);
//     }
// }

// fonction sans
// void exp_post_fixe_sans_prio(Element* expression, File* expressionEnSortie) {
//     initialiserFile(expressionEnSortie);
//     Element* actuel = expression;
//     Pile pile;
//     initialiserPile(&pile);

//     while (actuel != NULL) {
//         if (!estOperateur(actuel->valeur)) {
//             enfilerElement(expressionEnSortie, actuel->valeur);
//         } else {
//             while (!estPileVide(pile)) {
//                 int operande2 = depilerElement(&pile);
//                 int operande1 = depilerElement(&pile);
//                 int resultat = EffectuerCalcul(actuel->valeur, operande1, operande2);
//                 enfilerElement(expressionEnSortie, resultat);
//             }
//             empilerElement(&pile, actuel->valeur);
//         }
//         actuel = actuel->suivant;
//     }

//     while (!estPileVide(pile)) {
//         int val = depilerElement(&pile);
//         enfilerElement(expressionEnSortie, val);
//     }
// }

void exp_post_fixe_sans_prio(File *sortie, Element *expression)
{

    Element *liste = expression;
    initialiserFile(sortie);
    Pile pile;
    initialiserPile(&pile);
    int valeur;
    while (expression != 0)
    {
        if (!estOperateur(expression->valeur))
        {
            enfilerElement(sortie, expression->valeur);
        }
        else
        {
            if (!estPileVide(pile))
            {
                valeur = depilerElement(&pile);
                enfilerElement(sortie, valeur);
            }

            empilerElement(&pile, expression->valeur);
        }
        expression = expression->suivant;
    }
    if (!estPileVide(pile))
    {
        valeur = depilerElement(&pile);
        enfilerElement(sortie, valeur);
    }
}

int evaluation_gauche_droite_alternative(File expressionPosfixe)
{
    Pile p;
    initialiserPile(&p);

    while (!estFileVide(expressionPosfixe))
    {
        int valeur = defilerElement(&expressionPosfixe);

        if (!estOperateur(valeur))
        {
            empilerElement(&p, valeur);
        }
        else
        {
            int operand2 = depilerElement(&p);
            int operand1 = depilerElement(&p);
            int resultat = EffectuerCalcul(valeur, operand1, operand2);
            empilerElement(&p, resultat);
        }
    }

    int resultat = depilerElement(&p);
    return resultat;
}

int analyseLexical(FILE *file)
{
    int nombre = 0;
    int eInit = etatInitiale;
    char car;
    printf("\n");

    while (fread(&car, 1, 1, file) == 1)
    {
        if (car >= '0' && car <= '9')
        {
            eInit = etatDuNombre;
            int temp_nombre = nombre * 10 + (car - '0');
            if (temp_nombre <= 100)
            {
                nombre = temp_nombre;
            }
            else
            {
                // Gérer le cas où le nombre dépasse 100
                printf("Erreur : Nombre dépasse 100\n");
                // Vous pouvez soit réinitialiser le nombre soit traiter l'erreur d'une autre manière
                nombre = 0; // Par exemple, réinitialiser le nombre
            }
        }
        else if (car == '+' || car == '*')
        {
            if (eInit == etatDuNombre)
            {
                afficher(nombre, eInit);
                nombre = 0;
            }
            eInit = Operateur;
            afficher(car, eInit);
        }
        else if (car == '\n')
        {
            continue;
        }
        else
        {
            printf("\n%c : caractère inconnu, veuillez réessayer.\n", car);
            return 1;
        }
    }

    if (eInit == etatDuNombre)
        afficher(nombre, eInit);

    printf("\n\n");
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <fichier_expression>\n", argv[0]);
        return 1;
    }

    FILE *fdw = fopen(argv[1], "r");
    if (fdw == NULL)
    {
        fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier %s.\n", argv[1]);
        return 1;
    }

    // int val_anal = analyseLexical(fdw);
    // if (val_anal != 0) {
    //     fclose(fdw);
    //     return 1;
    // }

    // fseek(fdw, 0, SEEK_SET);  // Réinitialisation du fichier

    // Element* exp_arith = NULL;
    // char car;
    // while (fread(&car, 1, 1, fdw) == 1) {
    //     if (car >= '0' && car <= '9') {
    //         int valeur = car - '0';
    //         ajouterFin(&exp_arith, valeur);
    //     } else if (estOperateur(car)) {
    //         ajouterFin(&exp_arith, car);
    //     }
    // }
    int ResultAnalyse = analyseLexical(fdw);
    if (ResultAnalyse != 0)
    {
        fclose(fdw);
        return 1;
    }

    fseek(fdw, 0, SEEK_SET); // Réinitialisation du fichier

    Element *expression = NULL;
    char car;
    while (fread(&car, 1, 1, fdw) == 1)
    {
        if (car >= '0' && car <= '9')
        {
            int valeur = car - '0';
            ajouterFin(&expression, valeur);
        }
        else if (estOperateur(car))
        {
            int valeur = car;
            ajouterFin(&expression, valeur);
        }
    }

    File expressionENsortie;
    initialiserFile(&expressionENsortie);

    // Calcul avec l'expression en postfixe sans priorité
    exp_post_fixe_sans_prio(&expressionENsortie, expression);
    int resultat1 = evaluation_gauche_droite_alternative(expressionENsortie);

    initialiserFile(&expressionENsortie); // Réinitialisation de la file
    // Calcul avec l'expression en postfixe avec priorité
    exp_post_fixe_avec_prio(expression, &expressionENsortie);
    int resultat2 = evaluation_gauche_droite_alternative(expressionENsortie);

    printf("Avec priorité: %d\t Sans priorité: %d\n", resultat2, resultat1);

    fclose(fdw);

    // Libérer la mémoire allouée pour exp_arith
    while (expression != NULL)
    {
        Element *temp = expression;
        expression = expression->suivant;
        free(temp);
    }

    return 0;
}
