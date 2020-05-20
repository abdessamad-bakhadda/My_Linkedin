#include "groupe_chemploi.h"
#include "groupe_poste.h"
#include "groupe_employe.h"

#include "liste.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


////////////////////////////////////////////////////////// CHEMPLOI  ////////////////////////////////////////////////
#define MAX_COMP 5

groupe_chemplois* gch_open(FILE *db){
    FILE *f;
    char c;
    int ligne = 1 ,ind_sortie_virgule = 0 ,ind_sortie_pt_virgule = 0 , indice_noeud ,nb_pt_vir = 1 ;
    f= db ;
    char tmp[100]  ;
    int ind_tmp = 0 ;

    fseek(f,53,SEEK_SET) ; // sauter la première ligne du fichier
    chemploi*chemp =(chemploi*)malloc(sizeof(chemploi)) ;
    groupe_chemplois* g = (groupe_chemplois*)malloc(sizeof(groupe_chemplois)) ;

    FILE *dba = fopen("test/employe.csv", "r");
    groupe_employes* gr = gemp_open(dba);
    fclose(dba);

    if(f)
    {
        while(ligne <= 6)
        {
            c = fgetc(f) ;
            //printf("%c",c) ;
            if(c != ',' && c != ';' && c != '\n' && c != EOF)
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
                    if(ind_sortie_virgule == 1) chemp->id = atoi(tmp) ;
                    else if(ind_sortie_virgule == 2) strcpy(chemp->nom ,tmp) ;
                    else if(ind_sortie_virgule == 3) strcpy(chemp->prenom ,tmp) ;
                    else if(ind_sortie_virgule == 4) strcpy(chemp->mail,tmp) ;
                    else if(ind_sortie_virgule == 5) chemp->code_postale  = atoi(tmp) ;
                    else if(ind_sortie_virgule == 6)
                    {
                        strcpy(chemp->competence[ind_sortie_pt_virgule] ,tmp) ;
                        nb_pt_vir = 2 ;
                        for(int i = ind_sortie_pt_virgule+1 ;i< MAX_COMP ;i++)
                        {
                            chemp->competence[i][0] = '\0' ;
                        }
                        ind_sortie_pt_virgule = 0 ;
                    }
                    /*
                    else
                    {
                       strcpy(chemp->adresse,tmp) ;
                       ind_sortie_virgule = 0 ;
                    }
                    */
                }
                // if(c == '\n') || (c == ';') || (c == EOF)

                else
                {
                    if(c == ';')
                    {
                        if(nb_pt_vir == 1)
                        {
                            strcpy(chemp->competence[ind_sortie_pt_virgule] ,tmp) ;
                            ind_sortie_pt_virgule++ ;
                        }
                        else
                        {
                            if(tmp[0] != '\0')
                            {
                              chemp->collegues[ind_sortie_pt_virgule] = (chemploi*)malloc(sizeof(chemploi)) ;
                              chemp->collegues[ind_sortie_pt_virgule++]->id = atoi(tmp) ;
                            }
                            else chemp->collegues[ind_sortie_pt_virgule++] = NULL ;
                        }
                    }
                    if(c == '\n' || c == EOF )
                    {
                        if(tmp[0] != '\0')
                        {
                          chemp->collegues[ind_sortie_pt_virgule] = (chemploi*)malloc(sizeof(chemploi)) ;
                          chemp->collegues[ind_sortie_pt_virgule++]->id = atoi(tmp) ;
                        }
                        else chemp->collegues[ind_sortie_pt_virgule++] = NULL ;

                        for(int j= ind_sortie_pt_virgule;j< MAX_COLLEGUES ;j++)
                        {
                              chemp->collegues[j] = NULL ;
                        }
                        ind_sortie_pt_virgule = 0 ;
                        ind_sortie_virgule = 0 ;
                        nb_pt_vir = 1 ;
                        ligne++ ;
                        //printf("\n") ;
                        indice_noeud = chemp->id ;
                        if(indice_noeud== 1)
                        {
                            g->chemplois = l_make_node((chemploi*)chemp) ;
                        }
                        else
                        {
                            l_append(&(g->chemplois),l_make_node((chemploi*)chemp)) ;
                        }
                        chemp =(chemploi*)malloc(sizeof(chemploi)) ;
                    }
                }
                ind_tmp = 0 ;
            }
        }
        // ici il faut remplir les champs de la struct chemploi pour chaque ptr de collegues de chaque noeud ,
        node* tmp1 = g->chemplois ;
        while(tmp1)
        {
            chemploi* tmp2 =(chemploi*)tmp1->data ;

            for(int i= 0;i<MAX_COLLEGUES;i++)
            {
                if(tmp2->collegues[i])
                {
                    tmp2->collegues[i] = gemp_id(gr,tmp2->collegues[i]->id) ;
                }
            }
            tmp1 = tmp1->next ;
        }
        fclose(f);
    }
    return g;
}

