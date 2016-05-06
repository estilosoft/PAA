/*
  Autor: Jonas Cavalcante Macêdo
  		 Milrak Pereira Pessoa
  		 Yan Rodrigo da Silva Soares
  		 Rafael Soares da Costa
  Alunos de Ciência da Computação - FUCAPI
  Data: 06/05/2016
  --- Gera numero aleatórios em um arquivo, separa o arquivo e ordena em outros arquivos ---
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#define TAMANHO 1288490190 // define o tamanho de 6 GIGAS

typedef struct lista { // cria lista para ser inserido os numero que serão ordenados
   int num;  // numero da lista
   struct lista* prox; // apomtador para o proximo
}Lista;


Lista* cria_vazia(){ // retorna uma lista nula
   return NULL;
}

Lista* insere(Lista* l, int n){ //insere cada nó da lista
   Lista* no= (Lista*)malloc(sizeof(Lista)); // aloca no novo numero na memoria da lista
   Lista* aux;  // cria um PONTEIRO  do tipo lista, uma copia da lista de entrada
   no->num=n;  // novo local aponta para o numero da lista, que recebe o numero a ser inserido
   no->prox=NULL; // por estar adicionando um novo o proximo elemento da lista é nulo
   if(l==NULL) // caso a lista seja  nula, retorna somente numero adicionado a lista, ou seja, lista somenete com 1 numero
   		return no; 
   aux=l; // ponteiro do tipo lista recebe a lista recebida por paramentro
   while(aux->prox!=NULL) // percorre a lista até que o ultimo elemento seja nulo
   		aux=aux->prox;    // o endereço da lista auxiliar recebe o local do proximo elemento
   aux->prox=no; // recebe o ultimo valor a ser adicionado
   return l; // RETORNA A LISTA COM O NOVO NUMERO ADICIONADO
}
Lista* concatena_ordenado(Lista* a, Lista* b){ //recebe duas listas em ordem crescente e as concatena, resultando em uma unica lista ordenada
   Lista* l= cria_vazia();//aponta para a lista resultante
   Lista* aux;//aponta para o ultimo nó da lista resultante
   while(a!=NULL && b!=NULL){
      if(a->num < b->num){
         if(l==NULL)aux=a;
         else{
            aux->prox=a;
            aux=aux->prox;
         } 
         a=a->prox;
      }
      else{ // se a lista caso o numero da vez de A seja MAIOR que numero da vez de B
         if(l==NULL) // caso a lista seja nula
		 	aux=b; // o apontador recebe a lista B
         else{ // caso não seja nula
            aux->prox=b; // o apontador para o ultimo nó da lista auxiliar recebe a lista B
            aux=aux->prox; // e aponta para o proximo( nesse caso o Final)
         }
         b=b->prox; // a lista B recebe o ponteiro para o proximo elemento (nesse caso o Final da lista B)
      }
      aux->prox=NULL; // após concatenar as duas lista, a lista auxiliar adiciona NULO ao ultimo valor, para definir o final
      if(l==NULL) // se a lista inicial for NULA
	  	l=aux; // ela recebe a auxiliar ja concatenada
   }
	if(a==NULL)  // se a lista a for NULA
		aux->prox=b; // o final da lista auxiliar recebe a lista B
   	else
	   aux->prox=a; // o final da lista auxiliar recebe a lista A
   	return l; // retorna a lista ja concatenada
}

Lista* mergesort(Lista* l){//recebe uma lista desordenada e a ordena pelo mergesort
    Lista* a; // cria uma SubLista
    Lista* b; // cria uma SubLista
    
    if (l == NULL || l->prox == NULL) //caso a lista esteja vazia ou com apenas um elemento, retorna ela mesma
		return l;
    
    //dividir a lista em duas
    a = l; // a lista A recebe toda a lista L
    b = l->prox; // a lista B recebe o ultimo valor de L( ou seja, NULO)
    while (b != NULL && b->prox != NULL) { // enqutanto não chegar ao final da lista B
        l = l->prox; // o ponteiro anda até o final de L
        b = b->prox->prox; // o ponteiro anda até o final da lista B
    }
    b = l->prox; // a lista B recebe o ultimo valor de L(ou seja, NULO)
    l->prox = NULL; // o ultimo valor da lista L recebe NULO
    
    //chamada das recursões para subdividir todas as sublistas
    a=mergesort(a); // retorna a ordenação da lista A
    b=mergesort(b); // retorna a ordenação da lista B
    
    //retorna a concatenação das duas lista ordenada em ordem crescenete
    return concatena_ordenado(a,b);
}
    
int main(void){//função principal, recebe os elementos a serem ordenados, gera a lista e os ordena, através das chamadas às outras funções 
	int num;
	Lista* l; // ponteiro para a lista desordenada
	Lista* lista; // lista ordenada
	FILE* arquivo; // ponteiro para o arquivo aleatorio
   	FILE* aux; // ponteiro para o arquivo ordenado
    FILE* arqjunta; // para para o arquivo que junta e salva os ordenados
	long int b, tam=1; // variavel b é contar a quantidade de numeros e tam é a quantidade de numeros a ser salvo ordenado
   
    char nome[100]; // nome do arquivo a ser separado
    int cont; // contadir para separar os arquivos
	int contsepara=1450, contpart=1, contant=1000;
	
	srand( (unsigned)time(NULL) ); // pega a hora como numero inicial para que não gera numeros iguais até que todos sejam gerados
	  
	arquivo= fopen("mergesort.txt", "a+");
    //RECEBE OS ELEMENTOS DA LISTA E SALVA EM UM ARQUIVO
	l=cria_vazia();
	for(b=1;b<=TAMANHO;b++){    // vai de 1 byte até .....
	    // recebe valor aleatario de 1000 a 9999, ou seja de 4 bytes
      	fprintf(arquivo, "%d,", ( contant + rand() % contsepara )); // escreve no arquivo
		if (b==TAMANHO/20*contpart){
			contant = contsepara;
			contsepara+=450;
			contpart++;
		}
	}
	fclose(arquivo); // fecha o txt com numeros aleatórios
    printf("Arquivo Desordenado Gerado Com Sucesso\n");
      
	arquivo = fopen("mergesort.txt", "rt");
	arqjunta = fopen("juntaordenado.txt", "a+");
	for(cont=1;cont<=20;cont++){ // for que separa os arquivos ordenados
		printf("Lendo a %da parte do arquivo\n", cont);
	  	l=cria_vazia();
      	while (!feof(arquivo)) { // ler o arquivo até que seja nulo
      		if(tam<=64424510){ // se o elemento for menor que o tamanho de cada partição entra o se
      			tam++; // acrescenta mais 1 a cada leitura do arquivo
        		fscanf(arquivo, "%d,", &num); // ler o numero do arquivo e insere na variavel num da lista
          		l=insere(l, num); // ponteiro da lista recebe a inserção do numero
        	}
			else // caso o numero de elementos seja maior que o tamanhod definido
        		break; // o while para de rodar para que se inicie a ordenação
      	}
      	tam=1;
	  	printf("\nINCIO DA ORDENACAO %d\n",cont);
      	lista = mergesort(l); // envia o ponteiro da lista desordenada para o mergesorte que retorna ordenado
      
      	// SALVANDO A LISTA ORDENADA NO ARQUIVO
      	sprintf(nome, "%i.txt", cont); aux= fopen(nome, "w+"); // cria a partição para onde sera salvo a ordenação
	  	while(lista!=NULL){ // insere a lista no arquivo txt até que seja nula
        	fprintf(aux,"%d,", lista->num); // escreve o numero da lisra no arquivo
        	fprintf(arqjunta, "%d,", lista->num);
			lista=lista->prox; // o ponteiro da lista aponta para o proximo elemento
      	}
	  	fclose(aux); // fecha a partição a cada ordenação salva
      	free(lista); // limpa a lista ordenada
      	free(l); // limpa a lista desordenada
	}
    
	printf("Arquivos Gerados Com Sucesso\n");
   	fclose(arquivo); // fecha o desordenado
   	fclose(arqjunta); // fecha o ordenad
	fflush(stdin);
   	getchar(); return 0;
}
