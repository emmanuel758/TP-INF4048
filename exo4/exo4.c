/*
 * Écrire un analyseur qui permet de renvoyer les lexèmes d’une chaine arithmétique
 * permettant de faire les additions et les multiplications.Exemple : L’analyse 21 + 12 * 45 devra renvoyer:
 */

// importation des bibliotheques
#include <stdio.h>

// declaration des macros

#define etatInitial 0
#define etatNombre 1
#define etatOperateur 2
#define etatFinal 3

// Définit un nouveau type Etat comme alias pour int
typedef int Etat;

//  Fonction pour afficher les lexemes reconus

void afficher(int valeur, Etat etatCourant)
{
    // Vérifie si l'état courant est un nombre
    if (etatCourant == etatNombre)
        printf("<int:%d>", valeur); // Affiche les nombres au format <int:valeur>

    // Vérifie si l'état courant est un opérateur
    if (etatCourant == etatOperateur)
        printf("<oper:%c>", valeur); // Affiche les opérateurs au format <oper:caractère>
}

// Fonction principale d'analyse lexicale
/* Description:
 * Cette fonction prend un pointeur vers un fichier en lecture et
 * retourne un entier qui représente le succès ou l'échec de l'analyse lexicale.
 */
int analyseLexical(FILE *fdw)
{
    int nbOc = 0, i = 0, j = 0, state = -1, nbr = 0, nbr1; // Variables non utilisées
    int init = 0;                                          // Variable non utilisée
    Etat q = etatInitial, q_precedent = etatInitial;       // Déclare et initialise les états
    char car, tmp;                                         // Déclare les variables pour lire les caractères

    /*
     * nbr:Pour accumuler les chiffres et former un nombre.
     * q : Pour suivre l 'état actuel de l' analyse.
     * car : Pour stocker le caractère lu du fichier.
     * char car, tmp;
     */

    printf("\n"); // Aller a la ligne

    while (!feof(fdw)) // La boucle continue tant que la fin du fichier (feof(fdw)) n'est pas atteinte
    {
        fread(&car, 1, 1, fdw); // fread(&car, 1, 1, fdw) lit un caractère du fichier et le stocke dans car.

        switch (car)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            q = etatNombre;
            nbr = nbr * 10 + (car - '0');
            break;

        case '+':

        case '*':

            if (q == etatNombre)
            {
                afficher(nbr, q);
                nbr = 0;
            }

            q = etatOperateur;
            afficher(car, q);
            break;
        case '\n':
            break;

        default:
            printf("\n%c : Parse Error, unkown char\n", car);
            return 1;
        }
    }
    fclose(fdw);
    if (q == etatNombre)
        afficher(nbr, q); // Affiche le dernier nombre si nécessaire
    printf("\n\n");
    return 0; // Termine la fonction sans erreur
}

// Fonction principale du programme
int main(int argc, char **argv)
{
    FILE *fdw = fopen(argv[1], "r");   // Ouvre le fichier passé en argument
    int valAnal = analyseLexical(fdw); // Appelle la fonction d'analyse lexicale

    return 0; // Termine le programme
}