chemploi* gchemp_id(groupe_chemplois* g, int const id)
{
    node * ptr = g->chemplois ;
    while(ptr && ((chemploi*)ptr->data)->id != id) ptr = ptr->next ;
    if(ptr) return (chemploi*)ptr->data  ;
    return NULL ;
}
int gchemp_size(groupe_chemplois* g)
{
    return l_length(g->chemplois);
}
void voir_chemplois(groupe_chemplois* g)
{
    node * tmp1 = g->chemplois ;
    chemploi * tmp2  ;
    while(tmp1)
    {
        tmp2 = (chemploi *)tmp1->data ;
        tmp1 = tmp1->next ;
    }
}



void rechercher_chemploi_par_competences(groupe_chemplois * g,int id_poste)
{
    int i,j,t,len = gchemp_size(g) ;
    tab2 tab [len] ;
    for (i = 0 ;i <len ;i++)
    {
        tab[i].a = i+1 ;
        tab[i].b = 0 ;
    }
    node * ptr2 = g->chemplois ;

    FILE *db = fopen("test/poste.csv", "r");
    groupe_postes *gr = gp_open(db);
    fclose(db);
    poste * ptrf = gp_id(gr,id_poste) ;
    chemploi * chemp ;
    i = 0 ;
    t = 0 ;
    while(ptr2)
    {
            j = 0 ;
            while( ((chemploi*)ptr2->data)->competence[j][0] != '\0')
            {
                if(strcmp(ptrf->competence[i],((chemploi*)ptr2->data)->competence[j]) == 0)
                {
                      tab[t].b++ ;
                      j++ ;
                      i = 0 ;
                }
                else i++ ;
                if(ptrf->competence[i][0] == '\0')
                {
                    i = 0 ;
                    j++ ;
                }
            }
            ptr2 = ptr2->next ;
            t++ ;
    }
    qsort(tab,len,sizeof(tab2),compart_int_b) ;
    printf("nom ,prenom ,mail\n") ;

    i = 0  ;
    while(tab[i].b != 0 && i <len )
    {
            chemp = gchemp_id(g,tab[i].a) ;
            printf("%s,%s,%s\n",chemp->nom,chemp->prenom,chemp->mail) ;
            i++ ;

    }
}



void rechercher_chemploi_par_competences_et_code_postale(groupe_chemplois * g,int id_poste,int code_postale)
{
    int i,j,t,len = gchemp_size(g) ; //,code_postale selon idee de code_postale
    tab3 tab [len] ;
    for (i = 0 ;i <len ;i++)
    {
        tab[i].a = i+1 ;
        tab[i].b = 0 ;
        tab[i].c = 0 ;
    }
    node * ptr2 = g->chemplois ;

    FILE *db = fopen("test/poste.csv", "r");
    groupe_postes *gr = gp_open(db);
    fclose(db);
    poste * ptrf = gp_id(gr,id_poste) ;
    //code_postale = ptrf->entrep->code_postale ; selon idee de code_postale
    chemploi * chemp ;
    i = 0 ;
    t = 0 ;
    while(ptr2)
    {
            if(((chemploi*)ptr2->data)->code_postale == code_postale )
            {
                j = 0 ;
                while( ((chemploi*)ptr2->data)->competence[j][0] != '\0')
                {
                    if(strcmp(ptrf->competence[i],((chemploi*)ptr2->data)->competence[j]) == 0)
                    {
                          tab[t].b++ ;
                          j++ ;
                          i = 0 ;
                    }
                    else i++ ;
                    if(ptrf->competence[i][0] == '\0')
                    {
                        i = 0 ;
                        j++ ;
                    }
                }
            }
            if(tab[t].b != 0 && ((chemploi*)ptr2->data)->code_postale == code_postale) tab[t].c = 1 ; //faculatif
            ptr2 = ptr2->next ;
            t++ ;
    }
    qsort(tab,len,sizeof(tab3),compart_int_b_c) ;
    printf("nom ,prenom ,mail\n") ;
    i = 0  ;
    while(tab[i].b != 0 && tab[i].c != 0 && i <len )
    {
            chemp = gchemp_id(g,tab[i].a) ;
            printf("%s,%s,%s\n",chemp->nom,chemp->prenom,chemp->mail) ;
            i++ ;
    }
}

