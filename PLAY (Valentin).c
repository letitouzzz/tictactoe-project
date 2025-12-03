#include <stdio.h>

void initTableau(char tableau[3][3]) { // là on met en place les caractères vides
    for (int ligne = 0; ligne < 3; ligne++) { //  dans chaque ligne
        for (int col = 0; col < 3; col++) { // 3 caractères vides qui pourront êtres remplacés par X ou O
            tableau[ligne][col] = ' ';
        }
    }
}

void afficherTableau(char tableau[3][3]) {

    printf("\n");
    printf("   0    1    2 \n");
    printf("  -------------\n"); // première ligne du tableau

    for (int ligne = 0; ligne < 3; ligne++) { // ligne = horizontal

        if (ligne!= 0) {
            printf("  ----+---+----\n"); // différent de 0 donc ça sera 1 et 2 pour les deux étages du milieu
        }

        printf("%i ",ligne);// indices verticals

        for (int col = 0; col < 3; col++) { // colonne = vertical

            printf("| %c ",tableau[ligne][col]); // donc pour chaques lignes horizontales
        }
        printf("|\n"); // à la fin de chaque ligne pour fermer le tableau
    }
    printf("  -------------\n\n"); // dernière ligne
}

int wincondition(char tableau[3][3], char X, char O) {

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

    char tableau[3][3];
    char X = 'X';
    char O = 'O';
    int resultat = 0;

    initTableau(tableau); // on prépare les cases
    int coups = 0 ;
    int joueur = 1;
    int ligne ;
    int col ;

    printf("\n--- Début d'une partie multijoueur ---\n");

    while (1) {
        afficherTableau(tableau); // on affiche le tableau actuel

        // Indique quel joueur joue
        printf("Joueur %d (%c) - a vous : entrez colonne espace ligne (de 0 a 2) :   ",
               joueur, joueur == 1 ? X : O);

        if (scanf("%i %i", &col, &ligne) != 2) {
            printf("Entrée invalide. Veuillez taper deux chiffres (colonne ligne).\n");
            while (getchar() != '\n'){}
            continue;
        }
        if (col < 0 || col > 2 || ligne < 0 || ligne > 2) {
            printf("Coordonnées hors limites. Utilisez des valeurs entre 0 et 2.\n");
            continue;
        }
        if (tableau[ligne][col] != ' ') {
            printf("Case deja occupee, choisissez une autre case.\n");
            continue;
        }

        // On place le symbole
        if (joueur == 1) {
            tableau[ligne][col] = X ;
        }
        else {
            tableau[ligne][col] = O ;
        }

        coups++;

        // Vérif de victoire
        resultat = wincondition(tableau, X, O);
        if (resultat == 1 || resultat == 2) {
            afficherTableau(tableau);
            printf("Le joueur %i a gagne !! \n\n",resultat);
            break;
        }

        if (coups == 9) {
            afficherTableau(tableau);
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

//