#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
matriz de adjacencia
X cria grafo lendo de arquivo
X adiciona/remove um vértice
X adiciona/remove uma nova aresta
X retorna uma lista de nós vizinhos de um dado vértice
*/

int **AdicionaVertice(int **, int *);
int **RemoveVertice(int **, int *, int);
void RemoveAresta(int **, int, int);
void AdicionaAresta(int **, int, int);
void Vizinhos(int **, int, int);
void ImprimeMatriz(int **, int);
void Busca(int **, int, int, int **, int **, int *);
void BuscaGrafo(int **, int, int **, int **, int *);
void BuscaCompleta(int **, int, int **, int **, int *);
int EhConexo(int **, int, int **, int **, int *);
int TemCiclo(int **, int, int **, int **, int *);
int EhFloresta(int **, int, int **, int **, int *);
int EhArvore(int **, int, int **, int **, int *);
void ObterFlorestaGeradora(int **, int, int **, int **, int *);

int main() {
	// inicializa bando de gente
	FILE *Arquivo = NULL;
	int **Matriz = NULL;
	int *Visitado;
	int **Descoberta;
	int **Explorada;
	int vertices = 0;
	int arestas = 0;
	int i, j, v1, v2;
	////////////////////////////////////////////////////
 /* Visitado = (int *)malloc(vertices * sizeof(int));
  Explorada = (int **)malloc(vertices * sizeof(int *));
  Descoberta = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Descoberta[i] = (int *)malloc(vertices * sizeof(int));
	}
  for (i = 0; i < vertices; i++) {
	 Explorada[i] = (int *)malloc(vertices * sizeof(int));
	}*/

	// abre arquivo, le N e M
	Arquivo = fopen("grafo3.txt", "r");
	fscanf(Arquivo, "%d\t%d", &vertices, &arestas);
	///////////////////////////////////////////////

	// dinamicamente aloca matriz N x N, preenche com zeros
	Matriz = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Matriz[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Matriz[i][j] = 0;
		}
	}
	////////////////////////////////////////////////////////////

	// le arestas e marca elas como existentes (iguais a um) na matriz
	for (i = 0; i < arestas; i++) {
		fscanf(Arquivo, "%d\t%d", &v1, &v2);
		Matriz[v1][v2] = 1;
		Matriz[v2][v1] = 1;
	}
	///////////////////////////////////////////////////////////
  //Testando cada algoritmo e exibindo as respostas como 1(true) e 0(false)
  int arvore, conexo, ciclo, floresta;

  clock_t tempo1; //teste de tempo iniciado
	tempo1 = clock();
	//BuscaGrafo(Matriz,vertices, Descoberta,Explorada,Visitado);
  //BuscaCompleta(Matriz,vertices, Descoberta,Explorada,Visitado);
  //conexo = EhConexo(Matriz,vertices,Descoberta,Explorada,Visitado);
  //arvore = EhArvore(Matriz,vertices,Descoberta,Explorada,Visitado);
  //ciclo = TemCiclo(Matriz,vertices,Descoberta,Explorada,Visitado);
  //floresta = EhFloresta(Matriz, vertices, Descoberta, Explorada, Visitado);
  
  printf("Tempo de BuscaGrafo:%f\n",(clock() - tempo1) /
	(double)CLOCKS_PER_SEC);

 //printf("é conexo? %d\né arvore? %d\ntem ciclo? %d\né floresta? %d\n", conexo, arvore, ciclo, floresta);

  //Obtendo a floresta geradora, funcao void que printa as arestas que existem nela
  //ObterFlorestaGeradora(Matriz, vertices, Descoberta, Explorada, Visitado);
	// libera e fecha geral
	for (i = 0; i < vertices; i++) {
		free(Matriz[i]);
	}

	free(Matriz);

	fclose(Arquivo);
	////////////////////////////////////////////////////////

	// maravilha
	return 0;
}