void creer_profil_chemploi(groupe_chemplois * g)
{
    /*
    int id;
    char nom[128] ;
    char prenom[128] ;
    char mail[128] ;
    int code_postale ;
    char competence[5][128] ;
    employe * collegues[MAX_COLLEGUES];
    */
    int i,nb_comp ;
    int id_employe,nb_employe ;

    chemploi * chemp = (chemploi *)malloc(sizeof(chemploi)) ;

    chemp->id =  gchemp_size(g)+1 ;
    printf("nom = ") ;
    scanf("%s",&chemp->nom) ;
    printf("prenom = ") ;
    scanf("%s",&chemp->prenom) ;
    printf("mail = ") ;
    scanf("%s",&chemp->mail) ;
    printf("code_postale = ") ;
    scanf("%d",&chemp->code_postale) ;

    printf("nb_comp = ") ;
    scanf("%d",&nb_comp) ;
    for(i = 0 ;i< nb_comp ;i++)
    {
      printf("competence[%d] = ",i) ;
      scanf("%s",&chemp->competence[i]) ;
    }
    for(i = nb_comp ;i< MAX_COMP ;i++)
    {
        chemp->competence[i][0] = '\0' ;
    }
    printf("nb_employe = ") ;
    scanf("%d",&nb_employe) ;
    FILE *db = fopen("test/employe.csv", "r");
    groupe_employes* gr = gemp_open(db);
    fclose(db);
    for(i = 0 ;i< nb_employe ;i++)
    {
        printf("id_employe = ",id_employe) ;
        scanf("%d",&id_employe) ;
        chemp->collegues[i] = gemp_id(gr,id_employe) ;
    }
    for(i = nb_employe ;i< MAX_COLLEGUES ;i++) chemp->collegues[i] = NULL ;
    l_append(&(g->chemplois),l_make_node((chemploi*)chemp)) ;

}

void modifier_profil_chemploi(groupe_chemplois * g,int id_chemploi)
{
    int choix ;
    printf("si vous voulez\nAjouter des compétences : 1\nAjouter un(e) ancien(ne) collègue de travail : 2\nModifier le code postal :3\n") ;
    printf("entrer le numéro : ") ;
    scanf("%d",&choix) ;

    int i,j,nb_competences ,id_employe,nv_code_postale ;
    FILE *db = fopen("test/employe.csv", "r");
    groupe_employes* gr = gemp_open(db);
    fclose(db);
    chemploi * ptr = gchemp_id(g,id_chemploi) ;

    switch(choix)
    {
       case 1 :
           // Ajouter des compétences

           printf("nb_competences =  ") ;
           scanf("%d",&nb_competences) ;
           i = 0 ;
           while(ptr->competence[i][0] != '\0') i++ ;
           for(j = i ;j < i+nb_competences ;j++)
           {
               printf("competence[%d] = ",j) ;
               scanf("%s",&ptr->competence[j]) ;
           }
           break ;
      case 2 :
          //Ajouter un(e) ancien(ne) collègue de travail
          i = 0 ;
          while(ptr->collegues[i]) i++ ;
          printf("id_employe =  ") ;
          scanf("%d",&id_employe) ;
          ptr->collegues[i] = gemp_id(gr,id_employe) ;
          break ;
      case 3 :
          //Modifier le code postal

          printf("nv_code_postale =  ") ;
          scanf("%d",&nv_code_postale) ;
          ptr->code_postale  = nv_code_postale ;
          break ;
      default :
          printf("le choix fait n'existe pas\n") ;
    }
}

void supprimer_profil_chemploi(groupe_chemplois * g,int id_chemploi)
{
    node *tmp1 = g->chemplois ;

    while(tmp1)
    {
        if(((chemploi*)tmp1->data)->id == id_chemploi)
        {
            if(!tmp1->previous) g->chemplois = l_remove(tmp1) ;
            l_remove(tmp1) ;
            return ;
        }
        tmp1= tmp1->next ;
    }
}


