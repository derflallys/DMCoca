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
cp graphs/$graph.c ./graph.c

make clean #Nettoyage des fichiers compilés
make # Compilation du programme
rm -f graph.c # Suppression de la copie du graphe
TEST_OUT=$(./triangleToSAT)

# Lancer le solveur glucose
echo $TEST_OUT | grep -v 'Usage' && ./glucose-syrup/simp/glucose -model sat.cnf > resultat.txt

#Nettoyage des fichiers compilés
make clean