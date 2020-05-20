#include "groupe_chemploi.h"

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main_interface()
{
    //printf("p = %d\n",atoi('p')) ;
    //printf("q = %d\n",atoi('q')) ;

    // entreprise
    FILE *db1 = fopen("test/entreprise.csv", "r");
    groupe_entreprises *ge = ge_open(db1);
    fclose(db1);

    voir_entreprises(ge) ;
    int id_entreprise ;

    // poste
    FILE *db2 = fopen("test/poste.csv", "r");
    groupe_postes *gp = gp_open(db2);
    fclose(db2);

    voir_postes(gp) ;
    int id_poste ;
    // employe
    FILE *db3 = fopen("test/employe.csv", "r");
    groupe_employes *gemp = gemp_open(db3);
    fclose(db3);

    voir_employes(gemp) ;
    int id_employe ;

    // chemploi
    FILE *db4 = fopen("test/chemploi.csv", "r");
    groupe_chemplois *gchemp = gch_open(db4);
    fclose(db4);

    voir_chemplois(gchemp) ;
    int id_chemploi ;

    int code_postale ;

    //////
    char choix[1] ;

    char choix1_1[1] ;
    char choix1_2[1] ;

    char choix2_1[1] ;
    char choix2_2[1] ;
    char choix2_3[1] ;

    char choix3_1[1] ;
    char choix3_2[1] ;
    char choix3_3[1] ;

    printf("*** Bienvenu sur LuminIn, le site des pros *** \n* Menu principal * \nVous êtes :\n1. Une entreprise\n2. À la recherche d'un emploi\n3. Un employé\n") ;
    printf("Votre choix ('q' pour quitter) : ") ;
    scanf("%s",&choix) ;

    if (strcmp(choix , "q") == 0)   exit(EXIT_SUCCESS) ;
    switch(atoi(choix))
    {
        case 1 :

                printf("\n\n*** Bienvenu sur LuminIn, le site des pros ***\n* Menu entreprise *\nVous voulez :\n") ;
                printf("1. Créer le profil de votre entreprise\n") ;
                printf("2. Supprimer le profil de votre entreprise\n") ;
                printf("3. Créer le profil d'un poste à pourvoir\n") ;
                printf("4. Supprimer le profil d'un poste maintenant pourvu\n") ;
                printf("5. Faire une recherche parmi les chercheurs d'emploi\n") ;

                printf("Votre choix ('q' pour quitter, 'p' pour menu précédent) : ") ;
                scanf("%s",&choix1_1) ;

                if (strcmp(choix1_1 , "q") == 0)   exit(EXIT_SUCCESS) ;
                else if (strcmp(choix1_1 , "p") == 0) main_interface() ;
                switch(atoi(choix1_1))
                {
                      case 1 :
                              cree_profile_entrep(ge) ;
                              voir_entreprises(ge) ;
                              break ;
                      case 2 :
                              printf("entrer votre id_entreprise : ") ;
                              scanf("%d",&id_entreprise) ;
                              supprime_profile_entrep(ge,gp,id_entreprise) ;
                              voir_entreprises(ge) ;
                              break ;
                      case 3 :
                              cree_profile_poste(gp) ;
                              voir_postes(gp) ;
                              break ;
                      case 4 :
                              printf("entrer l'id du poste : ") ;
                              scanf("%d",&id_poste) ;
                              supprimer_profile_poste(gp,id_poste) ;
                              voir_postes(gp) ;
                              break ;
                      case 5 :
                              printf("\nVous voulez :\n") ;
                              printf("1. Faire une recherche parmi les chercheurs d'emploi par compétences\n") ;
                              printf("2. Faire une recherche parmi les chercheurs d'emploi par compétences et code postal\n") ;
                              printf("Votre choix ('q' pour quitter) : ") ;
                              scanf("%s",&choix1_2) ;
                              if (atoi(choix1_2) == 1)
                              {
                                  printf("entrer l'id du poste : ") ;
                                  scanf("%d",&id_poste) ;
                                  rechercher_chemploi_par_competences(gchemp,id_poste) ;
                              }
                              else if (atoi(choix1_2) == 2)
                              {
                                  printf("entrer l'id du poste : ") ;
                                  scanf("%d",&id_poste) ;
                                  printf("entrer le code_postale : ") ;
                                  scanf("%d",&code_postale) ;
                                  rechercher_chemploi_par_competences_et_code_postale(gchemp,id_poste,code_postale) ;
                              }
                              break ;
                }
                break ;

        case 2 :
                printf("\n\n*** Bienvenu sur LuminIn, le site des pros ***\n* Menu chercheur d'emploi *\nVous voulez :\n") ;
                printf("1. Créer votre profil chercheur d'emploi\n") ;
                printf("2. Modifier votre profil chercheur d'emploi\n") ;
                printf("3. Transitionner votre profil chercheur d'emploi à un profile employé\n") ;
                printf("4. Supprimer votre profil chercheur d'emploi \n") ;
                printf("5. Faire une recherche parmi les postes à pourvoir correspondant à votre profil chercheur d'emploi\n") ;
                printf("6. Faire une recherche parmi les anciens collègues\n") ;

                printf("Votre choix ('q' pour quitter, 'p' pour menu précédent) : ") ;
                scanf("%s",&choix2_1) ;
                if (strcmp(choix2_1 , "q") == 0)   exit(EXIT_SUCCESS) ;
                else if (strcmp(choix2_1 , "p") == 0) main_interface() ;
                switch(atoi(choix2_1))
                {
                      case 1 :
                              creer_profil_chemploi(gchemp) ;
                              voir_chemplois(gchemp) ;
                              break ;
                      case 2 :
                              printf("entrer votre id_chemploi : ") ;
                              scanf("%d",&id_chemploi) ;
                              modifier_profil_chemploi(gchemp,id_chemploi) ;
                              voir_chemplois(gchemp) ;
                              break ;
                      case 3 :
                              printf("entrer votre id_chemploi : ") ;
                              scanf("%d",&id_chemploi) ;
                              printf("entrer l'id de l'entrprise auquel vous êtes devenu employé : ") ;
                              scanf("%d",&id_entreprise) ;
                              transitionner_chempl_employe(gchemp,gemp,id_chemploi,id_entreprise) ;
                              voir_chemplois(gchemp) ;
                              voir_employes(gemp) ;
                              break ;
                      case 4 :
                              printf("entrer votre id_chemploi : ") ;
                              scanf("%d",&id_chemploi) ;
                              supprimer_profil_chemploi(gchemp,id_chemploi) ;
                              voir_chemplois(gchemp) ;
                              break ;
                      case 5 :
                              printf("\nVous voulez :\n") ;
                              printf("1. Faire une recherche parmi les postes à pourvoir par compétences\n") ;
                              printf("2. Faire une recherche parmi les postes à pourvoir par compétences et code postal\n") ;
                              printf("Votre choix ('q' pour quitter) : ") ;
                              scanf("%s",&choix2_2) ;

                              printf("entrer votre id_chemploi : ") ;
                              scanf("%d",&id_chemploi) ;
                              if (atoi(choix2_2) == 1) rechercher_poste_chemp_par_competences(gp,gchemp,id_chemploi) ;
                              else if (atoi(choix2_2) == 2)
                              {
                                  printf("entrer le code_postale : ") ;
                                  scanf("%d",&code_postale) ;
                                  rechercher_poste_chemp_par_competences_et_code_postale(gp,gchemp,id_chemploi,code_postale) ;
                              }
                              break ;
                      case 6 :
                              printf("\nVous voulez :\n") ;
                              printf("1. Faire une recherche parmi les anciens collègues par entreprise \n") ;
                              printf("2. Faire une recherche parmi les anciens collègues par compétences \n") ;
                              printf("Votre choix ('q' pour quitter) : ") ;
                              scanf("%s",&choix2_3) ;

                              printf("entrer votre id_chemploi : ") ;
                              scanf("%d",&id_chemploi) ;
                              if (atoi(choix2_3) == 1)
                              {
                                  printf("entrer l'id de l'entrprise auquel vos anciens collègues doivent être employés : ") ;
                                  scanf("%d",&id_entreprise) ;
                                  rechercher_employe_chemp_par_entreprise(gchemp,id_chemploi,id_entreprise) ;
                              }
                              else if (atoi(choix2_3) == 2) rechercher_employe_chemp_par_competences(gchemp,gp,id_chemploi) ;
                              break ;
                }
                break ;
        case 3 :
                printf("\n\n*** Bienvenu sur LuminIn, le site des pros ***\n* Menu employé *\nVous voulez :\n") ;
                printf("1. Créer votre profil employé\n") ;
                printf("2. Modifier votre profil employé\n") ;
                printf("3. Transitionner votre profil employé à un profile chercheur d'emploi\n") ;
                printf("4. Supprimer votre profil employé \n") ;
                printf("5. Faire une recherche parmi les postes à pourvoir correspondant à votre profil employé\n") ;
                printf("6. Faire une recherche parmi les anciens collègues\n") ;

                printf("Votre choix ('q' pour quitter, 'p' pour menu précédent) : ") ;
                scanf("%s",&choix3_1) ;
                if (strcmp(choix3_1 , "q") == 0)   exit(EXIT_SUCCESS) ;
                else if (strcmp(choix3_1 , "p") == 0) main_interface() ;
                switch(atoi(choix3_1))
                {
                      case 1 :
                              creer_profil_employe(gemp,ge) ;
                              voir_employes(gemp) ;
                              break ;
                      case 2 :
                              printf("entrer votre id_employé : ") ;
                              scanf("%d",&id_employe) ;
                              modifier_profil_employe(gemp,ge,id_employe) ;
                              voir_employes(gemp) ;
                              break ;
                      case 3 :
                              printf("entrer votre id_employé : ") ;
                              scanf("%d",&id_employe) ;
                              transitionner_employe_chempl(gemp,gchemp,id_employe) ;
                              voir_employes(gemp) ;
                              voir_chemplois(gchemp) ;
                              break ;
                      case 4 :
                              printf("entrer votre id_employé : ") ;
                              scanf("%d",&id_employe) ;
                              supprimer_profil_employe(gemp,id_employe) ;
                              voir_employes(gemp) ;
                              break ;
                      case 5 :
                              printf("\nVous voulez :\n") ;
                              printf("1. Faire une recherche parmi les postes à pourvoir par compétences\n") ;
                              printf("2. Faire une recherche parmi les postes à pourvoir par compétences et code postal\n") ;
                              printf("Votre choix ('q' pour quitter) : ") ;
                              scanf("%s",&choix3_2) ;

                              printf("entrer votre id_employé : ") ;
                              scanf("%d",&id_employe) ;
                              if (atoi(choix3_2) == 1) rechercher_poste_emp_par_competences(gp,gemp,id_employe) ;
                              else if (atoi(choix3_2) == 2)
                              {
                                  printf("entrer le code_postale : ") ;
                                  scanf("%d",&code_postale) ;
                                  rechercher_poste_emp_par_competences_et_code_postale(gp,gemp,id_employe,code_postale) ;
                              }
                              break ;
                      case 6 :
                              printf("\nVous voulez :\n") ;
                              printf("1. Faire une recherche parmi les anciens collègues par entreprise \n") ;
                              printf("2. Faire une recherche parmi les anciens collègues par compétences \n") ;
                              printf("Votre choix ('q' pour quitter) : ") ;
                              scanf("%s",&choix3_3) ;

                              printf("entrer votre id_employé : ") ;
                              scanf("%d",&id_employe) ;
                              if (atoi(choix3_3) == 1)
                              {
                                  printf("entrer l'id de l'entrprise auquel vos anciens collègues doivent être employés : ") ;
                                  scanf("%d",&id_entreprise) ;
                                  rechercher_employe_emp_par_entreprise(gemp,id_employe,id_entreprise) ;
                              }
                              else if (atoi(choix3_3) == 2) rechercher_employe_emp_par_competences(gemp,gp,id_employe) ;
                              break ;
                }
                break ;
        default :
                printf("le choix fait n'existe pas ,rechoisissez\n") ;
                main_interface() ;
                break ;
    }
}

int main()
{
        main_interface() ;
}
