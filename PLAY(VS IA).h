
#ifndef MAIN_PLAY_VS_IA_H
#define MAIN_PLAY_VS_IA_H

#endif //MAIN_PLAY_VS_IA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// def locale de la structure
typedef struct {
    char name[20];
    int wins;
    int losses;
    int draws;
} PlayerStats;

// Initialise la grille locale
void initTableau_IA(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Afficher la grille locale
void afficherTableau_IA(char board[3][3]) {
    printf("\n   0    1    2 \n");
    printf("  -------------\n");
    for (int i = 0; i < 3; i++) {
        if (i != 0) printf("  ----+---+----\n");
        printf("%i ", i);
        for (int j = 0; j < 3; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("  -------------\n\n");
}

// vérifier la victoire la grille locale
// soit : 0 (rien), 1 (victoire X), 2 (victoire O), 3 (match nul/plein)
int checkWin_IA(char board[3][3]) {
    // Lignes ou Colonnes
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return (board[i][0] == 'X') ? 1 : 2;
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return (board[0][i] == 'X') ? 1 : 2;
    }
    // diagonale
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return (board[0][0] == 'X') ? 1 : 2;
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return (board[0][2] == 'X') ? 1 : 2;

    return 0;
}

// Vérifie si la grille est pleine (Match Nul)
int isFull_IA(char board[3][3]) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(board[i][j] == ' ') return 0; // Il reste de la place
        }
    }
    return 1; // Plein
}

// IA

int compter_direction(char board[3][3], int lig, int col, int d_l, int d_c, char symbole) {
    int compteur = 0;

    for(int k=1; k<3; k++) {
        int testligne = lig + (d_l *k);
        int testcolue = col + (d_c *k);

    if (testligne<=2 && testligne>=0 && testcolue<=2 && testcolue>=0) {
        if (board[testligne][testcolue] == symbole) compteur++;
    }
        else {
            break;
        }

    }

    for (int k=0; k<3; k++) {
        int testligne = lig - (d_l * k);
        int testcol = col - (d_c * k);

        if (testligne<=2 && testligne>=0 && testcol>=0 && testcol<=2) {
            if (board[testligne][testcol] == symbole) compteur++;
        }
        else {
            break;
        }
    }
    return compteur;
}


void calcul_coup_IA(char board[3][3], int *ligne, int *col) {

    //---------IA difficile:


    int dl[] = { 0, 1, 1,  1 };
    int dc[] = { 1, 0, 1, -1 };


    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (board[i][j] == ' ') {
                char symboleTest[] = {'O', 'X'};

                for (int s = 0; s < 2; s++) {
                    char symbole = symboleTest[s];

                    // On teste les 4 directions grâce aux vecteurs
                    for (int axe = 0; axe < 4; axe++) {
                        // Si j'ai 2 voisins alignés dans cet axe, ça veut dire qu'en jouant là, j'en aurai 3 !
                        if (compter_direction(board, i, j, dl[axe], dc[axe], symbole) == 2) {
                            *ligne = i;
                            *col = j;
                            return; // On joue et on gagne/bloque !
                        }
                    }
                }
            }
        }
    }











    //------IA moyenne :

    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};


    for (int x = 0; x<3;x++) {
        for (int y = 0; y<3;y++) {
            if(board[x][y] == 'X') {
                for (int i =0; i<4; i++) {
                    int voisinx = x +dx[i] ;
                    int voisiny =y +dy[i] ;

                    if (voisinx >=0 && voisinx <= 2 && voisiny >=0 && voisiny <=2 && board[voisinx][voisiny] == ' ') {

                        *ligne = voisinx;
                        *col = voisiny;
                        return ;
                    }

                }



            }
        }}

    //--------IA facile : cherche une case vide au hasard
    do {
        *ligne = rand() % 3;
        *col = rand() % 3;
    } while (board[*ligne][*col] != ' ');




}




// Fonction principale appelée par main

void start_game_vs_ia(PlayerStats stats[]) {
    // tableau local
    char board[3][3];
    int tour = 0;
    int victoire = 0;

    // Initialisation
    initTableau_IA(board);
    srand(time(NULL));

    printf("\n=== MODE JEU CONTRE L'IA ===\n");
    printf("Vous etes les X, l'IA joue les O.\n");

    while (victoire == 0) {
        afficherTableau_IA(board);

        if (tour % 2 == 0) {
            // (JOUEUR)
            int l, c;
            int valide = 0;

            do {
                printf("Votre tour (Ligne Colonne) : ");
                if (scanf("%d %d", &c, &l) != 2) { // Inversion ou pas selon ta logique, ici Col Ligne
                    while(getchar() != '\n'); // Vider buffer si erreur
                    continue;
                }

                // Vérification validité du coup [cite: 73, 74]
                if (l >= 0 && l <= 2 && c >= 0 && c <= 2 && board[l][c] == ' ') {
                    board[l][c] = 'X';
                    valide = 1;
                } else {
                    printf("Coup invalide ! Reessayez.\n");
                }
            } while (!valide);

        } else {
            // --- C'EST A L'IA ---
            printf("L'IA reflechit...\n");
            int l, c;
            calcul_coup_IA(board, &l, &c);
            board[l][c] = 'O';
            printf("L'IA a joue en %d %d\n", c, l);
        }

        // Vérification fin de partie
        victoire = checkWin_IA(board);
        if (victoire == 0 && isFull_IA(board)) {
            victoire = 3; // Code pour match nul
        }

        tour++;
    }

    afficherTableau_IA(board); // Affichage final

    // Gestion des résultats
    if (victoire == 1) {
        printf("VICTOIRE ! Bravo !\n");
        // stats[0].wins++; (Décommente quand tu voudras gérer les stats)
    } else if (victoire == 2) {
        printf("DEFAITE... L'IA a gagne.\n");
        // stats[2].wins++;
    } else {
        printf("MATCH NUL !\n");
        // stats[0].draws++;
    }

    printf("Appuyez sur une touche pour revenir au menu...\n");
    getchar(); getchar();
}
