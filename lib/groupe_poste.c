#include "groupe_poste.h"
#include "groupe_entreprise.h"
#include "liste.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////// POSTE  ////////////////////////////////////////////////
groupe_postes* gp_open(FILE *db){
    FILE *f;
    char c;
    int ligne = 1 ,ind_sortie_virgule = 0  ,ind_sortie_pt_virgule = 0 , indice_noeud  ;
    f= db ;
    char tmp[100]  ;
    int ind_tmp = 0 ;

    fseek(f,32,SEEK_SET) ; // sauter la première ligne du fichier
    poste*pos =(poste*)malloc(sizeof(poste)) ;
    groupe_postes* g = (groupe_postes*)malloc(sizeof(groupe_postes)) ;

    FILE *dba = fopen("test/entreprise.csv", "r");
    groupe_entreprises* gr = ge_open(dba);
    //fclose(dba);

    if(f)
    {
        while(ligne <= 5)
        {
            c = fgetc(f) ;
            //printf("%c",c) ;
            if(c != ','&& c != ';' && c != '\n' && c != EOF)
            {
                //printf("%c",c) ;
                tmp[ind_tmp++] = c ;
                //printf(" tmp:%s",tmp) ;

            }
            else
            {
                tmp[ind_tmp] = '\0' ;
                //printf("%s ",tmp) ;
                if(c == ',')
                {
                    ind_sortie_virgule++ ;
                    if(ind_sortie_virgule == 1) pos->id = atoi(tmp) ;
                    else if(ind_sortie_virgule == 2) strcpy(pos->titre ,tmp) ;
                    else if(ind_sortie_virgule == 3)
                    {
                         strcpy(pos->competence[ind_sortie_pt_virgule] ,tmp) ;
                         for(int i = ind_sortie_pt_virgule+1 ;i< MAX_COMP ;i++)
                         {
                            pos->competence[i][0] = '\0' ;
                         }
                    }
                }

                else
                {
                        if(c == ';')
                        {
                            strcpy(pos->competence[ind_sortie_pt_virgule] ,tmp) ;
                            ind_sortie_pt_virgule++ ;
                        }
                        if (c == '\n' || c == EOF )
                        {
                            pos->entrep = ge_id(gr,atoi(tmp)) ;
                            ligne++ ;
                            ind_sortie_virgule = 0 ;
                            ind_sortie_pt_virgule = 0 ;
                            indice_noeud = pos->id ;
                            if(indice_noeud== 1)
                            {
                                g->postes = l_make_node((poste*)pos) ;
                            }
                            else
                            {
                                l_append(&(g->postes),l_make_node((poste*)pos)) ;
                            }
                            pos =(poste*)malloc(sizeof(poste)) ;
                        }
                }
                ind_tmp = 0 ;
            }
        }
        //fclose(f);
    }
    return g;
}
poste* gp_id(groupe_postes* g, int const id)
{
    node * ptr = g->postes ;
    while(ptr && ((poste*)ptr->data)->id != id) ptr = ptr->next ;
    if(ptr) return (poste*)ptr->data  ;
    return NULL ;
}
int gp_size(groupe_postes* g)
{
    return l_length(g->postes);
}
void voir_postes(groupe_postes* g)
{
    node * tmp1 = g->postes ;
    poste * tmp2  ;
    while(tmp1)
    {
        tmp2 = (poste *)tmp1->data ;
        tmp1 = tmp1->next ;
    }
}
void supprime_profile_entrep(groupe_entreprises* g,groupe_postes* gr,int id)
{
    node * tmpe = g-> entreprises ;
    node * tmpp = gr->postes ;
    while(tmpe)
    {
        if(((entreprise*)tmpe->data)->id == id)
        {
            while(tmpp)
            {
                if(((poste*)tmpp->data)->entrep && ((poste*)tmpp->data)->entrep->id == id)
                {
                    if (!tmpp->previous) gr->postes = l_remove(tmpp)  ;
                    else l_remove(tmpp) ;
                }
                tmpp = tmpp->next ;

            }
            if(!tmpe->previous) g->entreprises = l_remove(tmpe) ;
            else l_remove(tmpe) ;
            return ;
        }
        tmpe = tmpe->next ;
    }
}

void cree_profile_poste(groupe_postes* g)
{
  int id ;
  char titre[128] ;
  int i,nb_comp ;
  char competence[MAX_COMP][128] ;
  int id_entreprise ; //entreprise * entrep;
  entreprise * entrep ;

  poste * ptr = (poste *)malloc(sizeof(poste)) ;
  id = gp_size(g)+1 ;

  printf("titre = ") ;
  scanf("%s",&titre) ;
  printf("nb_comp = ") ;
  scanf("%d",&nb_comp) ;
  for(i = 0 ;i<nb_comp;i++)
  {
    printf("competence[%d] = ",i) ;
    scanf("%s",&competence[i]) ;
  }

  ptr->id = id ;
  strcpy(ptr->titre ,titre) ;
  for(i = 0 ;i<nb_comp;i++)
  {
    strcpy(ptr->competence[i] ,competence[i]) ;
  }

  printf("id_entreprise = ") ;
  scanf("%d",&id_entreprise) ;
  FILE *db = fopen("test/entreprise.csv", "r");
  groupe_entreprises * gr = ge_open(db);
  //fclose(db);
  entrep = ge_id(gr,id_entreprise) ;
  ptr->entrep = entrep ;
  l_append(&(g->postes),l_make_node((poste*)ptr)) ;
}

void supprimer_profile_poste(groupe_postes* g,int id)
{
    node * tmp1 = g->postes ;
    while(tmp1)
    {
        if(((poste*)tmp1->data)->id == id)
        {
            if(!tmp1->previous) g->postes = l_remove(tmp1) ;
            else l_remove(tmp1) ;
            return ;
        }
        tmp1= tmp1->next ;
    }

}
