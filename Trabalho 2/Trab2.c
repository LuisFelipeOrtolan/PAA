/* 
Universidade Federal de São Carlos
Projeto e Análise de Algoritmo - 2020/1
Aluno: Luís Felipe Corrêa Ortolan
RA: 759375
*/

#include <stdio.h>
#include <stdlib.h>

/*	Função que troca doubles em um vetor.
	Input: Um vetor de doubles e dois inteiros A e B com as posições a serem trocadas.
	Output: O vetor com as posições A e B trocadas. */
void troca(double v[], int posA, int posB){
	double aux = v[posA];
	v[posA] = v[posB];
	v[posB] = aux;
}

/*	Função que embaralha um vetor aleatoriamente.
	Input: Um vetor de doubles e um inteiro com o seu tamanho.
	Output: O vetor original embaralhado. */
void embaralhaVetor(double v[], int tamanho){
	for(int i = 0; i < tamanho; i++){ //Para cada item do vetor,
		int random = rand() % tamanho; //Gere um número aleatório
		troca(v,i,random); //E troque com aquela posição.
	}
}

/* 	Função que particiona um vetor com base em um pivô (posição inicial), dividindo o vetor em menores e maiores que ele.
	Input: Um inteiro dizendo em que posição o vetor começa, um inteiro dizendo em que posição o vetor termina e o vetor de doubles.
	Output: Um vetor de doubles com o pivô na posição em que estará na ordenação com valores menores a ele a direita e maiores que ele a esquerda. */
int particiona(int comeco, int fim, double notas[]){

	double pivo = notas[comeco]; //Pivô é o valor da primeira posição.
	int i = comeco + 1, j = fim; //E iteradores para variar do vetor entre v[1...n-1].

	while(i <= j){ //Enquanto os iteradores não se encontrarem,
		while((notas[i] < pivo) && (i <= fim)) //Desde que os valores a esquerda sejam menores que o pivô e o vetor não tenha chegado ao fim,
			i++; //Avança o iterador.
		while((notas[j] > pivo) && (j >= comeco)) //Desde que os valores a direita sejam maiores que o pivô e o vetor não tenha chegado ao começo,
			j--; //Retrai o iterador.

		if(i < j){ //Se os iteradores se encontraram, troque os conteúdos de posições.
			troca(notas, i, j);
		}
	}

	troca(notas,j,comeco); //Coloca-se o pivô na posição devida.
	return j; //Retorna a posição que já está ordenada.
}

/*	Função que implementa parte do quicksort em um vetor de doubles para saber qual valor ocupa determinada posição, 
				nesse caso, a nota do último participante aceito(tamanho do vetor - entrevistados +1).
	Input: Um vetor de doubles a ser ordenado, um inteiro com a posição que o vetor começa, um inteiro com a posição
				onde o vetor termina, o tamanho total do vetor e o número de pessoas aceitas na entrevista.
	Output: O valor da posição desejada ou -1 se ainda não foi encontrada. */
double quicksort(double notas[], int comeco, int final, int tamanho, int entrevistados){	
	if (comeco < final){ //Se o vetor analisado tem tamanho maior que 1.
		int j = particiona(comeco, final, notas); //Particiona o etor uma primeira vez e retorna a posição que já foi ordenada.

		if((tamanho - entrevistados +1) == j) //Se a posição retornada for a desejada,
			return notas[j]; //Retorna o valor, problema resolvido.

		//Se não for a posição desejada,
		double esquerda = -1, direita = -1;
		if((tamanho - entrevistados +1) < j) //Se a posição do valor desejado for menor que a posição descoberta, faz-se um quicksort a esquerda.
			esquerda = quicksort(notas, comeco, j-1, tamanho, entrevistados);
		if((tamanho - entrevistados +1) > j) //Se a posição do valor desejado for maior que a posição descoberta, faz-se um quicksort a direita.
			direita = quicksort(notas, j+1, final, tamanho, entrevistados);
		if (esquerda >= direita) //Retorna a posição com maior valor (já que ou acha o valor correto ou -1.)
			return esquerda;
		return direita;
	}

	if(comeco == final) //Se o vetor tiver apenas uma posição, certamente essa será a desejada.
		return notas[comeco];

	return -1;
}

int main(){
	
	int vagas = 0;
	scanf("%d", &vagas); //Descobre o número de vagas a serem preenchidas.

	for(int i = 0; i < vagas; i++){ //Para cada vaga,
		int entrevistados = 0, candidatos = 0;
		scanf("%d", &entrevistados); //Preenche o número de pessoas a serem entrevistadas,
		scanf("%d", &candidatos); //Preenche o número de candidatos.

		double notas[candidatos];
		for(int i = 0; i < candidatos; i++) //Para cada candidato, preencha as notas.
			scanf("%lf", &notas[i]);

		embaralhaVetor(notas, candidatos); //O vetor é embaralhado para melhor funcionamento do quicksort.

		double menor_nota = quicksort(notas, 0, candidatos-1, candidatos-1,entrevistados); //O quicksort modificado é chamado.

		printf("%.2lf\n", menor_nota); //Escreve a menor nota de um candidato aprovado pra entrevista na tela.
	}

	return 0;
}