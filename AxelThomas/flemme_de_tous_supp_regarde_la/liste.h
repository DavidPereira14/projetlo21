    //
// Created by v05ax on 06/12/2024.
//

#ifndef UNTITLED5_LISTE_H
#define UNTITLED5_LISTE_H
#include <stddef.h>
// Définition de la structure Liste
typedef struct Liste {
    void *data;            // Pointeur générique pour stocker tout type de valeur
    struct Liste *next;    // Pointeur vers l'élément suivant
} Liste;

Liste* create_ele(void *data, size_t data_size);

void add_queue(Liste **head, void *data, size_t data_size);

void free_list(Liste *head);

int count_list(Liste *head);

#endif //UNTITLED5_LISTE_H
