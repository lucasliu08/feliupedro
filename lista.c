include <stdio.h>
#include <stdlib.h>

/* lista de adjacencia */

struct vizinhos
{
    int valor;
    struct vizinhos* prox;
};


struct vertice
{
    int valor;
    struct vertice* prox;
    struct vizinhos* listavizinhos;
};

struct ArestaRotulada
{
  int explorada;
  int descoberta;
  int v1;
  int v2;
};

struct vizinhos* criaVizinho(int);
struct vertice* criaVertice(int);
struct vertice* BuscaVertice(struct vertice*, int);
struct vizinhos* BuscaVizinho(struct vizinhos*, int);
void LimpaListaVertice(struct vertice **);
void LimpaListaVizinhos(struct vizinhos **);
void InsereVerticeFim(struct vertice**, int, int*);
void InsereVizinhoFim(struct vizinhos**, int);
void ExcluiVizinho(struct vizinhos**, int);
void ExcluiVertice(struct vertice**, int, int*);
void ExcluiAresta(struct vertice**, int, int);
void AdicionaAresta(struct vertice**, int, int);
void ImprimeVizinhos(struct vizinhos*);
void ImprimeGrafo(struct vertice*);

void BuscaGrafo(int, int**, struct ArestaRotulada**, int);
void BuscaCompleta(int**, struct ArestaRotulada**, int, int);
int EhConexo(int, int**, struct ArestaRotulada**, int, int);
int TemCiclo(int**, struct ArestaRotulada**, int, int);
int EhFloresta(int**, struct ArestaRotulada**, int, int);
int EhArvore(int, int**, struct ArestaRotulada**, int, int);
void ObterFlorestaGeradora(int**, struct ArestaRotulada**, struct vertice**, int, int);


int main()
{
    //ListaVertice = no cabeca da lista encadeada
    //VerticesVisitados = vetor onde cada casa representa seu respectivo
    //vertice e seu valor (1 ou 0) representa se esse vertice foi visitado ou nao
    
    //ListaArestas = lista de arestas, seus vertices e se essas foram exploradas
    // e/ou descobertas (definida pelo struct ArestaRotulada acima da main)

    FILE* Arquivo = NULL; struct vertice* ListaVertice = NULL;
    struct vertice* FlorestaGeradora = NULL;
    int VerticesLidos = 0; int arestas = 0; int i, j, v1, v2;
    int VerticesAdicionados = 0; int VerticesAdiFlor = 0; struct vertice* TempVert;
    int* VerticesVisitados = NULL; struct ArestaRotulada* ListaArestas = NULL;
    ////////////////////////////////////////////////////


    //abre arquivo, le N e M
    Arquivo = fopen ("grafo1.txt","r");
    fscanf(Arquivo, "%d\t%d", &VerticesLidos , &arestas);
    ////////////////////////////////////////////////////


    VerticesVisitados = (int*) malloc(sizeof(int) * VerticesLidos);
    ListaArestas = (struct ArestaRotulada*) malloc(sizeof(struct ArestaRotulada) * arestas);


    for(i = 0; i < VerticesLidos; i++)
    {
      InsereVerticeFim(&ListaVertice, i, &VerticesAdicionados);
      InsereVerticeFim(&FlorestaGeradora, i, &VerticesAdiFlor);
      VerticesVisitados[i] = 0;
    }

    for(i = 0; i < arestas; i++)
    {
      fscanf(Arquivo, "%d\t%d", &v1, &v2);
      AdicionaAresta(&ListaVertice, v1, v2);
      ListaArestas[i].explorada = 0;
      ListaArestas[i].descoberta = 0;
      ListaArestas[i].v1 = v1;
      ListaArestas[i].v2 = v2;
    }

    



    //BuscaGrafo(0, &VerticesVisitados, &ListaArestas, arestas);

    //BuscaCompleta(&VerticesVisitados, &ListaArestas, arestas, VerticesLidos);


    //ObterFlorestaGeradora(&VerticesVisitados, &ListaArestas, &FlorestaGeradora, arestas, VerticesLidos);

    //EhConexo(0, &VerticesVisitados, &ListaArestas, VerticesLidos, arestas); 
    
    //TemCiclo(&VerticesVisitados, &ListaArestas, VerticesLidos, arestas);
    
    
    //EhFloresta(&VerticesVisitados, &ListaArestas, VerticesLidos, arestas);
    
    
    //EhArvore(0, &VerticesVisitados, &ListaArestas, VerticesLidos, arestas);







    free(ListaArestas);
    free(VerticesVisitados);
    LimpaListaVertice(&ListaVertice);
    LimpaListaVertice(&FlorestaGeradora);
    fclose(Arquivo);
    return 0;
}