void BuscaGrafo(
	int **Matriz,
	int vertices,
	int **Descoberta,
	int **Explorada,
	int *Visitado) {
	//clock_t tempo1; //teste de tempo iniciado
	//tempo1 = clock();

	// Cria Lista Visitados.

	Visitado = (int *)malloc(vertices * sizeof(int));
	int i, j;
	for (i = 0; i < vertices; i++) {
		Visitado[i] = 0;
	}

	// Cria Lista Aresta Explorada

	Explorada = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Explorada[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Explorada[i][j] = 0;
		}
	}

	// Cria Lista Aresta Descoberta

	Descoberta = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Descoberta[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Descoberta[i][j] = 0;
		}
	}

	Busca(Matriz, vertices, 0, Descoberta, Explorada, Visitado);

  

//printf("Tempo de BuscaGrafo:%f\n",(clock() - tempo1) /
	 //(double)CLOCKS_PER_SEC);
}

void Busca(
	int **Matriz,
	int vertices,
	int vertice,
	int **Descoberta,
	int **Explorada,
	int *Visitado) {
	 //clock_t tempo; //teste de tempo iniciado
	 //tempo = clock();

	if (Matriz[vertice]) {
		Visitado[vertice] = 1;
	}

	int i, j;
	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			// checa se a aresta existe, se o vertice ja foi visitado e se a
			// aresta nao foi explorada
			if (Matriz[i][j] == 1 && Visitado[i] == 1 && Explorada[i][j] == 0) {
				Explorada[i][j] = 1;

				if (Visitado[j] == 0) { // se o vertice j nao for visitado, ele
										// visita e descobre a aresta
					Visitado[j] = 1;

					Descoberta[i][j] = 1;
				}
			}
		}
	}
	//printf("Tempo Busca :%f\n",(clock() - tempo) /
	//(double)CLOCKS_PER_SEC);
}

void BuscaCompleta(
	int **Matriz,
	int vertices,
	int **Descoberta,
	int **Explorada,
	int *Visitado) {
	// clock_t tempo; //teste de tempo iniciado
	// tempo = clock();
	// Cria Lista Visitados.

	Visitado = (int *)malloc(vertices * sizeof(int));
	int i, j;
	for (i = 0; i < vertices; i++) {
		Visitado[i] = 0;
	}

	// Cria Lista Aresta Explorada

	Explorada = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Explorada[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Explorada[i][j] = 0;
		}
	}

	// Cria Lista Aresta Descoberta

	Descoberta = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Descoberta[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Descoberta[i][j] = 0;
		}
	}

	for (i = 0; i < vertices; i++) {
		if (Visitado[i] == 0) {
			Busca(Matriz, vertices, i, Descoberta, Explorada, Visitado);
		}
	}

  free(Descoberta);
	free(Explorada);
	free(Visitado);

	// printf("Tempo Busca completa:%f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
   //Tempo 0.000010 para 5 vertices e 6 arestas
   //Tempo 0.000078 para 50 vertices e 49 arestas
   //Tempo 0.000221 para 100 vertices e 100 arestas
}

int EhConexo(
	int **Matriz,
	int vertices,
	int **Descoberta,
	int **Explorada,
	int *Visitado) {
	 //clock_t tempo; //teste de tempo iniciado
	 //tempo = clock();
	 //Cria Lista Visitados.

	Visitado = (int *)malloc(vertices * sizeof(int));
	int i, j;
	for (i = 0; i < vertices; i++) {
		Visitado[i] = 0;
	}

	// Cria Lista Aresta Explorada

	Explorada = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Explorada[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Explorada[i][j] = 0;
		}
	}

	// Cria Lista Aresta Descoberta

	Descoberta = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Descoberta[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Descoberta[i][j] = 0;
		}
	}

	Busca(Matriz, vertices, 0, Descoberta, Explorada, Visitado);

	for (i = 0; i < vertices; i++) {
		if (Visitado[i] == 0) {
			return 0;
		}
	}
  free(Descoberta);
	free(Explorada);
	free(Visitado);

	 //printf("Tempo EhConexo:%f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
   return 1;
}

