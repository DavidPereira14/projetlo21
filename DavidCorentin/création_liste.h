#ifndef CRÉATION_LISTE_H
#define CRÉATION_LISTE_H

#include <stddef.h>


// Définition de la structure Liste
typedef struct Liste {
    void *data;            // Pointeur générique pour stocker tout type de valeur
    struct Liste *next;    // Pointeur vers l'élément suivant
} Liste;

Liste *createElement(void *data, size_t dataSize);

void ajouterQueue(Liste **head, void *data, size_t dataSize);

void freeListe(Liste *tete);

int count_list(Liste *head);

#endif //CRÉATION_LISTE_H
