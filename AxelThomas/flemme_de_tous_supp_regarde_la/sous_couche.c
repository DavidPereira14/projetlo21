//
// Created by v05ax on 08/12/2024.
//

#include "sous_couche.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "liste.h"
#include "noeud.h"

// Fonction pour initialiser la couche avec des neurones ayant des poids aléatoires
Liste* InitCouche(int nombre_neurones, int nombre_entrees, int seuil_par_defaut) {
    // Vérification des paramètres d'entrée
    if (nombre_neurones <= 0 || nombre_entrees <= 0) {
        printf("Erreur : nombre de neurones (%d) ou d'entrées (%d) invalide.\n", nombre_neurones, nombre_entrees);
        return NULL;
    }

    // Initialisation de la couche en tant que liste chaînée
    Liste *couche = NULL;

    // Initialisation de l'état aléatoire pour générer des nombres différents à chaque exécution
    srand(time(NULL));

    // Création des neurones pour la couche
    for (int i = 0; i < nombre_neurones; i++) {
        Liste *poids = NULL;

        // Initialisation des poids pour chaque neurone avec des valeurs aléatoires
        for (int j = 0; j < nombre_entrees; j++) {
            int poids_aleatoire = rand() % 10;  // Poids aléatoires entre 0 et 9 (ajustez la plage si nécessaire)
            add_queue(&poids, &poids_aleatoire, sizeof(int));  // Ajouter le poids à la liste chaînée des poids
        }

        // Initialisation du neurone avec les poids générés aléatoirement et son seuil
        Neurone *neurone = InitNeur(nombre_entrees, poids, seuil_par_defaut);
        if (neurone == NULL) {
            return NULL;
        }

        // Ajout du neurone à la couche
        add_queue(&couche, neurone, sizeof(Neurone));
    }

    return couche;
}

Liste* OutCouche(Liste *couche, Liste *entree){
    // Création de la sortie en tant que liste chaînée
    Liste *sortie = NULL;
    if (couche != NULL) {
        Neurone *n=couche->data;
        if (count_list(entree) != n->n_entrees){
            printf("Erreur : la taille de la liste n'est pas bonne");
            return NULL;
        }
        else{
            Liste *neuronne_temp = couche;
            while (neuronne_temp != NULL) {
                // Calculer la sortie du neurone courant
                int neurone_sortie = Outneurone(neuronne_temp->data, entree);

                // Ajouter cette sortie à la liste des sorties
                add_queue(&sortie, &neurone_sortie, sizeof(int));

                // Passer au neurone suivant
                neuronne_temp = neuronne_temp->next;
            }
        }
    }
    return  sortie;
}