int TemCiclo(
	int **Matriz,
	int vertices,
	int **Descoberta,
	int **Explorada,
	int *Visitado) {
	 //clock_t tempo; //teste de tempo iniciado
	 //tempo = clock();

	// Cria Lista Visitados.

	Visitado = (int *)malloc(vertices * sizeof(int));
	int i, j;
	for (i = 0; i < vertices; i++) {
		Visitado[i] = 0;
	}

	// Cria Lista Aresta Explorada

	Explorada = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Explorada[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Explorada[i][j] = 0;
		}
	}

	// Cria Lista Aresta Descoberta

	Descoberta = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Descoberta[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Descoberta[i][j] = 0;
		}
	}

	for (i = 0; i < vertices; i++) {
		if (Visitado[i] == 0) {
			Busca(Matriz, vertices, i, Descoberta, Explorada, Visitado);
		}
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			if (Descoberta[i][j] == 0) {
				//printf("Tempo TemCliclo:%f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
        return 1;
			}
		}
	}


	free(Descoberta);
	free(Explorada);
	free(Visitado);

	 //printf("Tempo TemCliclo:%f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
   return 0;
}

int EhFloresta(
	int **Matriz,
	int vertices,
	int **Descoberta,
	int **Explorada,
	int *Visitado) {
	 //clock_t tempo; //teste de tempo iniciado
	 //tempo = clock();
	if (TemCiclo(Matriz, vertices, Descoberta, Explorada, Visitado) == 0) {
		//printf("Tempo EhFloresta:%f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
    return 1;
	}
  
  //printf("Tempo EhFloresta:%f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
  return 0;
	free(Descoberta);
	free(Explorada);
	free(Visitado);
	
   
}

int EhArvore(
	int **Matriz,
	int vertices,
	int **Descoberta,
	int **Explorada,
	int *Visitado) {
	 clock_t tempo; //teste de tempo iniciado
	 tempo = clock();

	// Cria Lista Visitados.

	Visitado = (int *)malloc(vertices * sizeof(int));
	int i, j;
	for (i = 0; i < vertices; i++) {
		Visitado[i] = 0;
	}

	// Cria Lista Aresta Explorada

	Explorada = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Explorada[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Explorada[i][j] = 0;
		}
	}

	// Cria Lista Aresta Descoberta

	Descoberta = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Descoberta[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Descoberta[i][j] = 0;
		}
	}

	Busca(Matriz, vertices, 0, Descoberta, Explorada, Visitado);

	for (i = 0; i < vertices; i++) {

		if (Visitado[i] == 0) {
			//printf("Tempo EhArvore:%f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
      return 0;
		}
	}

	for (i = 0; i < vertices; i++) {
		if (Visitado[i] == 0) {
			Busca(Matriz, vertices, i, Descoberta, Explorada, Visitado);
		}
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			if (Descoberta[i][j] == 0) {
				//printf("Tempo EhArvore:%f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
        return 0;
			}
		}
	}
	//printf("Tempo EhArvore:%f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
  return 1;
	free(Descoberta);
	free(Explorada);
	free(Visitado);

	
}

