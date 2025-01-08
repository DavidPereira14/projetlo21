 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "noeud.h"


#include <stdlib.h>

Neurone* InitNeur(int n_entrees, Liste *poids, int seuil) {
    // On suppose que tous les poids sont égaux à 1 et le seuil est égal à n_entrees
    if (count_list(poids) != n_entrees) {
        printf("Erreur : nombre d'entrées et taille des poids ne correspondent pas.\n");
        return NULL;
    }

    // Création du neurone
    Neurone *neurone = (Neurone*)malloc(sizeof(Neurone));
    if (!neurone) {
        printf("Erreur d'allocation mémoire pour le neurone.\n");
        return NULL;
    }

    // Initialisation des poids à 1
    neurone->poids = poids;
    neurone->seuil = n_entrees;  // Le seuil est égal au nombre d'entrées
    neurone->n_entrees = n_entrees;

    return neurone;
}

int Outneurone(Neurone *neurone, Liste *entrees) {
    if (neurone == NULL) {
        printf("Erreur : neurone non initialisé.\n");
        return -1;
    }
    if ( count_list(entrees) != neurone->n_entrees ) {
        printf("Erreur : la taille des entrees ne correspond pas au nombre d'entrées initialisé dans le neuronne.\n");
        return -1;
    }
    int somme_ponderee = 0;
    Liste *poids_courant = neurone->poids;
    Liste *entree_courante = entrees;
    // Calcul de la somme pondérée Σ(wi * ei)
    for (int i = 0; i < neurone->n_entrees; i++) {
        somme_ponderee += (*(int *)(poids_courant->data)) * (*(int *)(entree_courante->data)) ; // (*(int *)(poids_courant->data)) sert a dire au compilateur que data ponte vers un int
        poids_courant = poids_courant->next;
        entree_courante = entree_courante->next;
    }
    // Application de la fonction d'activation
    if (somme_ponderee >= neurone->seuil)  {
        return 1;
    }
    else {
        return 0;
    }
}