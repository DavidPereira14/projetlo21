#include "neuronne.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction pour initialiser un neurone avec une liste de poids et un biais
void InitNeur(Neuronne* neuronne, int nb_entrées, int* liste_poids, int biais) {
    neuronne->biais = biais;
    neuronne->nbEntrees = nb_entrées;
    neuronne->poids = NULL;

    // Créer la liste chaînée des poids à partir de la liste fournie
    for (int i = 0; i < nb_entrées; i++) {
        Poids* nouveauPoids = (Poids*)malloc(sizeof(Poids));
        if (nouveauPoids == NULL) {
            printf("Erreur d'allocation de mémoire pour les poids.\n");
            return;
        }
        nouveauPoids->valeur = liste_poids[i];
        nouveauPoids->suivant = neuronne->poids; // Ajouter le poids à la tête de la liste
        neuronne->poids = nouveauPoids;
    }
}

// Fonction pour calculer la sortie du neurone
int Outneurone(Neuronne* neuronne, int* entrées) {
    int somme = 0;
    Poids* poidsActuel = neuronne->poids;

    // Calculer la somme pondérée des entrées
    for (int i = 0; i < neuronne->nbEntrees; i++) {
        somme += entrées[i] * poidsActuel->valeur;
        poidsActuel = poidsActuel->suivant; // Passer au poids suivant
    }

    // Ajouter le biais
    somme += neuronne->biais;

    // Appliquer la fonction d'activation
    if (somme >= 0) {
        return 1; // Sortie activée
    } else {
        return 0; // Sortie non activée
    }
}