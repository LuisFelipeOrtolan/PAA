/* 
Universidade Federal de São Carlos
Projeto e Análise de Algoritmo - 2020/1
Aluno: Luís Felipe Corrêa Ortolan
RA: 759375
*/

#include <stdio.h>
#include <stdlib.h>

/*	Função que retorna o maior inteiro entre dois inteiros.
	Input: Um inteiro a e um inteiro b.
	Output: a, se o maior inteiro for a, ou b, caso contrário. */
int max(int a, int b){
	if(a>=b)
		return a;
	return b;
}

/*	Função que usa a tabela de memoização do problema da mochila pra descobrir a maior soma possível até certo valor.
	Input: Um inteiro soma com a soma máxima que se deseja alcanar, um int com o número de moedas disponíveis, um vetor de inteiro
				com as moedas disponíveis e uma matriz de inteiros para memoização de tamanho número de moedas +1 e soma máxima +1. */
int diferenca(int soma, int nro_itens, int moedas[], int memoiz[nro_itens+1][soma+1]){
	for(int i = 1; i <= nro_itens; i++) //Preenchendo a matriz de memoização (Valores na coluna 0 e linha 0 têm valor 0).
		for(int j = 1; j <= soma; j++){
			if(j < moedas[i-1]) //Se a soma atual for menor que o valor da moeda sendo analisada,
				memoiz[i][j] = memoiz[i-1][j]; //Copia a resposta da mesma soma para a moeda anterior.
			else
				memoiz[i][j] = max(memoiz[i-1][j], memoiz[i-1][j-moedas[i-1]] + moedas[i-1]); //Máximo entre a resposta com a mesma soma
							//para até a moeda anterior e a resposta anterior mais a nova moeda.
		}

	return 0;
}

int main(){		
	int nro_itens;
	scanf("%d", &nro_itens); //Registra o número de moedas disponiveis.

	int itens[nro_itens];
	int soma = 0;
	for(int i = 0; i < nro_itens; i++){ 
		scanf("%d", &itens[i]); //Registra o valor das moedas.
		soma = soma + itens[i]; //Soma o valor da moeda atual no contador da soma global.
	}

	// Como queremos a menor diferença possível, simplesmente dividimos por dois, já que seria a diferença ideal.
	int impar = 0;
	if(soma%2 == 0) //Se um valor é par,
		soma = (soma/2); //Registra que ele é par e divide a soma por dois.
	else{ //Se ele é ímpar
		soma = soma/2; // Divide por dois.
		impar = 1; //Registra que o valor é ímpar.
	}

	int memoiz[nro_itens+1][soma+1];
	for(int i = 0; i <= nro_itens; i++) //Inicializa a matriz de memoização com 0.
		for(int j = 0; j <= soma; j++)
			memoiz[i][j] = 0;

	diferenca(soma,nro_itens,itens,memoiz); //Chama a função que preenche a matriz de memoização.


	int resultado = ((2*soma+impar) -memoiz[nro_itens][soma]) - memoiz[nro_itens][soma]; //Faz a subtração do maior valor na divisão menos o menor.
	printf("%d\n", resultado);

	return 0;
}
