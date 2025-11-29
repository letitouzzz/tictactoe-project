#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STATS_FILE "morpion_stats.txt"
#define P1_INDEX 0
#define P2_INDEX 1
#define AI_INDEX 2

//DECLARATION DE L'ENSSEMBLE DES VARIABLES UTILISES
typedef struct {
    char name[20];
    int wins;
    int losses;
    int draws; // Matchs nuls
} PlayerStats;

//ON TEST S'IL EXISTE DEJA UN FICHIER CONTENANT LES STATS SUR CE PC
void save_stats(PlayerStats stats[3]) {
    // Ouvre le fichier
    FILE *file = fopen(STATS_FILE, "w");

    if (file == NULL) {
        perror("Erreur: Impossible d'ouvrir le fichier de stats en écriture");
        return;
    }
    for (int i = 0; i < 3; i++) {
        fprintf(file, "%s %d %d %d\n",
                stats[i].name,
                stats[i].wins,
                stats[i].losses,
                stats[i].draws);
    }

    fclose(file);
}

//ON CHARGE LES STAT DEPUIS LE FICHIER, S'IL N'EXISTE PAS, ON LE CREE
void load_or_initialize_stats(PlayerStats stats[3]) {
    // Ouvre le fichier en mode "read" (lecture)
    FILE *file = fopen(STATS_FILE, "r");

    // CAS 1 : Le fichier n'existe pas (ou erreur de lecture)
    if (file == NULL) {
        printf("Fichier de stats non trouve. Creation d'un nouveau fichier...\n");

        strcpy(stats[P1_INDEX].name, "Joueur_1");
        stats[P1_INDEX].wins = 0;
        stats[P1_INDEX].losses = 0;
        stats[P1_INDEX].draws = 0;

        strcpy(stats[P2_INDEX].name, "Joueur_2");
        stats[P2_INDEX].wins = 0;
        stats[P2_INDEX].losses = 0;
        stats[P2_INDEX].draws = 0;

        strcpy(stats[AI_INDEX].name, "IA_VALENTIN");
        stats[AI_INDEX].wins = 0;
        stats[AI_INDEX].losses = 0;
        stats[AI_INDEX].draws = 0;

        save_stats(stats);

    }
    // CAS 2 : Le fichier existe, on le lit
    else {
        for (int i = 0; i < 3; i++) {
            // Lecture formatée du fichier
            if (fscanf(file, "%s %d %d %d",
                       stats[i].name,
                       &stats[i].wins,
                       &stats[i].losses,
                       &stats[i].draws) != 4) {
                printf("Erreur: Fichier de stats corrompu. Réinitialisation.\n");
                fclose(file);

                load_or_initialize_stats(stats);
                return;
                       }
        }
        fclose(file);
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main() {

    PlayerStats all_stats[3];
    load_or_initialize_stats(all_stats);

    int choix_menu = 0;

    printf("==============================\n");
    printf("           MORPION            \n");
    printf("==============================\n");
    printf("\n - 1. JOUER (1 VS 1)\n");
    printf("\n - 2. JOUER (VS IA)\n");
    printf("\n - 3. STATISTIQUES \n");
    printf("\n - 4. PARAMETRES \n");
    printf("\n - 5. QUITTER\n");
    printf("==============================\n");
    printf("Votre choix (1, 2, 3, 4 ou 5) :");
    scanf("%d ", &choix_menu);

    if (scanf("%d", &choix_menu) != 1) {
        // Si l'utilisateur tape "abc", scanf échoue (!= 1)
        choix_menu = 0; // On met une valeur invalide (pour aller au "default:")
    }

    // 2. On nettoie le buffer après un scanf
    clear_input_buffer();

    /*
     * =============================================
     */

    // 3. Le switch gère tous les cas
    switch (choix_menu) {
        case 1:
            //PlayMulti(all_stats); //<--- RETIRER LES DEUX '//' LORSQUE VOUS AUREZ FINI AVEC VOTRE CODE
            break;

        case 2:
            //start_game_vs_ia(all_stats); <--- RETIRER LES DEUX '//' LORSQUE VOUS AUREZ FINI AVEC VOTRE CODE
            break;

        case 3:
            // ... (code pour afficher les stats) ...
            break;

        case 4:
            //show_settings();  <--- RETIRER LES DEUX '//' LORSQUE VOUS AUREZ FINI AVEC VOTRE CODE
            break;

        case 5:
            printf("\nMerci d'avoir joue. Au revoir !\n");
            break;

        default: // C'est ici qu'on gère "7", "8", "0", ou les lettres
            printf("\nChoix invalide ! Veuillez taper un numero entre 1 et 5.\n");
            printf("Appuyez sur Entree pour reessayer...");
            getchar();
            break;
    }

}





