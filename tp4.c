#include <stdio.h>
#include <stdlib.h>
#include "lib_conjunto.h"
#define MAX 100


conjunto_t *ler_herois(conjunto_t *c){
    
}


conjunto_t *habilidades(int num) {
    conjunto_t *hab;

    hab = cria_cjt(MAX);

    insere_cjt(hab, num);

    return hab;
}


int main ()
{
    int num;
    conjunto_t *herois;

    herois = cria_cjt(MAX);

    /* ler os herois e suas habilidades */


    /* ler a missao */
    while(num != 0){
        scanf("%d", &num);
        habilidades(num);
    }

    /* ler as equipes de herois */

    /* a solucao eh encontrada se a missao esta contido na uniao das 
     * habilidades de uma equipe, mas tomando-se aquela de menor tamanho. */

    /* libera toda a memoria alocada dinamicamente */

    return 0;
}
