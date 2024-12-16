#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include <stddef.h>


// Fonction pour créer un nouveau nœud
Liste* create_ele(void *data, size_t data_size) {
    Liste *new_liste = (Liste *)malloc(sizeof(Liste));
    new_liste->data = malloc(data_size);    // Allouer de l'espace pour la donnée
    memcpy(new_liste->data, data, data_size); // Copier la donnée
    new_liste->next = NULL;
    return new_liste;
}

// Fonction pour ajouter un élément à la queue
void add_queue(Liste **head, void *data, size_t data_size) {
    Liste *new_ele = create_ele(data, data_size); // Crée un nouveau élément
    if (*head == NULL) {
        *head = new_ele; // Si la liste est vide, le nouveau élément devient le premier
    } else {
        Liste *temp = *head;
        while (temp->next != NULL) { // Parcourt jusqu'à la fin
            temp = temp->next;
        }
        temp->next = new_ele; // Ajoute l'élément à la fin
    }
}

// Fonction pour libérer la mémoire d'une liste
void free_list(Liste *head) {
    Liste *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data); // Libère la mémoire de la donnée
        free(temp);       // Libère l'élément
    }
}

// Fonction pour compter le nombre d'éléments dans une liste chaînée
int count_list(Liste *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}