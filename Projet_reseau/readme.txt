readme

Sommaire

-------------------------------

* Introduction
* Structure
* Fonctionnement
* Conclusion


Introduction

-------------------------------

Pour ce projet d'analyseur de protocoles réseau, dans le cadre de notre UE de Réseaux
en L3 d'Informatique à Sorbonne Université enseignée par M Prométhée Spathis, nous avons
choisi de coder notre solution en C++.

Nous avons choisi C++ car c'est un langage proche du C que nous avons étudié les années précédentes
et qui apporte un confort significatif pour la conception de nos différents analyseurs
de protocoles réseau par classe.

Structure

-------------------------------

Description de la structure de notre projet:

A l'exécution du main, notre programme prend en entrée une trame hexadécimale placée dans
le document "analyse_donne.txt". Puis il retourne une analyse des protocoles détectés,
indentés en sortie.

Nous avons différents types de classes:

1. Classes structurantes

Data, Trame, fonctionsMaths

Ces classes permettent d'analyser le code hexadécimal donné en entrée

2. Classes protocoles

IpFrame, IcmpFrame, ArpFrame, TcpFrame et HttpFrame

Ces classes correspondent chacune a un protocole différent et permettent de classer
le code hexadécimal par traces de protocoles.

Fonctionnement

-------------------------------







Créé par Pierre-Alexandre Gruman et Quentin Bellut
