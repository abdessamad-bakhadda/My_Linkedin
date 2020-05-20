#include "groupe_employe.h"


#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    ////////////////////////////////////////////////////////// EMPLOYE  ////////////////////////////////////////////////

// Nombre total de tests exécutés.
int tests_executes = 0;
// Pour chaque test qui réussi, cette variable sera incrémentée de 1.
// Le but est de la garder égale à test_executes.
int tests_reussis = 0;

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)

// Incrémente le nombre de test exécutés de 1.
// Si le test réussi, incrémente le nombre de tests réussis de 1.
#define TEST(x) tests_executes += 1;    \
                if(x)                   \
                {                       \
                    tests_reussis += 1; \
                    printf("[SUCCES] ");\
                }                       \
                else                    \
                {                       \
                    printf("[ECHEC ] ");\
                }                       \
                printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(x) "\n");

// Fonction à executer lors d'une segmentation fault.
// On imprime les résultats obtenus jusqu'à lors et on arrête immédiatement le programme.
void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    printf("[SEGFAULT]\n");
    printf("%d/%d\n", tests_reussis, tests_executes);
    exit(tests_reussis - tests_executes);
}

int main()
{
    // Mise en place de la fonction à exécuter lors d'une segmentation fault.
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);

    ////////////////////////////////////////////////////////// EMPLOYE  ////////////////////////////////////////////////

      FILE *db1 = fopen("test/entreprise.csv", "r");
      groupe_entreprises *gr  = ge_open(db1);
      fclose(db1);

      FILE *db = fopen("test/poste.csv", "r");
      groupe_postes *gr1 = gp_open(db);
      fclose(db);

      voir_postes(gr1) ;

     groupe_employes *g;
     {
         FILE *db2 = fopen("test/employe.csv", "r");
         g = gemp_open(db2);
         fclose(db2);
     }

     // Tests des fonctiosn g_open et g_size.
     {
          TEST(g != NULL);
          TEST(gemp_size(g) == 4);
     }
     
     

     // Tests de fonction creer_profil_employe
     {
        creer_profil_employe(g,gr) ;
        TEST(gemp_size(g) == 5);
        voir_employes(g) ;
     }


     // Tests de fonction modifier_profil-employe
     {
        modifier_profil_employe(g,gr,2) ;
        voir_employes(g) ;
     }



     // Tests de fonction supprimer_profil_employe
     {
        supprimer_profil_employe(g,1) ;
        TEST(gemp_size(g) == 3);
        supprimer_profil_employe(g,4) ;
        TEST(gemp_size(g) == 2);
        voir_employes(g) ;
     }

     //a tester
     // Tests de fonction rechercher_employe_par_competences et par_competences_et_code_postale  .
     {

         rechercher_poste_emp_par_competences(gr1,g,1) ;
         rechercher_poste_emp_par_competences(gr1,g,2) ;
         rechercher_poste_emp_par_competences(gr1,g,3) ;
         rechercher_poste_emp_par_competences(gr1,g,4) ;


         rechercher_poste_emp_par_competences_et_code_postale(gr1,g,1,75009) ;
         rechercher_poste_emp_par_competences_et_code_postale(gr1,g,2,75009) ;
         rechercher_poste_emp_par_competences_et_code_postale(gr1,g,3,77700) ;
         rechercher_poste_emp_par_competences_et_code_postale(gr1,g,4,12200) ;
     }
     

    
     // Tests de fonction rechercher_employe_chemp_par_entreprise et par_competences  .
     {

         rechercher_employe_emp_par_entreprise(g,1,1) ;
         rechercher_employe_emp_par_entreprise(g,2,1) ;
         rechercher_employe_emp_par_entreprise(g,3,1) ;
         rechercher_employe_emp_par_entreprise(g,4,2) ;


         rechercher_employe_emp_par_competences(g,gr1,1) ;
         rechercher_employe_emp_par_competences(g,gr1,2) ;
         rechercher_employe_emp_par_competences(g,gr1,3) ;
         rechercher_employe_emp_par_competences(g,gr1,4) ;

     }

}
