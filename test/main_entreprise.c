#include "groupe_entreprise.h"
#include "groupe_poste.h"
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////// ENTREPRISE  ////////////////////////////////////////////////

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
    //sigmptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);


////////////////////////////////////////////////////////// ENTREPRISE  ////////////////////////////////////////////////

    // Lecture de la DB vers une liste en mémoire.
    groupe_entreprises *g;
    {
        FILE *db = fopen("test/entreprise.csv", "r");
        g = ge_open(db);
        //fclose(db);
    }

    // Tests des fonctiosn g_open et g_size.
    {
         TEST(g!= NULL);
         TEST(ge_size(g) == 4);
    }

    /*
    //test cree_profile_entrep
    {
        cree_profile_entrep(g) ;
        TEST(ge_size(g) == 4);
        voir_entreprises(g) ;
    }
    */


    FILE *db = fopen("test/poste.csv", "r");
    groupe_postes *gr = gp_open(db);
    //fclose(db);
    //test supprime_profile_entrep
    {
        supprime_profile_entrep(g,gr,1) ;
        TEST(ge_size(g) == 3);
        voir_entreprises(g) ;
        voir_postes(gr) ;
        supprime_profile_entrep(g,gr,2) ;
        TEST(ge_size(g) == 2);
        voir_entreprises(g) ;
        voir_postes(gr) ;
    }
    
}