void ObterFlorestaGeradora(
	int **Matriz,
	int vertices,
	int **Descoberta,
	int **Explorada,
	int *Visitado) {
	//clock_t tempo; //teste de tempo iniciado
  //tempo = clock();
	int i, j;
	int **Grafo;
	Grafo = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Grafo[i] = (int *)malloc(vertices * sizeof(int));
	}

	// Cria Lista Visitados.

	Visitado = (int *)malloc(vertices * sizeof(int));

	for (i = 0; i < vertices; i++) {
		Visitado[i] = 0;
	}

	// Cria Lista Aresta Explorada

	Explorada = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Explorada[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Explorada[i][j] = 0;
		}
	}

	// Cria Lista Aresta Descoberta

	Descoberta = (int **)malloc(vertices * sizeof(int *));
	for (i = 0; i < vertices; i++) {
		Descoberta[i] = (int *)malloc(vertices * sizeof(int));
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			Descoberta[i][j] = 0;
		}
	}

	for (i = 0; i < vertices; i++) {
		if (Visitado[i] == 0) {
			Busca(Matriz, vertices, i, Descoberta, Explorada, Visitado);
		}
	}

	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			if (Descoberta[i][j] == 1) {
				Grafo[i][j] = 1;
			} else {
				Grafo[i][j] = 0;
			}
		}
	}

  //printf("Para a arvore geradora desse grafo temos:\n");
	//ImprimeMatriz(Grafo, vertices);

	free(Grafo);
  for(i=0;i<vertices;i++){
    free(Descoberta[i]);
	  free(Explorada[i]);
  }
	free(Visitado);

	//printf("Tempo ObterFlorestaGeradora:%f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
}

void ImprimeMatriz(int **Matriz, int n) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (Matriz[i][j] && i < j) {
				printf("Existe aresta entre %d e %d\n", i, j);
			}
		}
	}

	printf("\n\n");
}

void RemoveAresta(int **Matriz, int v1, int v2) {
	Matriz[v1][v2] = 0;
	Matriz[v2][v1] = 0;
}

void AdicionaAresta(int **Matriz, int v1, int v2) {
	Matriz[v1][v2] = 1;
	Matriz[v2][v1] = 1;
}

void Vizinhos(int **Matriz, int n, int v) {
	int i, j;
	int TemVizinho = 0;

	printf("Vizinhos do vertice %d:\n", v);

	for (i = 0; i < n; i++) {
		if (Matriz[v][i]) {
			printf("Vertice %d\n", i);
			TemVizinho = 1;
		}
	}

	if (TemVizinho == 0) {
		printf("Nenhum!\n");
	}
}

int **AdicionaVertice(int **Matriz, int *N) {
	int **MatrizNova = NULL;
	int i, j;
	int Vertices = (*N);
	int NovoVertices = (*N) + 1;

	MatrizNova = (int **)malloc(NovoVertices * sizeof(int *));
	for (i = 0; i < NovoVertices; i++) {
		MatrizNova[i] = (int *)malloc(NovoVertices * sizeof(int));
	}

	for (i = 0; i < Vertices; i++) {
		for (j = 0; j < Vertices; j++) {
			MatrizNova[i][j] = Matriz[i][j];
		}
	}

	for (i = 0; i < NovoVertices; i++) {
		MatrizNova[i][Vertices] = 0;
		MatrizNova[Vertices][i] = 0;
	}

	for (i = 0; i < Vertices; i++) {
		free(Matriz[i]);
	}

	(*N)++;

	return MatrizNova;
}

int **RemoveVertice(int **Matriz, int *N, int V) {
	int **MatrizNova = NULL;
	int i, j;
	int Vertices = (*N);
	int NovoVertices = (*N) - 1;

	MatrizNova = (int **)malloc(NovoVertices * sizeof(int *));
	for (i = 0; i < NovoVertices; i++) {
		MatrizNova[i] = (int *)malloc(NovoVertices * sizeof(int));
	}

	for (i = 0; i < Vertices; i++) {
		for (j = 0; j < Vertices; j++) {
			if (i < V && j < V) {
				MatrizNova[i][j] = Matriz[i][j];
			} else if (i < V && j > V) {
				MatrizNova[i][j - 1] = Matriz[i][j];
			} else if (i > V && j < V) {
				MatrizNova[i - 1][j] = Matriz[i][j];
			} else if (i > V && j > V) {
				MatrizNova[i - 1][j - 1] = Matriz[i][j];
			}
		}
	}

	for (i = 0; i < Vertices; i++) {
		free(Matriz[i]);
	}

	(*N)--;

	return MatrizNova;
}
