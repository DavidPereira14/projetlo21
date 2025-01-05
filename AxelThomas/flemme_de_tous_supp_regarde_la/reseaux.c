#include "reseaux.h"
#include "sous_couche.h"
#include "noeud.h"
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Création d'un réseau de neurones
Liste* CreerResNeur(int nombre_couches, Liste *neurones_par_couche,Liste *seuil, int nombre_entrees) {
    // Vérification de la validité des paramètres
    if (nombre_couches <= 0 || neurones_par_couche == NULL) {
        printf("Erreur : nombre de couches invalide.\n");
        return NULL;
    }
    if (count_list(neurones_par_couche) != nombre_couches) {
        printf("Erreur : la liste des nombres de neurones ne correspond pas au nombre de couches.\n");
        return NULL;
    }
    if (count_list(seuil) != nombre_couches) {
        printf("Erreur : la liste des seuils ne correspond pas au nombre de couches.\n");
        return NULL;
    }

    // Liste qui contiendra les couches du réseau
    Liste *reseau = NULL;
    Liste *nbr_neurones=neurones_par_couche;
    Liste *seuil_neurones=seuil;
    // Boucle pour créer chaque couche du réseau
    for (int i = 0; i < nombre_couches; i++) {

        // Si c'est la première couche (couche d'entrée), on passe le nombre d'entrées
        if (i == 0) {
            // Pour la première couche, le nombre d'entrées est donné par `nombre_entrees`
            Liste *couche = InitCouche(*((int *)nbr_neurones->data), nombre_entrees, *((int *)seuil_neurones->data)); // seuil 0 par défaut
            if (couche == NULL) {
                return NULL; // Erreur lors de l'initialisation de la couche
            }
            add_queue(&reseau, couche, sizeof(Liste)); // Ajouter la couche au réseau
        }
        else {
            // Pour les couches suivantes (couches cachées ou de sortie), on passe le nombre de neurones de la couche précédente
            Liste *couche_precedente = reseau;
            int nombre_entrees_couche = count_list(couche_precedente->data); // Le nombre d'entrées est égal au nombre de neurones dans la couche précédente
            Liste *couche = InitCouche(*((int *)nbr_neurones->data), nombre_entrees_couche, *((int *)seuil_neurones->data)); // seuil 0 par défaut
            if (couche == NULL) {
                return NULL; // Erreur lors de l'initialisation de la couche
            }
            add_queue(&reseau, couche, sizeof(Liste)); // Ajouter la couche au réseau
        }
        nbr_neurones = nbr_neurones->next;
        seuil_neurones = seuil_neurones->next;
    }

    return reseau;
}

Liste* PropagationAvant(Liste *reseau, Liste *entrees) {
    // Vérification que le réseau n'est pas vide
    if (reseau == NULL) {
        printf("Erreur : le réseau est vide.\n");
        return NULL;
    }

    // La première entrée du réseau est la liste des entrées
    Liste *sortie_couche = entrees;

    // Parcourir chaque couche du réseau
    Liste *couche_temp = reseau;
    while (couche_temp != NULL) {
        // Calcul de la sortie de la couche actuelle
        sortie_couche = OutCouche(couche_temp->data, sortie_couche);
        if (sortie_couche == NULL) {
            printf("Erreur dans le calcul de la sortie de la couche.\n");
            return NULL;
        }

        // Passer à la couche suivante
        couche_temp = couche_temp->next;
    }

    // Retourner la sortie de la dernière couche (couche de sortie)
    return sortie_couche;
}

Neurone* ReseauEt(int nombre_entre){
    Liste *poids=NULL;
    Liste *reseau;
    int poid=1;
    for(int i = 0;i < nombre_entre;i++){
        add_queue(&poids,&poid, sizeof(int));
    }
    return InitNeur(nombre_entre,poids,nombre_entre);
}

Neurone* ReseauOu(int nombre_entre){
    Liste *poids=NULL;
    Liste *reseau;
    int poid=1;
    for(int i = 0;i < nombre_entre;i++){
        add_queue(&poids,&poid, sizeof(int));
    }
    return InitNeur(nombre_entre,poids,1);
}

Neurone* ReseauNot(){
    Liste *poids=NULL;
    Liste *reseau;
    int poid=-1;
    add_queue(&poids,&poid, sizeof(int));
    return InitNeur(1,poids,0);
}

// Fonction pour construire le réseau multi-couches (A ET (NON B) ET C) OU (A ET (NON C))
Liste* CreerResNeurMulticouches() {
    // Définition du nombre de couches et des neurones par couche
    int nombre_couches = 3;
    Liste *neurones_par_couche = NULL;
    int couche1_neurones = 2; // 2 neurones dans la première couche (NOT B, NOT C)
    int couche2_neurones = 2; // 2 neurones dans la deuxième couche (AND)
    int couche3_neurones = 1; // 1 neurone dans la troisième couche (OR)
    add_queue(&neurones_par_couche, &couche1_neurones, sizeof(int));
    add_queue(&neurones_par_couche, &couche2_neurones, sizeof(int));
    add_queue(&neurones_par_couche, &couche3_neurones, sizeof(int));

    // Définition des seuils pour chaque couche
    Liste *seuils = NULL;
    int seuil1 = 1; // Seuil pour la première couche
    int seuil2 = 1; // Seuil pour la deuxième couche
    int seuil3 = 1; // Seuil pour la troisième couche
    add_queue(&seuils, &seuil1, sizeof(int));
    add_queue(&seuils, &seuil2, sizeof(int));
    add_queue(&seuils, &seuil3, sizeof(int));
    // Création du réseau multi-couches
    Liste *reseau = CreerResNeur(nombre_couches, neurones_par_couche, seuils, 3);

    return reseau;
}
