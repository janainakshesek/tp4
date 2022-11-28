#include <stdio.h>
#include <stdlib.h>
#include "lib_conjunto.h"


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
    c->card = 0;

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

    return c->card;
}

/*
 * Insere o elemento no conjunto, garante que nao existam repeticoes.
 * Retorna 1 se a operacao foi bem sucedida. Se tentar inserir elemento existente,
 * nao faz nada e retorna 1 tambem. Retorna 0 em caso de falha por falta de espaco.
 */
int insere_cjt (conjunto_t *c, int elemento){

   c->card = cardinalidade_cjt(c);

    if (c->card == c->max)
        return 0; 
    else if(pertence_cjt(c, elemento))
        return 1;
     
    c->v[c->card] = elemento;
    c->card = c->card+1;
    return 1;
}
/*
 * Remove o elemento 'elemento' do conjunto caso ele exista.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
 */
int retira_cjt (conjunto_t *c, int elemento){

    int sentinela, i;

    sentinela = c->v[c->card];
    i = 0;

    if(!pertence_cjt(c,elemento))
        return 0;
    else {
        while (c->v[i] != sentinela)
        {
            if (c->v[i] == elemento)
            {
                c->v[i] = c->v[i + 1];
                if (c->v[i] != sentinela)
                c->v[i + 1] = elemento;
            }
            i++;
        }
    return 1;
    }
}
/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
 */
int pertence_cjt (conjunto_t *c, int elemento){
    int i;

    for(i=0; i<c->card; i++){
        if(elemento == c->v[i])
            elemento = 1;
        else if(i > c->card)
            elemento = 0;
    }

    if(elemento == 1)
        return 1;
    else    
        return 0;  
}
/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
 */
int contido_cjt (conjunto_t *c1, conjunto_t *c2){
    
    int i, j, elemento, cont;

    if(c1->card <= c2->card)
        return 0;

    for(j=0; j<c1->card; j++){
        elemento = c1->v[j];

        for(i=0; i<c2->card; i++)
            if(c2->v[i]==elemento)
                cont = cont + 1;
    }

    if(cont == c1->card)
        return 1;
    return 0;

}

/*                                  
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
 */
int sao_iguais_cjt (conjunto_t *c1, conjunto_t *c2){
   
    if ((contido_cjt(c1,c2)) && (contido_cjt(c2,c1)))
        return 1;
    return 0;
}

/*
 * Cria e retorna o conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *diferenca_cjt (conjunto_t *c1, conjunto_t *c2){
    int i, j;
    conjunto_t *diferenca;

    diferenca = malloc(sizeof(conjunto_t*));

    for(i=0; i<=c1->card; i++){
        if(!pertence_cjt(c2, c1->v[i]))
            for(j=0; j<diferenca->max; j++)
                diferenca->v[j] = c1->v[i];
    }

    return diferenca;
}

/*
 * Cria e retorna o conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *interseccao_cjt (conjunto_t *c1, conjunto_t *c2){
    int i, j;
    conjunto_t *interseccao;

    interseccao = malloc(sizeof(conjunto_t*));

    for(i=0; i<c1->card; i++){
        for(j=0; i<c2->card; j++){
            if(c1->v[i]==c2->v[j])
                interseccao->v[i] = c1->v[i];
        }
    }
    return interseccao;
}

/*
 * Cria e retorna o conjunto uniao entre os conjunto c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *uniao_cjt (conjunto_t *c1, conjunto_t *c2){

    int i, j, k;
    conjunto_t *uniao;

    uniao = malloc(sizeof(conjunto_t*));

    uniao->max = c1->card + c2->card;
    uniao->card = cardinalidade_cjt(uniao);

    for(i=0; i<c1->card; i++){  /* Este for copia os elementos de c1 para uniao em sequencia*/
            uniao->v[i]=c1->v[i];
    }

    for(j=uniao->card+1; j<uniao->max; j++){ /* Este for completa o vetor uniao a partir do ultimo espaco ocupado pelo for anterior*/
        for(k=0; k<c2->card; k++){  /*Este for percorre tomalloc(sizeof(conjunto_t*));das as posicoes ocupadas de uniao*/
            uniao->v[j] = c2->v[k];
        }    
    }
    return uniao;
}

/*
 * Cria e retorna uma copia do conjunto c e NULL em caso de falha.
 */
conjunto_t *copia_cjt (conjunto_t *c){
    int i;
    conjunto_t *copia;

    copia = cria_cjt(c->max);

    for(i=0; i<c->card; i++){
        copia->v[i] = c->v[i];
    }
    return copia;
}

/*
 * Cria e retorna um subconjunto com elementos aleatorios do conjunto c.
 * Se o conjunto for vazio, retorna um subconjunto vazio.
 * Se n >= cardinalidade (c) entao retorna o proprio conjunto c.
 * Supoe que a funcao srand () tenha sido chamada antes.
 */
conjunto_t *cria_subcjt_cjt (conjunto_t *c, int n){

    conjunto_t *sub;
    int i;

    sub = malloc(n*sizeof(int));

    for(i=0; i<n; i++){
        sub->v[i] = c->v[rand()%c->card];
    }

    return sub;    
}

/*
 * Imprime os elementos do conjunto sempre em ordem crescente,
 * mesmo que a estrutura interna nao garanta isso.
 * Na impressao os elementos sao separados por um unico espaco
 * em branco entre os elementos, sendo que apos o ultimo nao
 * deve haver espacos em branco. Ao final imprime um \n.
 */
void imprime_cjt (conjunto_t *c){

    int i, j, menor;
    menor = c->v[0];

    for(i=0; i<c->card; i++){
        for(j=i+1; j<c->card; j++){
            if(c->v[j] < menor)
                menor = c->v[j];
        }
        printf("%d", menor);
        menor = c->v[i+1];
    }
}

/*
 * As funcoes abaixo implementam um iterador que vao permitir
 * percorrer os elementos do conjunto.
 * O ponteiro ptr da struct (iterador) pode ser inicializado para apontar 
 * para o primeiro elemento e incrementado ate' o ultimo elemento 
 * do conjunto.
 */

/*
 * Inicializa ptr usado na funcao incrementa_iterador 
 */
void inicia_iterador_cjt (conjunto_t *c){

    c->ptr = 0;
}

/*
 * Devolve no parametro ret_iterador o elemento apontado e incrementa o iterador.
 * A funcao retorna 0 caso o iterador ultrapasse o ultimo elemento, ou retorna
 * 1 caso o iterador aponte para um elemento valido (dentro do conjunto).
 */
int incrementa_iterador_cjt (conjunto_t *c, int *ret_iterador){
    if (c->ptr <= c->card){
        ret_iterador = c->v[c->ptr];
        c->ptr = c->ptr + 1;
        return 1;
    } else  
        return 0;
}

/*
 * Escolhe um elemento qualquer do conjunto para ser removido, o remove e
 * o retorna.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso       
 */
int retira_um_elemento_cjt (conjunto_t *c){

    c->v[c->card-1] = 0;
    c->card = c->card - 1;

    return c->v[c->card-1];
}
