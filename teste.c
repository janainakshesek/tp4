#include <stdio.h>
#include <stdlib.h>
#define TAM 21

struct conjunto {
    int max;    /* tamanho maximo do vetor atualmente alocado     */
    int card;   /* cardinalidade, isto eh, tamanho usado ate max  */
    int ptr;    /* ponteiro para algum indice do vetor (iterador) */
    int *v;     /* vetor de inteiros com no maximo max elementos  */
};
typedef struct conjunto conjunto_t;
/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
 */
conjunto_t *cria_cjt (int max){
    conjunto_t *c;

    c = malloc(max);
    if (c  == NULL) 
            return NULL;

    c->max = max;
    return c;
}

/*
 * Remove todos os elementos do conjunto, libera espaco e devolve NULL.
 */
conjunto_t *destroi_cjt (conjunto_t *c){
    
    free(c);
    c = NULL;

    return c;
}

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
 */
int vazio_cjt (conjunto_t *c){

    if (c->v==NULL)
        return 1;
    return 0;
    
}
/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
 */
int cardinalidade_cjt (conjunto_t *c){
    int i;
    for(i=0; i<=c->max-1; i++){
        if(c->v[i] != 0)
            c->card = c->card+1;
    }
    return c->card;
}

int insere_cjt (conjunto_t *c, int elemento){

    int i, tam;
    tam = c->card;
    printf("cheguei");
    for(i=0; i<tam; i++ ){
        if(elemento == c->v[i])
            return 1; 
    }
    if (tam == c->max)
        return 0;
    
    c->v[c->card+1] = elemento;
    c->card = c->card+1;
    return 1;
}

int main () {

    conjunto_t *c;
  

    c = cria_cjt(TAM);
    
    printf("%d\n", c->max);
    printf("%d\n", vazio_cjt(c));
    printf("%d\n", cardinalidade_cjt(c));
  

    destroi_cjt(c);
   

    return 0;
}