void transitionner_chempl_employe(groupe_chemplois *g,groupe_employes *gr,int id_chemploi,int id_entreprise)
{
    int i ;
    chemploi * ptrch = gchemp_id(g,id_chemploi) ;
    employe *  ptremp = (employe *)malloc(sizeof(employe)) ;



    ptremp->id = gemp_size(gr)+1  ;
    strcpy(ptremp->nom ,ptrch->nom) ;
    strcpy(ptremp->prenom ,ptrch->prenom) ;
    strcpy(ptremp->mail ,ptrch->mail) ;
    ptremp->code_postale = ptrch->code_postale ;

    i = 0 ;
    while(i < MAX_COMP)
            strcpy(ptremp->competence[i] ,ptrch->competence[i++]) ;

    i = 0 ;
    while(i < MAX_COLLEGUES)
    {
            ptremp->collegues[i] =  ptrch->collegues[i] ;
            i++ ;
    }
    FILE *db2 = fopen("test/entreprise.csv", "r");
    groupe_entreprises * gr2 = ge_open(db2);
    fclose(db2);

    ptremp->entrep = ge_id(gr2,id_entreprise) ;
    l_append(&(gr->employes),l_make_node((employe*)ptremp)) ;
    supprimer_profil_chemploi(g, ptrch->id) ;
}

int in_tab_collegues(employe * collegues[MAX_COLLEGUES],employe * ptr)
{
    int i = 0 ;
    while(i<MAX_COLLEGUES && collegues[i])
    {
        if(collegues[i] == ptr) return 1 ;
        i++ ;
    }
    return 0 ;
}

 // a tester
void transitionner_employe_chempl(groupe_employes *g,groupe_chemplois *gr,int id_employe)
{
    int i ,id_entreprise ;
    employe * ptre = gemp_id(g,id_employe) ;
    chemploi *  ptrc = (chemploi *)malloc(sizeof(chemploi)) ;

    ptrc->id = gchemp_size(gr)+1  ;
    strcpy(ptrc->nom ,ptre->nom) ;
    strcpy(ptrc->prenom ,ptre->prenom) ;
    strcpy(ptrc->mail ,ptre->mail) ;
    ptrc->code_postale = ptre->code_postale ;

    i = 0 ;
    while(i < MAX_COMP)
            strcpy(ptrc->competence[i] ,ptre->competence[i++]) ;

    i = 0 ;
    while(i < MAX_COLLEGUES)
    {
            ptrc->collegues[i] =  ptre->collegues[i] ;
            i++ ;
    }


    FILE *db2 = fopen("test/entreprise.csv", "r");
    groupe_entreprises * gr2 = ge_open(db2);
    fclose(db2);

    //employe * pt2 ;

    i = 0 ;
    while(ptrc->collegues[i]) i++ ;
    id_entreprise = ptre->entrep->id ;
    node  * pt = g->employes ;
    while(pt)
    {
        if(((employe *)pt->data)->id != ptre->id && ((employe *)pt->data)->entrep->id == id_entreprise   )
        {
             if(!in_tab_collegues(ptrc->collegues,(employe *)pt->data))  ptrc->collegues[i++] = (employe *)pt->data ;
        }
        pt = pt->next ;
    }
    l_append(&(gr->chemplois),l_make_node((chemploi *)ptrc)) ;
    supprimer_profil_employe(g, ptre->id) ;
}


//////////////recherche




void rechercher_poste_chemp_par_competences(groupe_postes * g,groupe_chemplois *gr,int id_chemploi)
{
    int i,j,t,len = gp_size(g) ;
    tab2 tab [len] ;
    //int tab_id[len] ;
    for (i = 0 ;i <len ;i++)
    {
        tab[i].a = i+1 ;
        tab[i].b = 0 ;
        //tab_id[i] = 0 ;
    }
    node * ptr2 = g->postes ;


    chemploi * ptrf = gchemp_id(gr,id_chemploi) ;
    poste * pos ;
    i = 0 ;
    t = 0 ;
    while(ptr2)
    {
            j = 0 ;
            while( ((poste*)ptr2->data)->competence[j][0] != '\0')
            {
                if(strcmp(ptrf->competence[i],((poste*)ptr2->data)->competence[j]) == 0)
                {
                      tab[t].b++ ;
                      j++ ;
                      i = 0 ;
                }
                else i++ ;
                if(ptrf->competence[i][0] == '\0')
                {
                    i = 0 ;
                    j++ ;
                }
            }
            ptr2 = ptr2->next ;
            t++ ;
    }
    qsort(tab,len,sizeof(tab2),compart_int_b) ;
    printf("titre du poste, Nom de l'entreprise ,Adresse mail de l'entreprise,Code postal de l'entreprise \n") ;

    i = 0  ;
    while(tab[i].b != 0 && i <len )
    {
            pos = gp_id(g,tab[i].a) ;
            printf("%s,%s,%s,%d\n",pos->titre,pos->entrep->nom,pos->entrep->mail,pos->entrep->code_postale) ;
            i++ ;

    }
}


