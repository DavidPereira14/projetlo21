//
// Created by v05ax on 16/12/2024.
//

#ifndef UNTITLED5_RESEAUX_H
#define UNTITLED5_RESEAUX_H

#include "reseaux.h"
#include "sous_couche.h"
#include "noeud.h"
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Liste* CreerResNeur(int nombre_couches, Liste *neurones_par_couche,Liste *seuil, int nombre_entrees);
Liste* PropagationAvant(Liste *reseau, Liste *entrees);
Neurone* ReseauEt(int nombre_entre);
Neurone* ReseauOu(int nombre_entre);
Neurone* ReseauNot();
Liste* CreerResNeurMulticouches();


#endif //UNTITLED5_RESEAUX_H
