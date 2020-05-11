#pragma once

#include "liste.h"

#include <stdbool.h>
#include <stdio.h>


////////////////////////////////////////////////////////// ENTREPRISE  ////////////////////////////////////////////////
typedef struct entreprise
{
    int id;
    char nom[128] ;
    int code_postale ;
    char mail[128];
} entreprise ;

typedef struct groupe_entreprises
{
    node* entreprises ;
} groupe_entreprises;

// Crée un groupe à partir d'un flux donné.
groupe_entreprises * ge_open(FILE* db);

// Retourne l entreprise qui porte l'id donné.
entreprise* ge_id(groupe_entreprises* g, int const id);
int ge_size(groupe_entreprises* g) ;
void cree_profile_entrep(groupe_entreprises* g) ;
//void l_remove_poste(int id) ;
void voir_entreprises(groupe_entreprises* g) ;
