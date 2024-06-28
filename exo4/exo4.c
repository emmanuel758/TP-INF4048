/* Enonce
 * Écrire un analyseur qui permet de renvoyer les lexèmes d’une chaine arithmétique
 * permettant de faire les additions et les multiplications.Exemple : L’analyse 21 + 12 * 45 devra renvoyer:
 */

// importation des bibliotheques
#include <stdio.h>

// declaration des macros

#define etatInitial 0
#define estUnNombre 1
#define Operateur 2
#define etatFinal 3

//  Fonction pour afficher les lexemes reconus

void afficher(int valeur, int etatCourant)
{
    // Vérifie si l'état courant est un nombre
    if (etatCourant == estUnNombre)
        printf("<int:%d>", valeur); // Affiche les nombres au format <int:valeur>

    // Vérifie si l'état courant est un opérateur
    if (etatCourant == Operateur)
        printf("<oper:%c>", valeur); // Affiche les opérateurs au format <oper:caractereactère>
}

// Fonction principale d'analyse lexicale
/* Description:
 * Cette fonction prend un pointeur vers un fichier en lecture et
 * retourne un entier qui représente le succès ou l'échec de l'analyse lexicale.
 */
int analyseLexical(FILE *file)
{
    int nbr = 0;
    int init = 0;
    int q = etatInitial, q_precedent = etatInitial; // Déclare et initialise les états
    char caractere;                                 // Déclare les variables pour lire les caractereactères

    printf("\n"); // Aller a la ligne

    while (!feof(file)) // La boucle continue tant que la fin du fichier (feof(file)) n'est pas atteinte
    {
        fread(&caractere, 1, 1, file); // fread(&caractere, 1, 1, file) lit un caractereactère du fichier et le stocke dans caractere.

        switch (caractere)
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
            q = estUnNombre;
            nbr = nbr * 10 + (caractere - '0');
            break;

        case '+':

        case '*':

            if (q == estUnNombre)
            {
                afficher(nbr, q);
                nbr = 0;
            }

            q = Operateur;
            afficher(caractere, q);
            break;
        case '\n':
            break;

        default:
            printf("\n%c : Parse Error, unkown char\n", caractere);
            return 1;
        }
    }
    fclose(file);
    if (q == estUnNombre)
        afficher(nbr, q); // Affiche le dernier nombre si nécessaire
    printf("\n\n");
    return 0; // Termine la fonction sans erreur
}

// Fonction principale du programme
int main(int argc, char **argv)
{
    FILE *file = fopen(argv[1], "r");   // Ouvre le fichier passé en argument
    int valAnal = analyseLexical(file); // Appelle la fonction d'analyse lexicale

    return 0; // Termine le programme
}
