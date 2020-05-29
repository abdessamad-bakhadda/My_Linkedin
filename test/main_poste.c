#include "groupe_poste.h"

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    ////////////////////////////////////////////////////////// POSTE ////////////////////////////////////////////////

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


    ////////////////////////////////////////////////////////// POSTE ////////////////////////////////////////////////

        groupe_postes *g;
        {
            FILE *db = fopen("test/poste.csv", "r");
            g = gp_open(db);
            //fclose(db);
        }

        // Tests des fonctiosn g_open et gp_size.
        {
             TEST(g!= NULL);
             TEST(gp_size(g) == 5);
             voir_postes(g) ;

        }
        
        //test cree_profile_poste
        {
            cree_profile_poste(g) ;
            TEST(gp_size(g) == 5);
            voir_postes(g) ;
        }



        //test supprime_profile_poste
        {
            supprimer_profile_poste(g,1) ;
            TEST(gp_size(g) == 3);
            voir_postes(g) ;
            supprimer_profile_poste(g,4) ;
            TEST(gp_size(g) == 2);
            voir_postes(g) ;
        }

        /*
        // Tests de fonction rechercher_employe_par_competences et par_competences_et_code_postale  .
        {
            rechercher_employe_par_competences(g,1) ;
            rechercher_employe_par_competences(g,2) ;
            rechercher_employe_par_competences(g,3) ;
            rechercher_employe_par_competences(g,4) ;
            rechercher_employe_par_competences(g,5) ;

            rechercher_employe_par_competences_et_code_postale(g,1,13100) ;
            rechercher_employe_par_competences_et_code_postale(g,2,13009) ;
            rechercher_employe_par_competences_et_code_postale(g,3,12200) ;
            rechercher_employe_par_competences_et_code_postale(g,4,12200) ;
        }
        */
        
}
