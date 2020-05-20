#pragma once

#include "groupe_poste.h"


#include "liste.h"

#include <stdbool.h>
#include <stdio.h>
////////////////////////////////////////////////////////// EMPLOYE  ////////////////////////////////////////////////
#define MAX_COLLEGUES 5
#define MAX_COMP 5

typedef struct employe
{
    int id;
    char nom[128] ;
    char prenom[128] ;
    char mail[128] ;
    int code_postale ;
    char competence[MAX_COMP][128] ;
    struct employe * collegues[MAX_COLLEGUES];
    entreprise * entrep ;
} employe ;

typedef struct groupe_employes
{
    node* employes ;
} groupe_employes ;

typedef struct tab2
{
    int a ;
    int b ;
}tab2 ;

typedef struct tab3
{
    int a ;
    int b ;
    int c ;
}tab3 ;

// Crée un groupe à partir d'un flux donné.
groupe_employes * gemp_open(FILE* db);
// Retourne l empolye qui porte l'id donné.
employe* gemp_id(groupe_employes* g, int const id) ;
int gemp_size(groupe_employes* g) ;
void voir_employes(groupe_employes* g) ;
void creer_profil_employe(groupe_employes * g,groupe_entreprises *gr) ;
void modifier_profil_employe(groupe_employes * g,groupe_entreprises *gr,int id_employe) ;
void supprimer_profil_employe(groupe_employes * g,int id_employe) ;
int compart_int_b ( const void * first, const void * second ) ;
int compart_int_b_c ( const void * first, const void * second ) ;
void rechercher_poste_emp_par_competences(groupe_postes * g,groupe_employes *gr,int id_employe) ;
void rechercher_poste_emp_par_competences_et_code_postale(groupe_postes * g,groupe_employes *gr,int id_employe,int code_postale) ;
void rechercher_employe_emp_par_entreprise(groupe_employes * g,int id_employe,int id_entreprise) ;
int in_tab_id (int n ,int tab_id[n],int e) ;
void rechercher_employe_emp_par_competences(groupe_employes * g,groupe_postes *g1,int id_employe) ;


//void creer_profil_employe(groupe_employes* g,int id,char nom[128],char prenom[128],char mail[128],int code_postale,char competence[MAX_COMP][128],employe * collegues[MAX_COLLEGUES],entreprise * entrep ) ;
