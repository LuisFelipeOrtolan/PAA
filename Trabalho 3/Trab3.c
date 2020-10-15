/* 
Universidade Federal de São Carlos
Projeto e Análise de Algoritmo - 2020/1
Aluno: Luís Felipe Corrêa Ortolan
RA: 759375
*/

#include <stdio.h>
#include <stdlib.h>
#define INFINITE 2147483647;

// Lista encadeada para os vértices.
typedef struct list aresta;
struct list{
	int destino; //Destino da aresta.
	double peso; //Peso da aresta.
	struct list *prox; //Próximo item da lista.
};

/*	Função que insere de fato uma aresta em um vetor de listas encadeadas onde v[0] corresponde as arestas do vérice 0, etc.
	Input: Um vetor de lista encadeadas, um inteiro com o vértice de origem 
				e outro com o vértice destino e um double com o peso da aresta.
	Output: A aresta inserida no vetor de vértices.	*/
void insereFato(aresta *vet[], int origem, int destino, double peso){
	aresta *novo; //Cria uma nova aresta.
	novo = malloc(sizeof(aresta)); //Aloca a nova aresta.
	novo->destino = destino; //Coloca o destino da nova aresta.
	novo->peso = peso; //Coloca o pesto da nova aresta.
	if(vet[origem] != NULL){ //Se a lista encadeada de arestas não estiver vazia, insere normalmente.
		novo->prox = vet[origem]->prox;
		vet[origem]->prox = novo;
	}
	else{ //Caso contrário, insere como primeiro item na lista.
		vet[origem] = novo;	
	}
}

/*	Função usada para inserir uma aresta em um grafo não direcionado.
	Input: Um vetor de lista encadeadas, um inteiro com o vértice de origem e outro com o vértice destino 
				e um double com o peso da aresta.
	Output: Duas arestas inseridas no vetor de vértices.	*/
void insere(aresta *vet[], int origem, int destino, double peso){
	insereFato(vet, origem, destino, peso);
	insereFato(vet, destino, origem, peso);
}

/*	Função que preenche um vetor com os caminhos mínimos no grafo a partir do vértice zero.
	Input: Um inteiro com o número de vértices, um vetor de pointeiros de arestas 
				e um vetor de doubles para os valores dos caminhos mínimos.
	Outut: O vetor bestSoFar estará com os valores dos caminhos mínimos a partir de zero.	*/
void caminhoMinimo(int nro_vertices, aresta *vet[], double *bestSoFar){
	int fechado[nro_vertices]; //Vetor binário para indicar se os vértices já foram visitados pelo algoritmo.
	fechado[0] = 0, bestSoFar[0] = 0; //Inicia o vértice zero como aberto e com custo mínimo zero.
	for(int i = 1; i < nro_vertices; i++){ //Para os demais vértices,
		fechado[i] = 0; //Marca como aberto e
		bestSoFar[i] = INFINITE; //Coloca o caminho mínimo como infinito.
	}
	
	for(int k = 0; k < nro_vertices; k++){ //Visitando cada vértice.
		//Procurar qual o vértice com a menor distância mínima e que ainda não foi visitado.
		int menor = INFINITE;  //Inicia o valor menor com infinito para comparação,
		int j = -1; //A variável j vai guardar qual o vértice com o menor caminho mínimo não visitado.
		for(int i = 0; i < nro_vertices; i++){ //Percorre todos os vértices,
			if(bestSoFar[i] < menor && fechado[i] == 0){ //Se o caminho mínimo é menor que o menor caminho mínimo atual e não foi visitado,
				menor = bestSoFar[i]; //Esse é o novo menor caminho mínimo.
				j = i;
			}
		}

		//Relaxamento das arestas:
		for(aresta *p = vet[j]; p != NULL; p = p->prox) //Percorre as arestas do vértice encontrado.
			if(bestSoFar[p->destino] > bestSoFar[j] + p->peso){ //Se tamanho do caminho mínimo do vetor destino for maior que
																//o tamanho do caminho mínimo do vetor origem mais o peso da aresta,
				bestSoFar[p->destino] = bestSoFar[j] + p->peso; //O caminho mínimo para o vértice destino é trocado.
			}

		fechado[j] = 1; //Marca o vértice j como visitado.
	}
}

int main(){
	//Leituras de entrada.
	int nro_vertices, nro_corredor, nro_tubos, consultas;
	scanf("%d", &nro_vertices);
	scanf("%d", &nro_corredor);
	scanf("%d", &nro_tubos);
	scanf("%d", &consultas);

	// Inicia os vetores de arestas para o jogador(corredor) e impostor(tubos).
	aresta *corredor[nro_vertices];
	aresta *tubos[nro_vertices];
	for(int i = 0; i < nro_vertices; i++){
		tubos[i] = NULL;
		corredor[i] = NULL;
	}

	//Leitura das arestas que representam corredores.
	for(int i = 0; i < nro_corredor; i++){
		int origem, destino;
		double peso;
		scanf("%d", &origem);
		scanf("%d", &destino);
		scanf("%lf", &peso);
		insere(corredor, origem, destino, peso);
		insere(tubos, origem, destino, peso); //As arestas são inseridas para os dois vetores pois todos podem usar o corredor.
	}

	//Leitura das arestas que representam tubos.
	for(int i = 0; i < nro_tubos; i++){
		int origem, destino;
		scanf("%d", &origem);
		scanf("%d", &destino);
		insere(tubos, origem, destino, 1); //As arestas são inseridas só para o vetor dos impostores.
	}

	//Calcula os caminhos mínimos.
	double jogador[nro_vertices], impostor[nro_vertices];
	caminhoMinimo(nro_vertices, corredor, &jogador[0]);
	caminhoMinimo(nro_vertices, tubos, &impostor[0]);

	for(int i = 0; i < consultas; i++){
		int destino;
		scanf("%d", &destino);

		if(jogador[destino] <= impostor[destino]){ //Se o jogador levar menos tempo ou igual que o impostor,
			printf("victory\n"); //O jogador vence.
		}
		else //Se o jogador levar mais tempo que o impostor,
			printf("defeat\n"); //O jogador perde.
	}

	return 0;
}