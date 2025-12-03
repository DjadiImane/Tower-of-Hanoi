#include <stdio.h>
#include <time.h>

long nbmoves = 0; 
void hanoi(int n, char A, char C, char B) {
    if (n != 0) {
        hanoi(n - 1, A, B, C);
        printf("%c --> %c (disque %d)\n", A, C, n);
        nbmoves++;
        hanoi(n - 1, B, C, A);
}
}

int main() {
       int n;
       int entree;
   do{
    printf("Entrer le nombre de disques (0 pour quitter): ");
    entree=scanf("%d", &n);
    
if(entree!=1){   
       if (entree != 1) {
            printf("Entree invalide !\n");
            return 0;
        }     
    }
if (n == 0) {
        printf("Programme terminer.\n");
        return 0;
        }

if (n < 0) {
        printf("Veuillez entrer un nombre positif.\n");
    }
else{
    nbmoves = 0;
    printf("------------- DEBUT DES MOUVEMENTS -------------\n\n");
    clock_t debut = clock(); 
    hanoi(n, 'A', 'C','B');
    clock_t fin = clock(); 
    double temps_total = (double)(fin - debut) / CLOCKS_PER_SEC;

   
    printf("\n---------------------------------------\n");
    printf("Nombre total de mouvements : %ld\n", nbmoves);
    printf("Temps d'execution : %f secondes\n", temps_total);
    printf("----------------------------------------\n");
}
    }while(n!=0);
    return 0;
}