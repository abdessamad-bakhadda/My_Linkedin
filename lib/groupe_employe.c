#include "groupe_employe.h"


#include "liste.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////// EMPLOYE  ////////////////////////////////////////////////
employe* gemp_id(groupe_employes* g, int const id)
{
    node * ptr = g->employes ;
    while(ptr && ((employe*)ptr->data)->id != id) ptr = ptr->next ;
    if(ptr) return (employe*)ptr->data  ;
    return NULL ;
}

groupe_employes* gemp_open(FILE *db){
    FILE *f;
    char c;
    int ligne = 1 ,ind_sortie_virgule = 0 ,ind_sortie_pt_virgule = 0, indice_noeud ,nb_pt_vir = 1 ;
    f= db ;
    char tmp[100]  ;
    int ind_tmp = 0 ;

    fseek(f,64,SEEK_SET) ; // sauter la première ligne du fichier
    employe* emp =(employe*)malloc(sizeof(employe)) ;
    groupe_employes* g = (groupe_employes*)malloc(sizeof(groupe_employes)) ;

    FILE *dba = fopen("test/entreprise.csv", "r");
    groupe_entreprises* gr = ge_open(dba);
    fclose(dba);

    if(f)
    {
        while(ligne <= 4)
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
                    if(ind_sortie_virgule == 1) emp->id = atoi(tmp) ;
                    else if(ind_sortie_virgule == 2) strcpy(emp->nom ,tmp) ;
                    else if(ind_sortie_virgule == 3) strcpy(emp->prenom ,tmp) ;
                    else if(ind_sortie_virgule == 4) strcpy(emp->mail,tmp) ;
                    else if(ind_sortie_virgule == 5) emp->code_postale  = atoi(tmp) ;
                    else if(ind_sortie_virgule == 6)
                    {
                        strcpy(emp->competence[ind_sortie_pt_virgule] ,tmp) ;
                        nb_pt_vir = 2 ;
                        ind_sortie_pt_virgule = 0 ;
                    }
                    else if(ind_sortie_virgule == 7 )
                    {
                        if (tmp[0] != '\0')
                        {
                              emp->collegues[ind_sortie_pt_virgule] = (employe*)malloc(sizeof(employe)) ;
                              emp->collegues[ind_sortie_pt_virgule++]->id = atoi(tmp) ;
                        }
                        else emp->collegues[ind_sortie_pt_virgule++] = NULL ;
                    }
                    /*
                    else
                    {
                       strcpy(emp->adresse,tmp) ;
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
                            strcpy(emp->competence[ind_sortie_pt_virgule] ,tmp) ;
                            ind_sortie_pt_virgule++ ;
                        }
                        else
                        {
                            emp->collegues[ind_sortie_pt_virgule] = (employe*)malloc(sizeof(employe)) ;
                            emp->collegues[ind_sortie_pt_virgule++]->id = atoi(tmp) ;
                        }

                    }
                    if(c == '\n' || c == EOF )
                    {
                        /////
                        emp->entrep = ge_id(gr,atoi(tmp)) ;
                        for(int j= ind_sortie_pt_virgule;j< MAX_COLLEGUES ;j++)
                        {
                              emp->collegues[j] = NULL ;
                        }
                        ind_sortie_pt_virgule = 0 ;
                        ind_sortie_virgule = 0 ;
                        nb_pt_vir = 1 ;
                        ligne++ ;
                        //printf("\n") ;
                        indice_noeud = emp->id ;
                        if(indice_noeud== 1)
                        {
                            g->employes = l_make_node((employe*)emp) ;
                        }
                        else
                        {
                            l_append(&(g->employes),l_make_node((employe*)emp)) ;
                        }
                        emp =(employe*)malloc(sizeof(employe)) ;
                    }
                }
                ind_tmp = 0 ;
            }
        }
        // ici il faut remplir les champs de la struct employe pour chaque ptr de collegues de chaque noeud ,
        node* tmp1 = g->employes ;
        while(tmp1)
        {
            employe* tmp2 =(employe*)tmp1->data ;

            for(int i= 0;i<MAX_COLLEGUES;i++)
            {
                if(tmp2->collegues[i])
                {
                    tmp2->collegues[i] = gemp_id(g,tmp2->collegues[i]->id) ;
                }
            }
            tmp1 = tmp1->next ;
        }
        fclose(f);
    }
    return g;
}

int gemp_size(groupe_employes* g)
{
    return l_length(g->employes);
}

void voir_employes(groupe_employes* g)
{
    node * tmp1 = g->employes ;
    employe * tmp2  ;
    while(tmp1)
    {
        tmp2 = (employe *)tmp1->data ;
        tmp1 = tmp1->next ;
    }
}

 // a tester
void creer_profil_employe(groupe_employes * g,groupe_entreprises *gr)
{
    /*
    int id;
    char nom[128] ;
    char prenom[128] ;
    char mail[128] ;
    int code_postale ;
    char competence[MAX_COMP][128] ;
    struct employe * collegues[MAX_COLLEGUES];
    entreprise * entrep ;
    */


    int i,nb_comp ;
    int id_employe,nb_employe,id_entreprise ;

    employe * emp = (employe *)malloc(sizeof(employe)) ;

    emp->id =  gemp_size(g)+1 ;
    printf("nom = ") ;
    scanf("%s",&emp->nom) ;
    printf("prenom = ") ;
    scanf("%s",&emp->prenom) ;
    printf("mail = ") ;
    scanf("%s",&emp->mail) ;
    printf("code_postale = ") ;
    scanf("%d",&emp->code_postale) ;

    printf("nb_comp = ") ;
    scanf("%d",&nb_comp) ;
    for(i = 0 ;i< nb_comp ;i++)
    {
      printf("competence[%d] = ",i) ;
      scanf("%s",&emp->competence[i]) ;
    }
    for(i = nb_comp ;i< MAX_COMP ;i++)
    {
        emp->competence[i][0] = '\0' ;
    }
    printf("nb_employe = ") ;
    scanf("%d",&nb_employe) ;

    for(i = 0 ;i< nb_employe ;i++)
    {
        printf("id_employe = ",id_employe) ;
        scanf("%d",&id_employe) ;
        emp->collegues[i] = gemp_id(g,id_employe) ;
    }
    for(i = nb_employe ;i< MAX_COLLEGUES ;i++) emp->collegues[i] = NULL ;

    printf("id_entreprise = ") ;
    scanf("%d",&id_entreprise) ;
    emp->entrep = ge_id(gr,id_entreprise) ;

    //emp->entrep = NULL ;
    l_append(&(g->employes),l_make_node((employe*)emp)) ;
}


 // a tester
void modifier_profil_employe(groupe_employes * g,groupe_entreprises *gr,int id_employe)
{

    int choix ;
    printf("si vous voulez\nAjouter des compétences : 1\nAjouter un(e) ancien(ne) collègue de travail : 2\nModifier le code postal :3\nModifier l'entreprise :4\n") ;
    printf("entrer le numéro : ") ;
    scanf("%d",&choix) ;



    int i,j,nb_competences ,nv_code_postale,id_entreprise ;
    employe * ptr = gemp_id(g,id_employe) ;


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
          ptr->collegues[i] = gemp_id(g,id_employe) ;
          break ;
      case 3 :
          //Modifier le code postal

          printf("nv_code_postale =  ") ;
          scanf("%d",&nv_code_postale) ;
          ptr->code_postale  = nv_code_postale ;
          break ;
      case 4 :
          //Modifier l'entreprise
          printf("id_entreprise =  ") ;
          scanf("%d",&id_entreprise) ;
          ptr->entrep = ge_id(gr,id_entreprise) ;
          break ;

      default :
          printf("le choix fait n'existe pas\n") ;
    }
}

 // a tester
