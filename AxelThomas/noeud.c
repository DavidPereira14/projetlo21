#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "noeud.h"


Neurone* InitNeur(int n_entrees, int *poids, int seuil) {
    if (count_entries(poids)==n_entrees) { //verifie que la taille de la liste poids est égal à n_entree
        Neurone *neurone = (Neurone *) malloc(sizeof(Neurone));
        if (neurone == NULL) {
            printf("Erreur : allocation mémoire échouée.\n");
            return NULL;
        }

        neurone->poids = NULL; // Initialiser la liste des poids comme vide
        for (int i = 0; i < n_entrees; i++) {
            add_queue(&neurone->poids, &poids[i], sizeof(int)); // Ajouter chaque poids
        }

        neurone->seuil = seuil;
        neurone->n_entrees = n_entrees;

        return neurone;
    }
    else{
        printf("Erreur : la taille de la liste poid doi être égal au nombre d'entrée");
        return NULL;
    }
}

int Outneurone(Neurone *neurone, int *entrees) {
    if (neurone == NULL) {
        printf("Erreur : neurone non initialisé.\n");
        return -1;
    }

    if ( count_entries(entrees) != neurone->n_entrees ) {
        printf("Erreur : la taille des entrees ne correspond pas au nombre d'entrées initialisé dans le neuronne.\n");
        return -1;
    }

    int somme_ponderee = 0;
    Liste *poids_courant = neurone->poids;

    // Calcul de la somme pondérée Σ(wi * ei)
    for (int i = 0; i < neurone->n_entrees; i++) {
        somme_ponderee += (*(int *)(poids_courant->data)) * entrees[i]; // (*(int *)(poids_courant->data)) sert a dire au compilateur que data ponte vers un int
        poids_courant = poids_courant->next;
    }

    // Application de la fonction d'activation
    if (somme_ponderee >= neurone->seuil)  {
        return 1;
    }
    else {
        return 0;
    }
}