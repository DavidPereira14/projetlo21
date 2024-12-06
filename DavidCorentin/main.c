#include <stdio.h>
#include "neuronne.h"

int main() {
    Neuronne neuronne;

    // Liste de poids pour le neurone (par exemple 3 entrées)
    int poids[] = {2, -1, 3};
    int biais = 1;  // Biais

    // Initialiser le neuronne avec 3 entrées et les poids
    InitNeur(&neuronne, 3, poids, biais);

    // Liste des entrées pour le neuronne
    int entrees[] = {1, 0, 1};

    // Calculer la sortie du neuronne
    int sortie = Outneurone(&neuronne, entrees);
    printf("Sortie du neuronne : %d\n", sortie);

    return 0;
}