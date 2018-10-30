#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>

#include "all.h" 
#include "graphs/G30.c"
using namespace std;

int **X;

int getNbClauses() {
    int nbclauses = 0;

    /*
    * Les 3 clauses utilisent les mêmes boucles
    */
    for(int i=0; i < orderG(); i++) {
        for(int j=0; j < orderG(); j++) {
            for(int k=0; k < orderG(); k++) {
                if(i != j && i != k && j != k) {
                    nbclauses+=3;
                }
            }
        }
    }
    return nbclauses;
}

string firstConstraint() {
    string formule = "c\nc CONTRAINTE 1 : Un sommet est le successeur de son successeur\nc\n";
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

    file << "p cnf " << orderG()*orderG() << " " << getNbClauses() << endl;
    file << firstConstraint();
    file << secondConstraint();
    file << thirdConstraint();

    for(int i = 0; i < n; i++) {
        delete [] X[i];
    }
    delete X;

    return 0;
}
