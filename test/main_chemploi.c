#include "groupe_chemploi.h"

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    ////////////////////////////////////////////////////////// CHEMPLOI  ////////////////////////////////////////////////

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

    ////////////////////////////////////////////////////////// CHEMPLOI  ////////////////////////////////////////////////






       groupe_chemplois *g;
       {
           FILE *db2 = fopen("test/chemploi.csv", "r");
           g = gch_open(db2);
           fclose(db2);
       }

     // Tests des fonctiosn g_open et g_size.
     {
          TEST(g != NULL);
          TEST(gchemp_size(g) == 6);
          voir_chemplois(g) ;
     }

     /*
     // Tests de fonction rechercher_chemploi_par_competences et par_competences_et_code_postale  .
     {
         rechercher_chemploi_par_competences(g,1) ;
         rechercher_chemploi_par_competences(g,2) ;
         rechercher_chemploi_par_competences(g,3) ;
         rechercher_chemploi_par_competences_et_code_postale(g,1,13100) ;
         rechercher_chemploi_par_competences_et_code_postale(g,2,13009) ;
         rechercher_chemploi_par_competences_et_code_postale(g,3,12200) ;
     }

     // Tests de fonction creer_profil_chemploi
     {
        creer_profil_chemploi(g) ;
        TEST(gchemp_size(g) == 7);
        voir_chemplois(g) ;
     }

     // Tests de fonction modifier_profil-chemploi
     {
        modifier_profil_chemploi(g,2) ;
        voir_chemplois(g) ;
     }

     // Tests de fonction transitionner_chempl_employe
     {
        FILE *db = fopen("test/employe.csv", "r");
        groupe_employes* gr = gemp_open(db);
        fclose(db);

        voir_employes(gr) ;
        transitionner_chempl_employe(g,gr,2,2) ;
        voir_employes(gr) ;
        voir_chemplois(g) ;
     }

     // Tests de fonction supprimer_profil_chemploi
     {
        supprimer_profil_chemploi(g,5) ;
        voir_chemplois(g) ;
     }


     // Tests de fonction transitionner_employe_chempl
     {
        FILE *db = fopen("test/employe.csv", "r");
        groupe_employes* gr = gemp_open(db);
        fclose(db);
        voir_employes(gr) ;
        transitionner_employe_chempl(gr,g,2) ;
        EST(emp_size(gr) == 3);
        voir_employes(gr) ;
        TEST(gchemp_size(g) == 7);
        voir_chemplois(g) ;
     }

     // Tests de fonction rechercher_employe_par_competences et par_competences_et_code_postale  .
     {
         FILE *db = fopen("test/poste.csv", "r");
         groupe_postes *gr = gp_open(db);
         fclose(db);

         rechercher_poste_chemp_par_competences(gr,g,1) ;
         rechercher_poste_chemp_par_competences(gr,g,2) ;
         rechercher_poste_chemp_par_competences(gr,g,3) ;
         rechercher_poste_chemp_par_competences(gr,g,4) ;
         rechercher_poste_chemp_par_competences(gr,g,5) ;

         rechercher_poste_chemp_par_competences_et_code_postale(gr,g,1,75009) ;
         rechercher_poste_chemp_par_competences_et_code_postale(gr,g,2,13009) ;
         rechercher_poste_chemp_par_competences_et_code_postale(gr,g,3,12200) ;
         rechercher_poste_chemp_par_competences_et_code_postale(gr,g,4,12200) ;
     }
     */
     // Tests de fonction rechercher_employe_chemp_par_entreprise et par_competences  .
     {
         FILE *db = fopen("test/poste.csv", "r");
         groupe_postes *gr = gp_open(db);
         fclose(db);

         voir_postes(gr) ;

         rechercher_employe_chemp_par_entreprise(g,1,1) ;
         rechercher_employe_chemp_par_entreprise(g,2,2) ;
         rechercher_employe_chemp_par_entreprise(g,3,1) ;
         rechercher_employe_chemp_par_entreprise(g,4,2) ;
         rechercher_employe_chemp_par_entreprise(g,5,1) ;
         rechercher_employe_chemp_par_entreprise(g,6,2) ;

         rechercher_employe_chemp_par_competences(g,gr,1) ;
         rechercher_employe_chemp_par_competences(g,gr,2) ;
         rechercher_employe_chemp_par_competences(g,gr,3) ;
         rechercher_employe_chemp_par_competences(g,gr,4) ;
         rechercher_employe_chemp_par_competences(g,gr,5) ;
         rechercher_employe_chemp_par_competences(g,gr,6) ;
     }


}
