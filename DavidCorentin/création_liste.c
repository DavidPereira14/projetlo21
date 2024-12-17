#include "création_liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Liste *createElement(void *data, size_t dataSize){
  Liste *nv_liste = (Liste *)malloc(sizeof(Liste));
  nv_liste->data = malloc(dataSize);
  memcpy(nv_liste->data, data, dataSize);
  nv_liste->next = NULL;
  return nv_liste;
}

void ajouterQueue(Liste **head, void *data, size_t dataSize){
  Liste *new_ele = createElement(data, dataSize); // Crée un nouveau élément
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

void free_list(Liste *tête){
  Liste *temp;
  while (tête != NULL) {
    temp = tête;
    tête = tête->next;
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