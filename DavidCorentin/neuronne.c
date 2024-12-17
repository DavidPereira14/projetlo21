#include "neuronne.h"
#include "création_liste.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction pour initialiser un neurone avec une liste de poids et un biais
Neuronne* InitNeur(int n_entrees, Liste *poids, int seuil) {
  
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