void rechercher_poste_chemp_par_competences_et_code_postale(groupe_postes * g,groupe_chemplois *gr,int id_chemploi,int code_postale)
{
    int i,j,t,len = gp_size(g) ;  //,code_postale selon idee de code_postale
    tab3 tab [len] ;
    for (i = 0 ;i <len ;i++)
    {
        tab[i].a = i+1 ;
        tab[i].b = 0 ;
        tab[i].c = 0 ;
    }
    node * ptr2 = g->postes ;


    chemploi * ptrf = gchemp_id(gr,id_chemploi) ;
    //code_postale = ptrf->entrep->code_postale ; selon idee de code_postale
    poste * pos ;
    i = 0 ;
    t = 0 ;
    while(ptr2)
    {
            if(((poste*)ptr2->data)->entrep->code_postale == code_postale )
            {
                j = 0 ;
                while( ((poste*)ptr2->data)->competence[j][0] != '\0')
                {
                    if(strcmp(ptrf->competence[i],((poste*)ptr2->data)->competence[j]) == 0)
                    {
                          tab[t].b++ ;
                          j++ ;
                          i = 0 ;
                    }
                    else i++ ;
                    if(ptrf->competence[i][0] == '\0')
                    {
                        i = 0 ;
                        j++ ;
                    }
                }
            }
            if(tab[t].b != 0 && ((poste*)ptr2->data)->entrep->code_postale == code_postale) tab[t].c = 1 ; //faculatif
            ptr2 = ptr2->next ;
            t++ ;
    }
    qsort(tab,len,sizeof(tab3),compart_int_b_c) ;
    printf("titre du poste, Nom de l'entreprise ,Adresse mail de l'entreprise,Code postal de l'entreprise \n") ;
    i = 0  ;
    while(tab[i].b != 0 && tab[i].c != 0 && i <len )
    {
        pos = gp_id(g,tab[i].a) ;
        printf("%s,%s,%s,%d\n",pos->titre,pos->entrep->nom,pos->entrep->mail,pos->entrep->code_postale) ;
        i++ ;
    }
}

void rechercher_employe_chemp_par_entreprise(groupe_chemplois *g,int id_chemploi,int id_entreprise)
{
    chemploi * ptrf = gchemp_id(g,id_chemploi) ;

    printf("Nom du (de la) collègue, Prénom du (de la) collègue ,Adresse mail du (de la) collègue \n") ;
    int i = 0 ;
    while(ptrf->collegues[i])
    {
        if(ptrf->collegues[i]->entrep->id == id_entreprise)
        {
            printf("%s,%s,%s\n",ptrf->collegues[i]->nom,ptrf->collegues[i]->prenom,ptrf->collegues[i]->mail) ;
        }
        i++ ;
    }
}




void rechercher_employe_chemp_par_competences(groupe_chemplois *g,groupe_postes * g1,int id_chemploi)
{

      int i,j,t,len = gp_size(g1) ;
      tab2 tab [len] ;
      int tab_id[len] ;

      for (i = 0 ;i <len ;i++)
      {
          tab[i].a = i+1 ;
          tab[i].b = 0 ;
          tab_id[i] = 0 ;
      }
      node * ptr2 = g1->postes ;


      chemploi * ptrf = gchemp_id(g,id_chemploi) ;
      poste * pos ;
      i = 0 ;
      t = 0 ;
      if(ptrf->collegues[i])
      {
          while(ptr2)
          {
                  j = 0 ;
                  while( ((poste*)ptr2->data)->competence[j][0] != '\0')
                  {
                      pos = ((poste*)ptr2->data) ; // voir
                      if(strcmp(ptrf->competence[i],((poste*)ptr2->data)->competence[j]) == 0)
                      {
                            tab[t].b++ ;
                            j++ ;
                            i = 0 ;
                      }
                      else i++ ;
                      if(ptrf->competence[i][0] == '\0')
                      {
                          i = 0 ;
                          j++ ;
                      }
                  }
                  ptr2 = ptr2->next ;
                  t++ ;
          }
          qsort(tab,len,sizeof(tab2),compart_int_b) ;
          i = 0  ;
          while(tab[i].b != 0 && i <len )
          {
                  pos = gp_id(g1,tab[i].a) ;
                  if(!in_tab_id (len,tab_id,pos->entrep->id)) tab_id[i] = pos->entrep->id ; // ne pas entré s'il est deja la-bas
                  i++ ;
          }
      }

      i = 0 ;
      while(ptrf->collegues[i])
      {
          if(in_tab_id (len,tab_id,ptrf->collegues[i]->entrep->id))
          {
              printf("%s,%s,%s\n",ptrf->collegues[i]->nom,ptrf->collegues[i]->prenom,ptrf->collegues[i]->mail) ;
          }
          i++ ;
      }
}
