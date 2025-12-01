#include <stdio.h>

char tableau[3][3];
char X = 'X';
char O = 'O';
int resultat = 0;  // résultat de wincondition()

void initTableau() { // là on met en place les caractères vides
    for (int ligne = 0; ligne < 3; ligne++) { //  dans chaque ligne
        for (int col = 0; col < 3; col++) { // 3 caractères vides qsui pourront êtres remplacés par X ou O
            tableau[ligne][col] = ' ';
        }
    }
}
void afficherTableau() {

    printf("\n");
    printf("   0    1    2 \n");
    printf("  -------------\n"); // première ligne du tableau

    for (int ligne = 0; ligne < 3; ligne++) { // ligne = horizontal

        if (ligne!= 0) {
            printf("  ----+---+----\n"); // différent de 0 donc ça sera 1 et 2 pour les deux etages du milieu
        }

        printf("%i ",ligne);// indices verticals

        for (int col = 0; col < 3; col++) { // colonne = vertical

            printf("| %c ",tableau[ligne][col]); // donc pour chaques lignes horizontales
        }                                         // trois fois | + caractere vide
        printf("|\n"); // à la fin de chaque ligne pour fermer le tableau
    }
    printf("  -------------\n\n"); // dernière ligne
}

int wincondition() {

    // colonnes
    if (tableau[0][0] == X && tableau[1][0] == X && tableau[2][0] == X) {
        return 1;
    }
    if (tableau[0][1] == X && tableau[1][1] == X && tableau[2][1] == X) {
        return 1;
    }
    if (tableau[0][2] == X && tableau[1][2] == X && tableau[2][2] == X) {
        return 1;
    }

    if (tableau[0][0] == O && tableau[1][0] == O && tableau[2][0] == O) {
        return 2;
    }
    if (tableau[0][1] == O && tableau[1][1] == O && tableau[2][1] == O) {
        return 2;
    }
    if (tableau[0][2] == O && tableau[1][2] == O && tableau[2][2] == O) {
        return 2;
    }

    // lignes
    if (tableau[0][0] == X && tableau[0][1] == X && tableau[0][2] == X) {
        return 1;
    }
    if (tableau[1][0] == X && tableau[1][1] == X && tableau[1][2] == X) {
        return 1;
    }
    if (tableau[2][0] == X && tableau[2][1] == X && tableau[2][2] == X) {
        return 1;
    }

    if (tableau[0][0] == O && tableau[0][1] == O && tableau[0][2] == O) {
        return 2;
    }
    if (tableau[1][0] == O && tableau[1][1] == O && tableau[1][2] == O) {
        return 2;
    }
    if (tableau[2][0] == O && tableau[2][1] == O && tableau[2][2] == O) {
        return 2;
    }

    // diagonales
    if (tableau[0][0] == X && tableau[1][1] == X && tableau[2][2] == X) {
        return 1;
    }
    if (tableau[0][2] == X && tableau[1][1] == X && tableau[2][0] == X) {
        return 1;
    }

    if (tableau[0][0] == O && tableau[1][1] == O && tableau[2][2] == O) {
        return 2;
    }
    if (tableau[0][2] == O && tableau[1][1] == O && tableau[2][0] == O) {
        return 2;
    }

    return 0;
}

void PlayMulti() {
    initTableau(); // on prépare les cases
    int coups = 0 ;
    int joueur = 1;
    int ligne ;
    int col ;

    printf("\n--- Début d'une partie multijoueur ---\n");

    while (1) {
        afficherTableau(); // on affiche le tableau actuel

        // Indique quel joueur joue
        printf("Joueur %d (%c) - a vous : entrez colonne espace ligne (de 0 a 2) :   ",
               joueur, joueur == 1 ? X : O);// là si joueur est = 1 %c sera X sinon ca sera O comme un if   else

        if (scanf("%i %i", &col, &ligne) != 2) { // Verif des deux entiers colonne puis ligne
            printf("Entrée invalide. Veuillez taper deux chiffres (colonne ligne).\n");
            continue; // on reprend au debut du while
        }
        if (col < 0 || col > 2 || ligne < 0 || ligne > 2) { // verif des de la valeur des entiers
            printf("Coordonnées hors limites. Utilisez des valeurs entre 0 et 2.\n");
            continue;
        }
        if (tableau[ligne][col] != ' ') { // on voit si la case est deja occupée
            printf("Case deja occupee, choisissez une autre case.\n");
            continue;
        }

        // On place le symbole
        if (joueur == 1) {
            tableau[ligne][col] = X ;
        }
        else {                                // si c'est le j1 on place X si c'est l'autre on place O
            tableau[ligne][col] = O ;
        }

        coups++; // on vient de placer donc on ajoute un coup

        // Vérif de victoire
        resultat = wincondition();
        if (resultat == 1 || resultat == 2) {
            afficherTableau();// affiche le tableau final
            printf("Le joueur %i a gagne !! \n",resultat);
            break;
        }

        if (coups == 9) { // si pas de victoire + coup = 9 c'est égalité
            afficherTableau();  // vu que la win condition a été testée pour le 9e coup
            printf("egalite !\n\n");
            break;
        }

        // Change de joueur entre chaque coup
        if (joueur == 1) {
            joueur = 2 ;
        }
        else {
            joueur = 1 ;
        }
    }
    printf("=================\n");
    printf("Fin de la partie\n");
    printf("=================\n\n");
}

int main() {
    PlayMulti();
    return 0;
}
