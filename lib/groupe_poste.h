#pragma once

#include "liste.h"
#include "groupe_entreprise.h"

#include <stdbool.h>
#include <stdio.h>

////////////////////////////////////////////////////////// POSTE  ////////////////////////////////////////////////
#define MAX_COMP 5


typedef struct poste
{
    int id;
    char titre[128] ;
    char competence[MAX_COMP][128] ;
    entreprise * entrep;
} poste ;

typedef struct groupe_postes
{
    node* postes ;
} groupe_postes;



// Crée un groupe à partir d'un flux donné.
groupe_postes * gp_open(FILE* db,groupe_entreprises * gr);
void voir_postes(groupe_postes* g) ;
//void supprime_poste_entr(groupe_postes* gr,int id) ;
void supprime_profile_entrep(groupe_entreprises* g,groupe_postes* gr,int id) ;
void cree_profile_poste(groupe_postes* g,groupe_entreprises * gr) ;
int gp_size(groupe_postes* g) ;
node * gp_id_node(groupe_postes* g, int const id) ;
void supprimer_profile_poste(groupe_postes* g,int id) ;
poste* gp_id(groupe_postes* g, int const id) ;
