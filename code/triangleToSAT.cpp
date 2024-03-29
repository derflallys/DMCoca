#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include "all.h" 

#include "graph.c"    

using namespace std;

int **X;

int getNbClauses() {
    int nbclauses = 0;

    /*
    * Les 3 clauses utilisent les mêmes boucles
    */
    for(int u=0; u < orderG(); u++) {
        for(int v=0; v < orderG(); v++) {
            for(int w=0; w < orderG(); w++) {
                //Contrainte 1
                if( (u != v && u != w && v != w) && (are_adjacent(u,v) != 0 && are_adjacent(v,w) != 0 && are_adjacent(w,u) != 0 ) ) {
                    nbclauses++;
                }
                //Contrainte 2
                if( (u != v && u != w && v != w) && (are_adjacent(u,v) != 0 && are_adjacent(v,w) != 0 && are_adjacent(w,u) != 0 ) ) {
                    nbclauses++;
                }
                //Contrainte 3
                if( (u != v && u != w && v != w) && (are_adjacent(u,v) != 0 && are_adjacent(v,w) != 0 && are_adjacent(w,u) != 0 ) ) {
                    nbclauses++;   
                }
                
            }
        }
    }
    
    for(int u=0; u < orderG(); u++) {
        for(int v=0; v < orderG(); v++) {
                if( (u != v && v != u) && (are_adjacent(u,v) != 0) ) {
                    nbclauses++;
                }
        }
    }
     if(orderG()%3 != 0) {
        nbclauses+=2;   
    }
    return nbclauses;
}

string firstConstraint() {
    string formule = "c\nc CONTRAINTE 1 : Un sommet est le successeur de son successeur\nc\n";
    for(int u=0; u < orderG(); u++) {
        for(int v=0; v < orderG(); v++) {
            for(int w=0; w < orderG(); w++) {
                if( (u != v && u != w && v != w) && (are_adjacent(u,v) != 0 && are_adjacent(v,w) != 0 && are_adjacent(w,u) != 0 ) ) {
                    std::ostringstream ss1;
                    std::ostringstream ss2;
                    std::ostringstream ss3;
                    ss1 << X[u][v];
                    ss2 << X[v][w];
                    ss3 << X[w][u];
                    formule += "-" + ss1.str() + " -" + ss2.str() + " "+ss3.str() + " 0\n";
                }
            }
        }
    }
    return formule;
}

string secondConstraint() {
    string formule = "c\nc CONTRAINTE 2 : Un sommet ne peut avoir qu'un seul successeur\nc\n";
    for(int u=0; u < orderG(); u++) {
        for(int v=0; v < orderG(); v++) {
            for(int w=0; w < orderG(); w++) {
                if( (u != v && u != w && v != w) && (are_adjacent(u,v) != 0 && are_adjacent(v,w) != 0 && are_adjacent(w,u) != 0 ) ) {
                    std::ostringstream ss1;
                    std::ostringstream ss2;
                    ss1 << X[u][v];
                    ss2 << X[u][w];
                    formule += "-" + ss1.str() + " -" + ss2.str() + " 0\n";
                }
            }
        }
    }
    return formule;
}

string thirdConstraint() {
    string formule = "c\nc CONTRAINTE 3 : Un sommet ne peut etre qu'une fois successeur des autres sommets\nc\n";
    for(int u=0; u < orderG(); u++) {
        for(int v=0; v < orderG(); v++) {
            for(int w=0; w < orderG(); w++) {
                if( (u != v && u != w && v != w) && (are_adjacent(u,v) != 0 && are_adjacent(v,w) != 0 && are_adjacent(w,u) != 0 ) ) {
                    std::ostringstream ss1;
                    std::ostringstream ss2;
                    ss1 << X[u][v];
                    ss2 << X[w][v];
                    formule += "-" + ss1.str() + " -" + ss2.str() + " 0\n";
                }
            }
        }
    }
    return formule;
}

// Constrainte a ajouter UNIQUEMENT lorsque le nombre de sommet est inexact pour rendre la formule insatisfiable.
string NoTrianglesConstraint() {
    string formule = "c\nc CONTRAINTE 4 : Le graphe doit avoir un nombre de sommet multiple de 3.\nc\n";
    formule += "-1 0\n 1 0\n";
    return formule;
}

string fourthConstraint() {
    string formule = "c\nc CONTRAINTE 4 : Un sommet u est succeseur de v mais v ne peux pas etre successeur de u\nc\n";
    for(int u=0; u < orderG(); u++) {
        for(int v=0; v < orderG(); v++) {
                if( (u != v ) && (are_adjacent(u,v) != 0) ) {
                    std::ostringstream ss1;
                    std::ostringstream ss2;
                    ss1 << X[u][v];
                    ss2 << X[v][u];
                    formule += "-" + ss1.str() + " -" + ss2.str() + " 0\n";
                }
        }
    }
    return formule;
}


int main(int argc, char const *argv[]){
    int n = orderG(); // Nombre de sommets du graphe
    int m = sizeG(); // Nombre d'arêtes du graphe
    int nbclauses = 0; // Nombre de clauses 

    //Initialisation de la variable X tableau de taille n
    X = new int*[n];
    for(int i = 0; i < n; i++) {
        X[i] = new int[n];
    }

    int indiceVariable = 0;
    for(int i = 0; i <n; i++) {
        for(int j = 0; j< n; j++) {
            X[i][j] = ++indiceVariable;
        }
    }

    // Création du fichier
    ofstream file("sat.cnf");

    file << "p cnf " << orderG()*(orderG()-1)<< " " << getNbClauses() << endl;
    file << firstConstraint();
    file << secondConstraint();
    file << thirdConstraint();
    file << fourthConstraint();

    if(orderG()%3 != 0) {
        file << NoTrianglesConstraint();
    }

    for(int i = 0; i < n; i++) {
        delete [] X[i];
    }
    delete X;

    return 0;
}
