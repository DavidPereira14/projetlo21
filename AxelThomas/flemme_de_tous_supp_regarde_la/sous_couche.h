//
// Created by v05ax on 08/12/2024.
//

#ifndef UNTITLED5_SOUS_COUCHE_H
#define UNTITLED5_SOUS_COUCHE_H
#include "liste.h"
#include "noeud.h"

Liste* InitCouche(int nombre_neurones, int nombre_entrees, int seuil_par_defaut) ;

Liste* OutCouche(Liste *couche, Liste *entree);

#endif //UNTITLED5_SOUS_COUCHE_H
