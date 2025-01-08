#include <stdio.h>
#include "liste.h"

#include "reseaux.h"

// Fonction pour afficher les résultats d'une liste d'entiers (sortie du réseau)
void afficher_sortie(Liste *sortie) {
    Liste *temp = sortie;
    while (temp != NULL) {
        printf("%d ", *((int *)temp->data));
        temp = temp->next;
    }
    printf("\n");
}
// Fonction principale pour tester le réseau
int main() {
    // Initialisation des entrées (A, B, C) pour tester le réseau
    Liste *entrees = NULL;
    int entreeA = 1; // A = 1
    int entreeB = 0; // B = 0
    int entreeC = 1; // C = 1
    add_queue(&entrees, &entreeA, sizeof(int));
    add_queue(&entrees, &entreeB, sizeof(int));
    add_queue(&entrees, &entreeC, sizeof(int));




    // Test de la propagation avant
    Liste *sortie = PropagationAvant(CreerResNeurMulticouches(), entrees);

    // Affichage de la sortie du réseau
    printf("Sortie du réseau : ");
    afficher_sortie(sortie);

    // Libération de la mémoire
    free(entrees);


    return 0;
}
/*
// Fonction principale pour tester la propagation avant
int main() {
    // Initialisation des entrées du réseau (par exemple : [1, 0])
    Liste *entrees = NULL;
    int entrees_data[] = {1, 0};  // Exemple d'entrées pour les tests
    for (int i = 0; i < 2; i++) {
        add_queue(&entrees, &entrees_data[i], sizeof(int));
    }

    // Définir le nombre de neurones par couche (par exemple : 2 neurones dans chaque couche)
    Liste *neurones_par_couche = NULL;
    int neurones_data[] = {2, 2};  // Exemple de 2 neurones pour chaque couche
    for (int i = 0; i < 2; i++) {
        add_queue(&neurones_par_couche, &neurones_data[i], sizeof(int));
    }

    // Définir les seuils de chaque couche
    Liste *seuil = NULL;
    int seuil_data[] = {1, 1};  // Exemple de seuil 1 pour chaque couche
    for (int i = 0; i < 2; i++) {
        add_queue(&seuil, &seuil_data[i], sizeof(int));
    }

    // Créer le réseau de neurones
    int nombre_couches = 2;  // Exemple : 2 couches
    Liste *reseau = CreerResNeur(nombre_couches, neurones_par_couche, seuil, 2);

    // Vérifier si la création du réseau a réussi
    if (reseau == NULL) {
        printf("Erreur lors de la création du réseau.\n");
        return 1;
    }

    // Propagation avant avec les entrées
    Liste *sortie = PropagationAvant(reseau, entrees);

    // Afficher la sortie de la dernière couche
    if (sortie != NULL) {
        Liste *temp = sortie;
        printf("Sortie du réseau : ");
        while (temp != NULL) {
            int valeur = *(int *)(temp->data);
            printf("%d ", valeur);
            temp = temp->next;
        }
        printf("\n");
    } else {
        printf("Erreur lors de la propagation avant.\n");
    }

    // Libération de la mémoire (si nécessaire)
    // Ici vous pouvez ajouter des fonctions pour libérer les listes et autres allocations dynamiques

    return 0;
}
*/
