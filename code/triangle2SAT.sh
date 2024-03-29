#!/bin/bash

echo "Choisissez un des graphes ci-dessous à reduire en CNF-SAT (ne pas écrire le .c)."
# Affichage de tous les graphes
ls graphs
# Récupération du graphe choisi
read graph

# Test de l'existance du graphe
while [[ ! -e graphs/$graph.c ]]; do
    echo "Le graphe choisi n'existe pas. Réessayez."
    # Affichage de tous les graphes
    ls graphs
    read graph
done

# Copie du graphe choisi (renommé) dans le répertoire courant 
cp graphs/$graph.c ./

#Renommage du fichier
mv $graph.c graph.c 

make clean #Nettoyage des fichiers compilés
make # Compilation du programme

#Lance le programme qui génère le fichier cnf
./triangleToSAT

rm -f graph.c # Suppression de la copie du graphe

#compilation de glucose
#make clean -C glucose-syrup-4.1/simp/
make -C glucose-syrup-4.1/simp/

# Lancer le solveur glucose
./glucose-syrup-4.1/simp/glucose sat.cnf > resultat.txt

#Nettoyage des fichiers compilés
make clean

echo "Vous pouvez consulter le résulat dans le fichier resultat.txt."