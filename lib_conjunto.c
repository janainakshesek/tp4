#include <stdio.h>
#include <stdlib.h>
#include "lib_conjunto.h"


/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
 */
conjunto_t *cria_cjt (int max){

    conjunto_t *c;

    /* aloca espaco para o conjunto */
    c = malloc(sizeof(conjunto_t));
    if (c  == NULL) 
      return NULL;

    /* alocar o vetor de inteiros (elementos do conjuntos */
    c->v = malloc (sizeof(int)*max);
    if (c->v == NULL)
    {	    
      free(c);	    
      return NULL;
    }

    c->max = max;
    c->card = 0;
    c->ptr = 0;

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
    return !c->card;
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

    if(c->card == c->max)
        return 0;
    if (pertence_cjt(c, elemento))
        return 1;

    c->v[c->card] = elemento;
    c->card += 1;
    return 1;
}

/*
 * Remove o elemento 'elemento' do conjunto caso ele exista.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
 */
int retira_cjt (conjunto_t *c, int elemento){

    int i, aux;
	
	aux = -1;
	
	for(i=0;i<(c->card);i++)
		if (c->v[i] == elemento)
			aux = i;
			
	if (aux == -1 )
		return 0;
		
	c->card --;
		
	for(i=aux;i<(c->card);i++)
		c->v[i] = c->v[i+1];
		
	return 1;
}
/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
 */
int pertence_cjt (conjunto_t *c, int elemento){

    int i;
	
	for (i=0;i<c->max;i++)
	
		if (c->v[i] == elemento)
			return 1;
			
	return 0;
}
/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
 */
int contido_cjt (conjunto_t *c1, conjunto_t *c2){
    
    int i;

    if(c1->card > c2->card)
        return 0;

   while(i<=c1->card){
        if(!(pertence_cjt(c2, c1->v[i])))
            return 0;
        i++;
   }
   return 1;
    
}

/*                                  
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
 */
int sao_iguais_cjt (conjunto_t *c1, conjunto_t *c2){


    if(c1->card != c2->card)
        return 0;
  
    if((contido_cjt(c1,c2)) && (contido_cjt(c2,c1)))
        return 1;
    return 0;
}
/*
 * Cria e retorna o conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *diferenca_cjt (conjunto_t *c1, conjunto_t *c2){
    int i;
    conjunto_t *diferenca;

    diferenca = cria_cjt(c1->card + c2->card);

    for(i=0; i<c1->card; i++){
        if(!(pertence_cjt(c2, c1->v[i])))
            insere_cjt(diferenca, c1->v[i]);
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
   
    interseccao = cria_cjt(c1->card+c2->card);

    for(i=0; i<c1->card; i++){
        for(j=0; j<c2->card; j++){
            if(pertence_cjt(c2, c1->v[i]))
                insere_cjt(interseccao, c1->v[i]);
        }
    }
    return interseccao;
}

/*
 * Cria e retorna o conjunto uniao entre os conjunto c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t *uniao_cjt (conjunto_t *c1, conjunto_t *c2){

    int i, j;
    conjunto_t *uniao;

    uniao = cria_cjt(c1->card+c2->card);

    for (i = 0; i < c1->card; i++) {
        insere_cjt(uniao, c1->v[i]);
    }
    for (j=0; j < c2->card; j++) {
        insere_cjt(uniao, c2->v[j]);
    }
    return uniao;
}

/*
 * Cria e retorna uma copia do conjunto c e NULL em caso de falha.
 */
conjunto_t *copia_cjt (conjunto_t *c){
    int i;
    conjunto_t *copia;

    copia = cria_cjt(c->card);

    for(i=0; i<c->card; i++){
        insere_cjt(copia, c->v[i]);
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
    int i, cont, tam;
    cont = 0;

    sub = copia_cjt(c);

    if(n >= c->card)
        return sub;

    tam = c->card - n;
    while(cont < tam){
        i = rand()%(sub->card);
        retira_cjt(sub, sub->v[i]);
        cont++;
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

    if(vazio_cjt(c))
        printf("conjunto vazio");

    for(i=0; i<c->card; i++){
        for(j=i+1; j<c->card; j++){
            if(c->v[j] < menor)
                menor = c->v[j];
        }
        printf("%d ", menor);
        menor = c->v[i+1];
    }
    printf("\n");
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
    if (c->ptr > c->card)
	   return 0;

    *ret_iterador = c->v[c->ptr];
    c->ptr = c->ptr + 1;
    return 1;
}

/*
 * Escolhe um elemento qualquer do conjunto para ser removido, o remove e
 * o retorna.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso       
 */
int retira_um_elemento_cjt (conjunto_t *c){

    c->v[c->card] = 0;
    c->card -= 1;

    return c->v[c->card];
}
