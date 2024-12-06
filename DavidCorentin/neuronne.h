
#ifndef PROJET_H
#define PROJET_H
// Structure représentant un poids dans la liste chaînée
typedef struct Poids {
    int valeur;           // Valeur du poids
    struct Poids* suivant; // Pointeur vers le poids suivant
} Poids;

// Structure représentant un neurone
typedef struct Neuronne {
    Poids* poids;    // Liste chaînée des poids
    int biais;       // Biais du neurone
    int nbEntrees;   // Nombre d'entrées du neurone
} Neuronne;


// Fonction pour initialiser un neurone avec une liste de poids et un biais
void InitNeur(Neuronne* neuronne, int nb_entrées, int* liste_poids, int biais);

// Fonction pour calculer la sortie du neurone
int Outneurone(Neuronne* neuronne, int* entrées);

#endif //PROJET_H