struct vizinhos* criaVizinho(int v)
{
    struct vizinhos* p = (struct vizinhos*) malloc(sizeof(struct vizinhos));
    p->valor = v;
    p->prox = NULL;

    return p;
}


struct vertice* criaVertice(int v)
{
    struct vertice* p = (struct vertice*) malloc(sizeof(struct vertice));
    p->valor = v;
    p->prox = NULL;
    p->listavizinhos = NULL;

    return p;
}


void LimpaListaVertice(struct vertice ** p)
{
    if (*p)
    {
        LimpaListaVertice(&((*p)->prox));
        LimpaListaVizinhos(&((*p)->listavizinhos));
        free(*p);
        *p = NULL;
    }
}


void LimpaListaVizinhos(struct vizinhos ** p)
{
    if (*p)
    {
        LimpaListaVizinhos(&((*p)->prox));
        free(*p);
        *p = NULL;
    }
}


void InsereVerticeFim(struct vertice** p, int v, int* N)
{
    if (*p)
    {
        InsereVerticeFim(&((*p)->prox), v, N);
    }

    else
    {
        struct vertice* elem = criaVertice(v);
        elem->prox = NULL;
        elem->listavizinhos = NULL;
        *p = elem;

        (*N)++;
    }
}


void InsereVizinhoFim(struct vizinhos** p, int v)
{
    if (*p)
    {
        InsereVizinhoFim(&((*p)->prox), v);
    }

    else
    {
        struct vizinhos* elem = criaVizinho(v);
        elem->prox = NULL;
        *p = elem;
    }
}


struct vertice* BuscaVertice(struct vertice* p, int v)
{
    if (p)
    {
        if (v == p->valor)
        {
            return p;
        }

        else
        {
            return BuscaVertice(p->prox, v);
        }
    }

    else
    {
        return NULL;
    }
}


struct vizinhos* BuscaVizinho(struct vizinhos* p, int v)
{
    if (p)
    {
        if (v == p->valor)
        {
            return p;
        }

        else
        {
            return BuscaVizinho(p->prox, v);
        }
    }

    else
    {
        return NULL;
    }
}


void ExcluiVizinho(struct vizinhos** p, int v)
{
    if (*p)
    {
        if (v == (*p)->valor)
        {
            struct vizinhos* e = *p;
            *p = e->prox;
            free(e);
        }

        else
        {
            ExcluiVizinho(&((*p)->prox), v);
        }
    }
}


void ExcluiVertice(struct vertice** p, int v, int* N)
{
    if(*p)
    {
      ExcluiVertice( &((*p)->prox), v, N);
      ExcluiVizinho( &((*p)->listavizinhos), v );
      if((*p)->valor == v)
      {
        struct vertice* e = *p;
        *p = e->prox;
        free(e);


        (*N)--;
      }

      else
      {
        ExcluiVertice( &((*p)->prox), v, N);
      }
    }
}


void ExcluiAresta(struct vertice** p, int u, int v)
{
    struct vertice* VerticeU = BuscaVertice(*p, u);
    struct vertice* VerticeV = BuscaVertice(*p, v);

    ExcluiVizinho( &(VerticeU->listavizinhos), v);
    ExcluiVizinho( &(VerticeV->listavizinhos), u);
}


