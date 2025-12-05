#include <stdio.h>
#include <stdlib.h>//pour malloc et free
#include <windows.h>// couleurs


long nbmoves = 0;
int n;
int **piles; // tableau de 3 colonnes et chaque element est un pointeur vers un tableau dynamique d'entiers les 3 piquets
int hauteur[3] = {0, 0, 0}; // hauteur de chaque pile(piquets)


//donner la couleur au texte dans la console
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Affichage des piquets et disques
 void afficher() {
    for (int level = n - 1; level >= 0; level--) {//parcourire chaque niveau du haut vers le bas
        for (int p = 0; p < 3; p++) {//Pour chaque level on parcourt les 3 piquets p = 0,1,2 (A,B,C)

            if (level < hauteur[p]) { //existe-t-il un disque à ce niveau sur la pile p ?
                int disk = piles[p][level]; /*disk = numero du disque (1 = plus petit, n = plus grand).*/

                setColor((disk % 15) + 1); //(disk-1)%7 pour cycler si >7
                int largeur = disk;//largeur disque=son numero

                // espaces gauche
                for (int s = 0; s < (n - largeur); s++) printf(" ");

                // disque gauche
               // activer la couleur pour tout ce qui est apres  jusqu’au prochain RESET ou une autre coleur est donnee
                setColor((disk % 15) + 1);
                 for (int c = 0; c < largeur; c++) printf("~");

                // tige centrale
                setColor(7);
                printf("|");

                // disque droite
                setColor((disk % 15) + 1);
                for (int c = 0; c < largeur; c++) printf("~");

                // revenir normal
                setColor(7);

                // espaces droite
                for (int s = 0; s < (n - largeur); s++) printf(" ");

            } else {
                // tige vide
                for (int s = 0; s < n; s++) printf(" ");
                setColor(7);
                printf("|");
                setColor(7);

                for (int s = 0; s < n; s++) printf(" ");
            }

            printf("   ");
        }
        printf("\n");



    }

    // Affichage des noms des piquets alignés sous chaque tige
    for (int p = 0; p < 3; p++) {
        for (int s = 0; s < n; s++) printf(" "); // espaces avant le nom
        printf("%c", 'A' + p); // A, B, C
        for (int s = 0; s < n; s++) printf(" "); // espaces après le nom
        printf("   "); // espace entre les piles
    }
    printf("\n");
}

//ajouter un disque disk sur le haut de la pile.
void ajouter(int pile, int disk) {
    piles[pile][hauteur[pile]] = disk;
    hauteur[pile]++;
}
//retirer et retourner le disque du haut de la pile pile.
int retirer(int pile) {
    hauteur[pile]--;
    return piles[pile][hauteur[pile]];
}

// Mouvement disque + affichage
void deplacer(int from, int to) {
    int disk = retirer(from);
    ajouter(to, disk);
    afficher();
}

// Hanoi récursif
void hanoi(int nb, int A, int C, int B) {
    if (nb > 0) {
        hanoi(nb - 1, A, B, C);
        deplacer(A, C);
        nbmoves++;
        hanoi(nb - 1, B, C, A);
    }
}

// Programme principal
int main() {
    do {
        printf("Entrez le nombre de disques (0 pour quitter) : ");
         // <-- utilise la variable globale n
        if(scanf("%d", &n)!=1){
            printf("entree invalide");
            return 0;
        }
        if (n == 0) {return 0;};
        if (n < 0) {
            printf("Veuillez entrer un nombre positif.\n");
            continue;
        }

        // Libérer l'ancienne mémoire si nécessaire
        if (piles != NULL) {
            for (int i = 0; i < 3; i++) free(piles[i]);
            free(piles);
        }

        // Allocation dynamique pour le nouveau n
        piles = malloc(3 * sizeof(int*));
        for (int i = 0; i < 3; i++) {
            piles[i] = malloc(n * sizeof(int));
            hauteur[i] = 0; // réinitialiser la hauteur
        }

        // Remplir la pile A
        for (int i = n; i >= 1; i--) ajouter(0, i);

        nbmoves = 0;
        afficher();
        
        hanoi(n, 0, 2, 1);
        
        printf("Nombre total de mouvements : %ld\n", nbmoves);
        printf("---------------------------------------------\n");

    } while (n != 0);
    return 0;
}    
