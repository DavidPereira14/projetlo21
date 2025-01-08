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
// Fonction pour afficher les détails d'un neurone
void afficher_neurone(Neurone *neurone) {
    if (neurone == NULL) {
        printf("Le neurone est NULL.\n");
        return;
    }

    printf("Neurone:\n");
    printf("  Nombre d'entrées : %d\n", neurone->n_entrees);
    printf("  Seuil : %d\n", neurone->seuil);

    printf("  Poids : ");
    Liste *poids = neurone->poids;
    while (poids != NULL) {
        printf("%d ", *(int *)poids->data); // Supposant que les poids sont des entiers
        poids = poids->next;
    }
    printf("\n");
}
void afficher_couche(Liste *couche) {
    if (couche == NULL) {
        printf("La couche est vide.\n");
        return;
    }

    int index = 0;
    while (couche != NULL) {
        printf("Neurone %d:\n", index++);
        afficher_neurone((Neurone *)couche->data);
        couche = couche->next;
    }
}
void afficher_reseau(Liste *reseau) {
    if (reseau == NULL) {
        printf("Le réseau est vide.\n");
        return;
    }

    int index_couche = 0;
    while (reseau != NULL) {
        printf("Couche %d:\n", index_couche++);
        afficher_couche((Liste *)reseau->data);
        reseau = reseau->next;
    }
}

// Fonction pour construire le réseau multi-couches (A ET (NON B) ET C) OU (A ET (NON C))
Liste* CreerResNeurMulticouches() {
    Liste *poid_n1 = NULL;
    for(int i=0 ;i<3;i++){
        if(i==0){
            add_queue(&poid_n1, &(int){1}, sizeof(int));
        }
        else{
            add_queue(&poid_n1,&(int){0}, sizeof(int));
        }
    }
    Neurone *n1 = InitNeur(3,poid_n1,1);
    Liste *poid_n2 = NULL;
    for(int i=0 ;i<3;i++){
        if(i==1){
            add_queue(&poid_n2,&(int){1}, sizeof(int));
        }
        else{
            add_queue(&poid_n2,&(int){0}, sizeof(int));
        }
    }
    Neurone *n2 = InitNeur(3,poid_n2,-1);
    Liste *poid_n3 = NULL;
    for(int i=0 ;i<3;i++){
        if(i==2){
            add_queue(&poid_n3,&(int){1}, sizeof(int));
        }
        else{
            add_queue(&poid_n3,&(int){0}, sizeof(int));
        }
    }
    Neurone *n3 = InitNeur(3,poid_n3,1);
    Liste *poid_n4 = NULL;
    for(int i=0 ;i<3;i++){
        if(i==2){
            add_queue(&poid_n4,&(int){1}, sizeof(int));
        }
        else{
            add_queue(&poid_n4,&(int){0}, sizeof(int));
        }
    }
    Neurone *n4 = InitNeur(3,poid_n4,-1);
    Liste *c1 = NULL;

    add_queue(&c1,n1, sizeof(Neurone));
    add_queue(&c1,n2, sizeof(Neurone));
    add_queue(&c1,n3, sizeof(Neurone));
    add_queue(&c1,n4, sizeof(Neurone));
    poid_n1 = NULL;
    poid_n2 = NULL;
    for(int i=0 ;i<4;i++){
        if(i<3){
            add_queue(&poid_n1,&(int){1}, sizeof(int));
        }
        else{
            add_queue(&poid_n1,&(int){0}, sizeof(int));
        }
    }
    n1 = InitNeur(4,poid_n1,3);
    for(int i=0 ;i<4;i++){
        if(i==0 || i ==3){
            add_queue(&poid_n2,&(int){1}, sizeof(int));
        }
        else{
            add_queue(&poid_n2,&(int){0}, sizeof(int));
        }
    }
    n2 = InitNeur(4,poid_n2,2);
    Liste *c2 = NULL;
    add_queue(&c2,n1, sizeof(Neurone));
    add_queue(&c2,n2, sizeof(Neurone));
    Liste *c3 = NULL;
    Neurone *nou= ReseauOu(2);
    add_queue(&c3, nou, sizeof(Neurone));
    Liste *reseaux = NULL;
    add_queue(&reseaux,c1, sizeof(Neurone));
    add_queue(&reseaux,c2, sizeof(Neurone));
    add_queue(&reseaux,c3, sizeof(Neurone));
    return reseaux;
}
