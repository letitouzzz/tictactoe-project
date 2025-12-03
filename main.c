#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FICHIER_STATS "morpion_stats.txt"

#define ID_J1 0
#define ID_J2 1
#define ID_IA 2

#define COL_VICTOIRES 0
#define COL_DEFAITES 1
#define COL_NULS 2


void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


/*  On passe deux tableaux séparés :
 * 1. noms[3][20] : Contient les 3 noms
 * 2. stats[3][3] : Contient les chiffres (3 joueurs x 3 types de stats)
 */
void sauvegarder_stats(char noms[3][20], int stats[3][3]) {
    FILE *fichier = fopen(FICHIER_STATS, "w");

    if (fichier == NULL) {
        perror("Erreur d'ouverture fichier");
        return;
    }

    // On parcourt les 3 joueurs (0, 1 et 2)
    for (int i = 0; i < 3; i++) {
        fprintf(fichier, "%s %d %d %d\n",
                noms[i],              // Le nom
                stats[i][0],          // Victoires
                stats[i][1],          // Défaites
                stats[i][2]);         // Nuls
    }
    fclose(fichier);
}

void charger_ou_init_stats(char noms[3][20], int stats[3][3]) {
    FILE *fichier = fopen(FICHIER_STATS, "r");

    if (fichier == NULL) {
        printf("Creation du fichier de stats...\n");

        // Initialisation des Noms
        strcpy(noms[ID_J1], "Joueur_1");
        strcpy(noms[ID_J2], "Joueur_2");
        strcpy(noms[ID_IA], "IA_VALENTIN");

        // Initialisation des Stats à 0
        for(int i=0; i<3; i++) {
            stats[i][COL_VICTOIRES] = 0;
            stats[i][COL_DEFAITES] = 0;
            stats[i][COL_NULS] = 0;
        }

        sauvegarder_stats(noms, stats);
    }
    else {
        for (int i = 0; i < 3; i++) {
            // On lit : Nom Victoires Defaites Nuls
            if (fscanf(fichier, "%s %d %d %d",
                       noms[i],
                       &stats[i][COL_VICTOIRES],
                       &stats[i][COL_DEFAITES],
                       &stats[i][COL_NULS]) != 4) {

                printf("Fichier corrompu. Reset.\n");
                fclose(fichier);
                // Appel récursif pour recréer proprement
                charger_ou_init_stats(noms, stats);
                return;
            }
        }
        fclose(fichier);
    }
}

// Fonction pour mettre à jour les scores à la fin d'une partie
void enregistrer_victoire(char noms[3][20], int stats[3][3], int id_gagnant, int id_perdant) {
    if (id_gagnant == -1) {
        // Match nul : On ajoute 1 dans la colonne 2 pour les deux
        stats[id_perdant][COL_NULS]++;
    } else {
        // Victoire : Colonne 0 pour le gagnant
        stats[id_gagnant][COL_VICTOIRES]++;
        // Défaite : Colonne 1 pour le perdant
        stats[id_perdant][COL_DEFAITES]++;
    }
    // Sauvegarde
    sauvegarder_stats(noms, stats);
}

void afficher_stats(char noms[3][20], int stats[3][3]) {
    printf("\n--- STATISTIQUES ---\n");
    printf("| %-12s | Win | Def | Nul |\n", "Nom");
    printf("|--------------|-----|-----|-----|\n");

    for(int i = 0; i < 3; i++) {
        printf("| %-12s | %-3d | %-3d | %-3d |\n",
               noms[i],
               stats[i][COL_VICTOIRES],
               stats[i][COL_DEFAITES],
               stats[i][COL_NULS]);
    }
    printf("----------------------------------\n");
    printf("Entree pour continuer...");
    vider_buffer();
    getchar();
}


int main() {
    // Tableau pour les noms des 3 joueurs (max 20 lettres)
    char noms_joueurs[3][20];
    // Tableau 3x3 pour les stats (Lignes=Joueurs, Cols=V/D/N)
    int stats_joueurs[3][3];

    charger_ou_init_stats(noms_joueurs, stats_joueurs);

    int choix = 0;

    do {
        system("cls");

        printf("\n=== MENU MORPION ===\n");
        printf(" 1. Jouer (1 vs 1)\n");
        printf(" 2. Jouer (1 vs IA)\n");
        printf(" 3. Stats\n");
        printf(" 4. Parametres\n");
        printf(" 5. Quitter\n");
        printf("Choix : ");

        if (scanf("%d", &choix) != 1) choix = 0;
        vider_buffer();

        switch (choix) {
            case 1:
                printf("Lancement 1v1...\n");
                // A la fin de ta partie, tu appelleras :
                // enregistrer_victoire(noms_joueurs, stats_joueurs, ID_J1, ID_J2);
                getchar();
                break;

            case 2:
                printf("Lancement IA...\n");
                // A la fin de ta partie :
                // enregistrer_victoire(noms_joueurs, stats_joueurs, ID_IA, ID_J1);
                getchar();
                break;

            case 3:
                afficher_stats(noms_joueurs, stats_joueurs);
                break;

            case 4:
                //Affichage menu parametres
                break;

            case 5:
                printf("BYE BYE !!!!!");
                break;

            default:
                printf("Choix incorrect.\n");
                getchar();
                break;
        }

    } while (choix != 5);

    return 0;
}