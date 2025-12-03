#include <stdio.h>

// --- Déclarations des fonctions ---
void afficher_menu_principal(int *difficulte_ptr, char *symbole_joueur_ptr);
void afficher_parametres(int *difficulte_ptr, char *symbole_joueur_ptr);
void choisir_difficulte(int *difficulte_ptr);
void choisir_symbole(char *symbole_joueur_ptr);
void afficher_credits();
void effacer_ecran();
void vider_buffer();

// --- Fonction bien pratique pour vider le buffer d'entrée ---
void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Fonction désactivée pour effacer l'écran ---
void effacer_ecran() {
    // Laisser vide
}

// --- Menu Principal ---
void afficher_menu_principal(int *difficulte_ptr, char *symbole_joueur_ptr) {
    int choix;

    do {
        // effacer_ecran();
        printf("\n-----------------------------------\n");
        printf("1. Parametres\n");
        printf("2. Quitter\n"); // Ajout de l'option "Quitter" pour sortir
        printf("-----------------------------------\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {
            vider_buffer();
            choix = 0;
        } else {
            vider_buffer();
        }

        switch (choix) {
            case 1:
                // Passage des pointeurs aux paramètres
                afficher_parametres(difficulte_ptr, symbole_joueur_ptr);
                break;
            case 2:
                printf("\nAu revoir ! Merci d'avoir configure le jeu.\n");
                break;
            default:
                printf("\nChoix invalide. Appuyez sur ENTREE pour continuer...\n");
                getchar();
        }

    } while (choix != 2);
}

// --- Menu Paramètres ---
void afficher_parametres(int *difficulte_ptr, char *symbole_joueur_ptr) {
    int choix;
    // On utilise *difficulte_ptr et *symbole_joueur_ptr pour lire les valeurs
    char symbole_actuel = *symbole_joueur_ptr;
    int difficulte_actuelle = *difficulte_ptr;

    do {
        // effacer_ecran();
        printf("\n--- Parametres  ---\n");
        printf(" 1. Difficulte du Robot (Actuelle : %s)\n", difficulte_actuelle == 1 ? "Facile" : difficulte_actuelle == 2 ? "Moyen" : "Difficile");
        printf(" 2. Choisir ton symbole (Actuel : %c)\n", symbole_actuel);
        printf(" 3. Credits \n");
        printf(" 4. Retour au Menu Principal\n");
        printf("-------------------------\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {
            vider_buffer();
            choix = 0;
        } else {
            vider_buffer();
        }

        switch (choix) {
            case 1:
                // Passage du pointeur pour modification
                choisir_difficulte(difficulte_ptr);
                // Mise à jour de la difficulté locale pour affichage
                difficulte_actuelle = *difficulte_ptr;
                break;
            case 2:
                // Passage du pointeur pour modification
                choisir_symbole(symbole_joueur_ptr);
                // Mise à jour du symbole local pour affichage
                symbole_actuel = *symbole_joueur_ptr;
                break;
            case 3:
                afficher_credits();
                break;
            case 4:
                // Sort de la boucle, retour au Menu Principal
                break;
            default:
                printf("\nChoix invalide. Appuyez sur ENTREE pour continuer...\n");
                getchar();
        }
    } while (choix != 4);
}

// --- Sous-menu Difficulté ---
void choisir_difficulte(int *difficulte_ptr) {
    int choix;
    // On utilise *difficulte_ptr pour lire la valeur actuelle
    int difficulte_actuelle = *difficulte_ptr;

    do {
        // effacer_ecran();
        printf("\n--- Difficulte du Robot ---\n");
        printf(" Choisissez le niveau de l'IA :\n");
        printf(" 1. Facile %s\n", difficulte_actuelle == 1 ? "<- Actuel" : "");
        printf(" 2. Moyen %s\n", difficulte_actuelle == 2 ? "<- Actuel" : "");
        printf(" 3. Difficile %s\n", difficulte_actuelle == 3 ? "<- Actuel" : "");
        printf(" 4. Annuler et Retour\n");
        printf("-------------------------------\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {
            vider_buffer();
            choix = 0;
        } else {
            vider_buffer();
        }

        switch (choix) {
            case 1:
            case 2:
            case 3:
                // On modifie la valeur pointée (la variable dans main)
                *difficulte_ptr = choix;
                printf("\nDifficulte reglee. Appuyez sur ENTREE pour revenir aux Parametres...\n");
                getchar();
                choix = 4;
                break;
            case 4:
                break;
            default:
                printf("\nChoix invalide. Appuyez sur ENTREE pour continuer...\n");
                getchar();
        }
    } while (choix != 4);
}

// --- Sous-menu Symbole ---
void choisir_symbole(char *symbole_joueur_ptr) {
    char choix_char;
    // On utilise *symbole_joueur_ptr pour lire la valeur actuelle
    char symbole_actuel = *symbole_joueur_ptr;

    do {
        // effacer_ecran();
        printf("\n--- Choisir votre Symbole ---\n");
        printf(" Votre symbole actuel est : %c\n", symbole_actuel);
        printf(" Entrez 'X' ou 'O' (ou 'A' pour Annuler) : ");

        if (scanf(" %c", &choix_char) != 1) {
            vider_buffer();
            choix_char = ' ';
        } else {
            vider_buffer();
        }

        if (choix_char >= 'a' && choix_char <= 'z') {
            choix_char = choix_char - 'a' + 'A';
        }

        if (choix_char == 'X' || choix_char == 'O') {
            // On modifie la valeur pointée (la variable dans main)
            *symbole_joueur_ptr = choix_char;
            printf("\nVotre symbole a ete change pour '%c'. Appuyez sur ENTREE pour revenir aux Parametres...\n", *symbole_joueur_ptr);
            getchar();
            break;
        } else if (choix_char == 'A') {
            break;
        } else {
            printf("\nSymbole invalide. Appuyez sur ENTREE pour continuer...\n");
            getchar();
        }
    } while (1);
}

// ---- Sous-menu Credits ----
void afficher_credits() {
    // effacer_ecran();
    printf("\n--- Credits ---\n");
    printf(" Developpeur : \n - Valetnin PARADE\n - Maxime NOEL \n - Antoine Talleu\n - Antoine SEKHI\n");
    printf(" Annee de creation : 2025\n");
    printf("------------------------\n");
    printf("Appuyez sur ENTREE pour revenir aux Parametres...\n");
    getchar();
}

int main() {
    // Les variables sont maintenant locales à main()
    int difficulte = 1;
    char symbole_joueur = 'X';

    // On passe les adresses (pointeurs) des variables
    afficher_menu_principal(&difficulte, &symbole_joueur);

    // On peut vérifier l'état final des variables ici si besoin
    /*
    printf("\n--- Etat Final ---\n");
    printf("Difficulte: %d\n", difficulte);
    printf("Symbole: %c\n", symbole_joueur);
    */

    return 0;
}