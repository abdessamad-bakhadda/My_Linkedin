#include "groupe_entreprise.h"

#include "liste.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////// ENTREPRISE  ////////////////////////////////////////////////
groupe_entreprises* ge_open(FILE *db){
    FILE *f;
    char c;
    int ligne = 1 ,ind_sortie_virgule = 0  , indice_noeud  ;
    f= db ;
    char tmp[100]  ;
    int ind_tmp = 0 ;

    fseek(f,24,SEEK_SET) ; // sauter la première ligne du fichier
    entreprise*entrep =(entreprise*)malloc(sizeof(entreprise)) ;
    groupe_entreprises* g = (groupe_entreprises*)malloc(sizeof(groupe_entreprises)) ;

    if(f)
    {
        while(ligne <= 4)
        {
            c = fgetc(f) ;
            //printf("%c",c) ;
            if(c != ',' && c != '\n' && c != EOF)
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
                    if(ind_sortie_virgule == 1) entrep->id = atoi(tmp) ;
                    else if(ind_sortie_virgule == 2) strcpy(entrep->nom ,tmp) ;
                    else if(ind_sortie_virgule == 3) entrep->code_postale = atoi(tmp) ;
                }
                // if(c == '\n') || (c == EOF)
                else
                {
                        strcpy(entrep->mail ,tmp) ;
                        ligne++ ;
                        ind_sortie_virgule = 0 ;
                        indice_noeud = entrep->id ;
                        if(indice_noeud== 1)
                        {
                            g->entreprises = l_make_node((entreprise*)entrep) ;
                        }
                        else
                        {
                            l_append(&(g->entreprises),l_make_node((entreprise*)entrep)) ;
                        }
                        entrep =(entreprise*)malloc(sizeof(entreprise)) ;
                }
                ind_tmp = 0 ;
            }
        }
        //fclose(f);
    }
    return g;
}

entreprise* ge_id(groupe_entreprises* g, int const id)
{
    node * ptr = g->entreprises ;
    while(ptr && ((entreprise*)ptr->data)->id != id) ptr = ptr->next ;
    if(ptr) return (entreprise*)ptr->data  ;
    return NULL ;
}
int ge_size(groupe_entreprises* g)
{
    return l_length(g->entreprises);
}

void cree_profile_entrep(groupe_entreprises* g)
{
  int id;
  char nom[128] ;
  int code_postale ;
  char mail[128];
  entreprise * ptr = (entreprise *)malloc(sizeof(entreprise)) ;

  id = ge_size(g)+1 ;
  printf("nom = ") ;
  scanf("%s",&nom) ;
  printf("code_postale = ") ;
  scanf("%d",&code_postale) ;
  printf("mail = ") ;
  scanf("%s",&mail) ;

  ptr->id = id ;
  strcpy(ptr->nom ,nom) ;
  ptr->code_postale = code_postale ;
  strcpy(ptr->mail ,mail) ;

  l_append(&(g->entreprises),l_make_node((entreprise*)ptr)) ;
}
void voir_entreprises(groupe_entreprises* g)
{
    node * tmp1 = g->entreprises ;
    entreprise * tmp2  ;
    while(tmp1)
    {
        tmp2 = (entreprise *)tmp1->data ;
        tmp1 = tmp1->next ;
    }
}