void supprimer_profil_employe(groupe_employes * g,int id_employe)
{
    node *tmp1 = g->employes ;
    while(tmp1)
    {
        if(((employe*)tmp1->data)->id == id_employe)
        {
            if(!tmp1->previous) g->employes = l_remove(tmp1) ;
            else l_remove(tmp1) ;
            return ;
        }
        tmp1= tmp1->next ;
    }
}

//////////////recherch2

//a tester

int compart_int_b ( const void * first, const void * second ) {
  return -( (*(tab2*)first).b  - (*(tab2*)second).b );
}


void rechercher_poste_emp_par_competences(groupe_postes * g,groupe_employes *gr,int id_employe)
{
    int i,j,t,len = gp_size(g) ;
    tab2 tab [len] ;
    for (i = 0 ;i <len ;i++)
    {
        tab[i].a = i+1 ;
        tab[i].b = 0 ;
    }
    node * ptr2 = g->postes ;


    employe * ptrf = gemp_id(gr,id_employe) ;
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

int compart_int_b_c ( const void * first, const void * second ) {
  return -( (*(tab3*)first).b  - (*(tab3*)second).b );
}

void rechercher_poste_emp_par_competences_et_code_postale(groupe_postes * g,groupe_employes *gr,int id_employe,int code_postale)
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


    employe * ptrf = gemp_id(gr,id_employe) ;
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

//a tester
// recherche final


void rechercher_employe_emp_par_entreprise(groupe_employes * g,int id_employe,int id_entreprise)
{
    employe * ptrf = gemp_id(g,id_employe) ;

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


int in_tab_id (int n ,int tab_id[n],int e)
{
    int i = 0 ;
    while(i < n && tab_id[i] != 0)
    {
        if(tab_id[i] == e) return 1 ;
        i++ ;
    }
    return 0 ;
}

void rechercher_employe_emp_par_competences(groupe_employes * g,groupe_postes *g1,int id_employe)
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


      employe * ptrf = gemp_id(g,id_employe) ;
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

      printf("Nom du (de la) collègue, Prénom du (de la) collègue ,Adresse mail du (de la) collègue \n") ;
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


/*
void creer_profil_employe(groupe_employes* g,int id,char nom[128],char prenom[128],char mail[128],int code_postale,char competence[MAX_COMP][128],employe * collegues[MAX_COLLEGUES],entreprise * entrep )
{

    int i ;
    employe * emp = (employe *)malloc(sizeof(employe)) ;

    emp->id = id  ;// gemp_size(g)+1 ;
    strcpy(emp->nom,nom) ;
    strcpy(emp->prenom,prenom) ;
    strcpy(emp->mail,mail) ;
    emp->code_postale = code_postale ;

    for(i = 0 ;i< MAX_COMP ;i++)
    {
        strcpy(emp->competence[i],competence[i]) ;
    }

    for(i = 0 ;i< MAX_COLLEGUES ;i++)
    {
        emp->collegues[i] = collegues[i] ;
    }
    emp->entrep = entrep ;
    l_append(&(g->employes),l_make_node((employe*)emp)) ;
}
*/
