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
Liste* CreerResNeurMulticouches(int nombre_entrees) {
    Liste *reseau = NULL;
    Liste *couche=NULL;
    // Couche 1 : Neurones NOT pour B et C
    Neurone *neuroneNotB = ReseauNot();  // Neurone pour NOT B
    Neurone *neuroneNotC = ReseauNot();  // Neurone pour NOT C
    add_queue(&couche, neuroneNotB, sizeof(Neurone));
    add_queue(&couche, neuroneNotC, sizeof(Neurone));

    add_queue(&reseau,couche, sizeof(Liste));
    couche=NULL;
    // Couche 2 : Neurones AND pour (A ET (NON B) ET C) et (A ET (NON C))
    Neurone *neuroneEt1 = ReseauEt(3);  // Neurone pour (A ET (NON B) ET C)
    Neurone *neuroneEt2 = ReseauEt(3);  // Neurone pour (A ET (NON C))
    add_queue(&couche, neuroneEt1, sizeof(Neurone));
    add_queue(&couche, neuroneEt2, sizeof(Neurone));

    add_queue(&reseau,couche, sizeof(Liste));
    couche=NULL;
    // Couche 3 : Neurone OR pour (A ET (NON B) ET C) OU (A ET (NON C))
    Neurone *neuroneOr = ReseauOu(2);   // Neurone OR avec 2 entrées
    add_queue(&couche, neuroneOr, sizeof(Neurone));
    add_queue(&reseau,couche, sizeof(Liste));


    return reseau;
}