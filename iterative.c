#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Structure représentant une pile (stack) qui sert de tour.
// Chaque tour peut contenir jusqu'à 50 disques.
// top représente l'indice du disque au sommet.
typedef struct {
    int data[50];  // Tableau contenant les disques empilés
    int top;       // Index du dernier élément (sommet)
} Stack;


// Fonction create()
// Alloue dynamiquement une pile et initialise son sommet à -1,
// ce qui signifie que la pile est vide.
Stack* create() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

// Fonction push()
// Ajoute un disque au sommet de la pile.
// ++s->top augmente d'abord l'indice puis place la valeur.
void push(Stack* s, int disk) {
    s->data[++s->top] = disk;
}

// Fonction pop()
// Retire et retourne le disque au sommet de la pile.
// s->top-- retourne la valeur puis décrémente l'indice.
int pop(Stack* s) {
    return s->data[s->top--];
}

// Fonction peek()
// Permet de regarder le disque au sommet sans le retirer.
// Si la pile est vide (top == -1), on retourne 999,
// un nombre très grand pour éviter qu'une tour vide soit
// considérée comme ayant un "disque plus petit".
int peek(Stack* s) {
    return (s->top == -1) ? 999 : s->data[s->top];
}

// Fonction initTowers()
// Remplit la tour A avec les disques allant de n → 1.
// Le disque n (le plus grand) est en bas,
// le disque 1 (le plus petit) est au sommet.
void initTowers(Stack* A, int n) {
    for (int d = n; d >= 1; d--) {
        push(A, d);
    }
}

// Fonction moveBetween()
// Réalise un mouvement légal entre deux tours X et Y.
// Cette fonction compare les deux disques au sommet
// et effectue automatiquement le mouvement correct.
// Elle affiche aussi le mouvement sous forme :
//       Mouvement 12 : A -> C
void moveBetween(Stack* X, Stack* Y, char nameX, char nameY, long long moveNum) {

    int topX = peek(X);  // disque au sommet de la tour X
    int topY = peek(Y);  // disque au sommet de la tour Y

    // Si la tour X a le plus petit disque, on déplace X → Y
    if (topX < topY) {
        push(Y, pop(X));
        printf("Mouvement %lld : %c -> %c\n", moveNum, nameX, nameY);
    }

    // Sinon, la tour Y a le plus petit disque : on déplace Y → X
    else {
        push(X, pop(Y));
        printf("Mouvement %lld : %c -> %c\n", moveNum, nameY, nameX);
    }
}

int main() {

    int n;
    int entree;
   do{
    printf("Entrer le nombre de disques (0 pour quitter): ");
    entree=scanf("%d", &n);

if(entree!=1){   
    printf("Entree invalide !\n");
    return 0;     
    }
if (n == 0) {
        printf("Programme terminer.\n");
        return 0;
        }

if (n < 0) {
        printf("Veuillez entrer un nombre positif.\n");
    }
else{
    // Création des trois tours A, B et C.
    // A est la tour de départ (initialisee avec initTowers)
    // B est la tour auxiliaire
    // C est la tour destination

    Stack *A = create(), *B = create(), *C = create();
    initTowers(A, n);


    // Formule mathématique des Hanoi :
    //   Nombre minimal de mouvements = 2^n - 1
    // Ici 1LL << n calcule 2^n en long long.
    long long moves = (1LL << n) - 1;

    // printf("\nNombre total de mouvements = %lld\n", moves);
    printf("------------- DEBUT DES MOUVEMENTS -------------\n");

    // On démarre le chronomètre pour mesurer les performances
    clock_t start = clock();

    // Algorithme itératif des tours de Hanoi :
    //
    // Il existe un pattern très précis pour déplacer les disques.
    // il dépend de la PARITÉ du nombre de disques.
    //
    // Si n est impair :
    //   1 → A->C
    //   2 → A->B
    //   0 → B->C
    //
    // Si n est pair :
    //   1 → A->B
    //   2 → A->C
    //   0 → B->C
    //
    // Le programme utilise i % 3 pour repérer le mouvement suivant.
    for (long long i = 1; i <= moves; i++) {

        int mod = i % 3;  // détermine quel mouvement effectuer

        if (n % 2 == 1) {  // CAS : nombre impair de disques

            if (mod == 1)
                moveBetween(A, C, 'A', 'C', i);  // mouvement légal entre A et C

            else if (mod == 2)
                moveBetween(A, B, 'A', 'B', i);  // mouvement légal entre A et B

            else
                moveBetween(B, C, 'B', 'C', i);  // mouvement légal entre B et C
        }

        else {  // CAS : nombre pair de disques

            if (mod == 1)
                moveBetween(A, B, 'A', 'B', i);

            else if (mod == 2)
                moveBetween(A, C, 'A', 'C', i);

            else
                moveBetween(B, C, 'B', 'C', i);
        }
    }

    // Fin du chronométrage et calcul du temps en millisecondes
    clock_t end = clock();
    double exec_time = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

    printf("\nTemps d'execution : %.2f ms\n", exec_time);
    printf("Nombre total de mouvements effectues : %lld\n", moves);
    printf("-------------------------------------------------\n");
    // -----------------------------------------------------
    // Libération de la mémoire allouée
    // -----------------------------------------------------
    free(A);
    free(B);
    free(C);
    }
   }while(n!=0);
    return 0;
}
