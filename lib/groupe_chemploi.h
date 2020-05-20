#pragma once

#include "liste.h"
#include "groupe_employe.h"
#include "groupe_poste.h"

#include <stdbool.h>
#include <stdio.h>
////////////////////////////////////////////////////////// CHEMPLOI ////////////////////////////////////////////////
#define MAX_COMP 5

typedef struct chemploi
{
    int id;
    char nom[128] ;
    char prenom[128] ;
    char mail[128] ;
    int code_postale ;
    char competence[5][128] ;
    employe * collegues[MAX_COLLEGUES];

} chemploi ;

typedef struct groupe_chemplois
{
    node * chemplois ;
} groupe_chemplois ;



// Crée un groupe à partir d'un flux donné.
groupe_chemplois * gch_open(FILE* db);
chemploi* gchemp_id(groupe_chemplois* g, int const id) ;
int gchemp_size(groupe_chemplois* g) ;
void voir_chemplois(groupe_chemplois* g) ;
void rechercher_chemploi_par_competences(groupe_chemplois * g,int id_poste) ;
void rechercher_chemploi_par_competences_et_code_postale(groupe_chemplois * g,int id_poste,int code_postale) ;
void creer_profil_chemploi(groupe_chemplois * g) ;
void modifier_profil_chemploi(groupe_chemplois * g,int id_chemploi) ;
void supprimer_profil_chemploi(groupe_chemplois * g,int id_chemploi) ;
void transitionner_chempl_employe(groupe_chemplois *g,groupe_employes *gr,int id_chemploi,int id_entreprise) ;
int in_tab_collegues(employe * collegues[MAX_COLLEGUES],employe * ptr) ;
void transitionner_employe_chempl(groupe_employes *g,groupe_chemplois *gr,int id_employe) ;
void rechercher_poste_chemp_par_competences(groupe_postes * g,groupe_chemplois *gr,int id_chemploi) ;
void rechercher_poste_chemp_par_competences_et_code_postale(groupe_postes * g,groupe_chemplois *gr,int id_chemploi,int code_postale) ;
void rechercher_employe_chemp_par_entreprise(groupe_chemplois *g,int id_chemploi,int id_entreprise) ;
void rechercher_employe_chemp_par_competences(groupe_chemplois *g,groupe_postes * g1,int id_chemploi) ;
