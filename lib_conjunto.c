#include <stdio.h>
#include <stdlib.h>
#include "lib_conjunto.h"
#define MAX 100


conjunto_t **ler_herois(){
    
    int h, i = 0, j= 0;
    conjunto_t **herois;
    herois = malloc(MAX*sizeof(conjunto_t));
    
    while (i < 10) {
        scanf("%d", &h);
        if (h != 0) {
            herois[i] = cria_cjt(MAX);
            while(h != 0 && j != MAX) {
                insere_cjt(herois[i], h);
                scanf("%d", &h);
                j++;
            }
            imprime_cjt(herois[i]);
        }
        i++;
    }
    
    return herois;
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
    conjunto_t **herois;
   

    /* ler os herois e suas habilidades */
    
    herois = ler_herois();
    

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
