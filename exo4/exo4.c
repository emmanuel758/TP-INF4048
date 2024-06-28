

// /* Enonce
//  * Écrire un analyseur qui permet de renvoyer les lexèmes d’une chaine arithmétique
//  * permettant de faire les additions et les multiplications.Exemple : L’analyse 21 + 12 * 45 devra renvoyer:
//  */

// Importation des bibliothèques
#include <stdio.h>

// Déclaration des macros
#define etatInitial 0
#define estUnNombre 1
#define Operateur 2

// Fonction pour afficher les lexèmes reconnus
void afficher(int valeur, int etatCourant)
{
    // Vérifie si l'état courant est un nombre
    if (etatCourant == estUnNombre)
        printf("<int:%d>", valeur); // Affiche les nombres au format <int:valeur>

    // Vérifie si l'état courant est un opérateur
    if (etatCourant == Operateur)
        printf("<oper:%c>", valeur); // Affiche les opérateurs au format <oper:caractère>
}

// Fonction principale d'analyse lexicale
/* Description:
 * Cette fonction prend un pointeur vers un fichier en lecture et
 * retourne un entier qui représente le succès ou l'échec de l'analyse lexicale.
 */
int analyseLexical(FILE *file)
{
    int nbr = 0;
    int q = etatInitial; // Déclare et initialise les états
    char caractere;      // Déclare les variables pour lire les caractères

    printf("\n"); // Aller à la ligne

    while (fread(&caractere, 1, 1, file) == 1) // Lire un caractère à la fois du fichier pour ne pas lire deux foisi
    {
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
            nbr = nbr * 10 + (caractere - '0'); // convertier un int
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
            printf("\n%c : Parse Error, unknown char\n", caractere);
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
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r"); 
    if (file == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", argv[1]);
        return 1;
    }

    int valAnal = analyseLexical(file); // Appelle la fonction d'analyse lexicale pour fair e l'anal

    return valAnal; // 
}
