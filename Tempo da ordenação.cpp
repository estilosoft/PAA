/*
  Autor: Jonas Cavalcante Macêdo
  		 Milrak Pereira Pessoa
  		 Yan Rodrigo da Silva Soares
  		 Rafael Soares da Costa
  Alunos de Ciência da Computação - FUCAPI
  Data: 05/05/2016
  --- Gera numero aleatórios em um arquivo, separa o arquivo e ordena em outros arquivos ---
*/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
 
void merge(int p,int q,int n,int *v){
	int i,j,k, *c = NULL;
    c = (int*)malloc((n-p)*sizeof(int)); //  alocação de memória para o C
	i = p; // variavel recebe o valor 0(zero)
	j = q; // variavel recebe a metade do tamanho informado o main
	k = 0; // variavel para contar cada troca do valores

	while(i < q && j < n){  // executa até i chegar na metade do vetor e j chegar no final
		if(v[i] <= v[j]){ // se o valor da primeira metade for menor que o da segunda metade
			c[k] = v[i]; // o novo vetor recebe o menor valor da primeira metade
			k++; // acrescenta mais 1 para salvar o proximo valor do novo vetor
			i++; // acrescenta mais 1 para verificar a proxima prosição da primeira  parte do vetor
	    }else{ // caso o valor da primeira metade do vetor não seja menor
			c[k] = v[j]; // o novo vetor recebe o menor valor da segunda metade 
			k++;
			j++; // acrescenta mais 1 para verificar a proxima prosição da segunda  parte do vetor
		}
	}
	while(i < q){ // enquanto a primeira metade do vetor não foi verificada totalmente
		c[k] = v[i]; // vetor novo ordenado recebe os valor não lidos da primeira metade
		k++;
		i++;
	}
	while(j < n){ // enquanto a segunda metade do vetor não foi verificada totalmente 
		c[k] = v[j];  // vetor novo ordenado recebe os valor não lidos da segunda metade
		k++;
		j++;
	}
	for(i = p;i < n; i++) // salva os valores do vetor novo no vetor MÃE
		v[i] = c[i-p];
	free(c); // limpa memoria do vetor
}

void mergesort(int p,int n, int *v){
	int q;
	if(p < n-1){ // se a quantidade de numeros informados for maior que 0
		q = (p+n)/2; // pega a metade do valor informado
		mergesort(p,q,v); // manda a metade
		mergesort(q,n,v); // manda a outra metade
		merge(p,q,n,v); //chama a ordenação mandando a metadade e o final do vetor
	}
	else
		return; // se for zero, retorna 0
}

int main (){
	int *v,n;
	clock_t t1,t2; // declara variavel para armazenar os tempos
	float tempo[50], acm=0, desvio=0;
	
	printf("\nInforme a quantidade de numeros: ");
	scanf("%d",&n);
	v=(int*)malloc(n*sizeof(int)); // aloca memoria par o vetor
	srand(time(NULL));
	
	for (int j=0;j<50;j++){ // total de vezes que sera gerado e ordenado
		for (int i=0;i<n;i++) { // gera numeros até a quantidade informada
			v[i]=rand()% 9999; // adiciona o numero no vetor
		}
		t1=clock();//pega o tempo inicial antes da ordenação
		mergesort(0,n,v); // chamar a ordenação
		t2=clock(); // pega o tempo final depois da ordenação
		tempo[j]=(float)(t2-t1)/CLOCKS_PER_SEC;  // gera o tempo medio de cada interação
		acm+=tempo[j]; // pega o tempo medio total
	}
	for (int j=0;j<50;j++) { // gera a soma do desvio padrão
		desvio+=pow(tempo[j]-(acm/50),2); // formula para gerar o desvio padrão
	}
	printf("Tempo medio: %f",acm/50);
	printf("\nDesvio padrao: %f\n",sqrt(desvio/(50-1)));
}

