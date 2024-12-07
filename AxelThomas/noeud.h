//
// Created by v05ax on 06/12/2024.
//

#ifndef UNTITLED5_NOEUD_H
#define UNTITLED5_NOEUD_H

// Définition de la structure pour un neurone
typedef struct Neurone {
    Liste *poids;          // Liste chaînée pour les poids
    int seuil;             // Seuil d'activation
    int n_entrees;         // Nombre d'entrées
} Neurone;

#endif //UNTITLED5_NOEUD_H
