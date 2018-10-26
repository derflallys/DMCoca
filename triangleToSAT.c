#include <stdio.h>
#include <stdlib.h>
#include "all.h" 

int main(int argc, char const *argv[]){
    int n = orderG(); // Nombre de sommets du graphe
    int m = sizeG(); // Nombre d'arêtes du graphe
    int nbclauses = 0; // Nombre de clauses 

    // Création/Ecriture du fichier
    FILE* fd = NULL;
    fd = fopen("sat.cnf", "w");
    if(fd == NULL) {
        usage("Impossible to open the file !");
    }
    
    // int **X = malloc((n+1) * sizeof(int*)); // [1...n]
    // if(X == NULL){
    //     usage("Not enough memory !");
    // }

    // for (int i = 1; i <= n; i++) {
    //     X[i] = malloc((k+1) * sizeof(int)); // [0...k]
    //     if(X[i] == NULL){
    //         usage("Not enough memory !");
    //     }
    // }

    fclose(fd);
    return 0;
}
