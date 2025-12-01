#include <stdio.h>

// --- Voici les variables globales qui gèrent les paramètres du jeu ---
int difficulte = 1;
char symbole_joueur = 'X';

// --- Voici quelques exemples de fonctions pour vous donner une idée de leur fonctionnement ---
void afficher_menu_principal();
void afficher_parametres();
void choisir_difficulte();
void choisir_symbole();
void afficher_credits();
void effacer_ecran(); // On a gardé la structure, mais on a vidé le contenu
void vider_buffer();

// --- Voici une petite fonction bien pratique pour vider le buffer d'entrée ---
void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Je viens de désactiver la fonction pour effacer l'écran ---
void effacer_ecran() {
    // Laissez-le vide, ou ajoutez des sauts de ligne si vous en avez besoin
    // Pour le débogage, on peut laisser ce champ vide

}

// --- Menu Principal ---
void afficher_menu_principal() {
    int choix;

    do {
        // effacer_ecran();
        printf("\n-----------------------------------\n"); //Pour rendre le texte plus clair \n,
        printf("1. Parametres\n");
        printf("2. Quitter\n");
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
                afficher_parametres();
                break;
            case 2:
                printf("\nAu revoir ! Merci d'avoir configurer le jeu.\n");
                break;
            default:
                printf("\nChoix invalide. Appuyez sur ENTREE pour continuer...\n");
                getchar();
        }

    } while (choix != 2);
}

// --- Menu Paramètres ---
void afficher_parametres() {
    int choix;
    do {
        // effacer_ecran();
        printf("\n--- Parametres  ---\n");
        printf(" 1. Difficulte du Robot (Actuelle : %s)\n", difficulte == 1 ? "Facile" : difficulte == 2 ? "Moyen" : "Difficile");
        printf(" 2. Choisir ton symbole (Actuel : %c)\n", symbole_joueur);
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
                choisir_difficulte();
                break;
            case 2:
                choisir_symbole();
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
void choisir_difficulte() {
    int choix;
    do {
        // effacer_ecran();
        printf("\n--- Difficulte du Robot ---\n");
        printf(" Choisissez le niveau de l'IA :\n");
        printf(" 1. Facile %s\n", difficulte == 1 ? "<- Actuel" : "");
        printf(" 2. Moyen %s\n", difficulte == 2 ? "<- Actuel" : "");
        printf(" 3. Difficile %s\n", difficulte == 3 ? "<- Actuel" : "");
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
                difficulte = choix;
                printf("\nDifficulte regle. Appuyez sur ENTREE pour revenir aux Parametres...\n");
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
void choisir_symbole() {
    char choix_char;
    do {
        // effacer_ecran();
        printf("\n--- Choisir votre Symbole ---\n");
        printf(" Votre symbole actuel est : %c\n", symbole_joueur);
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
            symbole_joueur = choix_char;
            printf("\nVotre symbole a ete change pour '%c'. Appuyez sur ENTREE pour revenir aux Parametres...\n", symbole_joueur);
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

// --- Sous-menu Credits ---
void afficher_credits() {
    // effacer_ecran();
    printf("\n--- Credits ---\n");
    printf(" Developpeur : \n - Valetnin PARADE\n - Maxime NOEL \n - Antoine Talleu\n - Antoine\n");
    printf(" Annee de creation : 2025\n");
    printf("------------------------\n");
    printf("Appuyez sur ENTREE pour revenir aux Parametres...\n");
    getchar();
}

int main() {
    afficher_menu_principal();
    return 0;
}