void AdicionaAresta(struct vertice** p, int u, int v)
{
    struct vertice* VerticeU = BuscaVertice(*p, u);
    struct vertice* VerticeV = BuscaVertice(*p, v);

    InsereVizinhoFim( &(VerticeU->listavizinhos), v);
    InsereVizinhoFim( &(VerticeV->listavizinhos), u);
}


void ImprimeVizinhos(struct vizinhos* p)
{
  if (p)
  {
    printf("Vertice %d\n", p->valor);
    ImprimeVizinhos(p->prox);
  }
  else
  {
    printf("Sem mais vizinhos.\n");
  }
}


void ImprimeGrafo(struct vertice* p)
{
  if (p)
  {
    printf("Vizinhos do vertice %d:\n", p->valor);
    ImprimeVizinhos(p->listavizinhos);
    printf("\n\n");
    ImprimeGrafo(p->prox);
  }
}



void BuscaGrafo(int r, int** V, struct ArestaRotulada** E, int m)
{
  (*V)[r] = 1; int i;
  
  for(i = 0; i < m; i++)
  {
    if((*E)[i].explorada == 0 && (*V)[(*E)[i].v1] == 1)
    {
      (*E)[i].explorada = 1;

      if( (*V)[(*E)[i].v2] == 0 )
      {
        (*V)[(*E)[i].v2] = 1;
        
        (*E)[i].descoberta = 1;
      }
    }

    if((*E)[i].explorada == 0 && (*V)[(*E)[i].v2] == 1)
    {
      (*E)[i].explorada = 1;
      
      if( (*V)[(*E)[i].v1] == 0 )
      {
        (*V)[(*E)[i].v1] = 1;
        
        (*E)[i].descoberta = 1;
      }
    }
  }
}



void BuscaCompleta(int** V, struct ArestaRotulada** E, int m, int n)
{
  int i;

  for(i = 0; i < m; i++)
  {
    (*E)[i].descoberta = 0;
    (*E)[i].explorada = 0;
  }

  for(i = 0; i < n; i++)
  {
    (*V)[i] = 0;
  }

  for(i = 0; i < n; i++)
  {
    if((*V)[i] == 0)
    {
      BuscaGrafo(i, V, E, m);
    }
  }
}


int EhConexo(int r, int** V, struct ArestaRotulada** E, int n, int m)
{
  BuscaGrafo(r, V, E, m);
  
  int i;
  for(i = 0; i < n; i++)
  {
    if ((*V)[i] == 0)
    {
      return 0;
    }
  }

  return 1;
}


int TemCiclo(int** V, struct ArestaRotulada** E, int n, int m)
{
  BuscaCompleta(V, E, m, n);

  int i;
  for(i = 0; i < m; i++)
  {
    if((*E)[i].descoberta == 0)
    {
      return 1;
    }
  }

  return 0;
}


int EhFloresta(int** V, struct ArestaRotulada** E, int n, int m)
{
  if(TemCiclo(V, E, n, m)  == 0)
  {
    return 1;
  }

  else
  {
    return 0;
  }

}


int EhArvore(int r, int** V, struct ArestaRotulada** E, int n, int m)
{
  BuscaGrafo(r, V, E, m);

  int i;
  for(i=0; i < n; i++)
  {
    if((*V)[i] == 0)
    {
      return 0;
    }
  }
  
  for(i = 0; i < m; i++)
  {
    if((*E)[i].descoberta == 0)
    {
      return 0;
    }
  }

  return 1;
}


void ObterFlorestaGeradora(int** V, struct ArestaRotulada** E, struct vertice** T, int m, int n)
{
  BuscaCompleta(V, E, m, n);
  int i; int j = 0;
  for(i = 0; i < m; i++)
  {
    if((*E)[i].descoberta == 1)
    {
      AdicionaAresta( T, (*E)[i].v1, (*E)[i].v2 );
    }
  }
}
