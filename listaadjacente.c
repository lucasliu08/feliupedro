#include <stdio.h>
#include <stdlib.h>

/*
lista de adjacencia
X cria grafo lendo de arquivo
X adiciona/remove um vértice
X adiciona/remove uma nova aresta
X retorna uma lista de nós vizinhos de um dado vértice
*/

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


int main()
{
    //inicializa bando de gente
    FILE* Arquivo = NULL; struct vertice* ListaVertice = NULL;
    int VerticesLidos = 0; int arestas = 0; int i, j, v1, v2;
    int VerticesAdicionados = 0; struct vertice* TempVert;
    ////////////////////////////////////////////////////


    //abre arquivo, le N e M
    Arquivo = fopen ("grafo1.txt","r");
    fscanf(Arquivo, "%d\t%d", &VerticesLidos , &arestas);
    ///////////////////////////////////////////////

    for(i = 0; i < VerticesLidos; i++)
    {
      InsereVerticeFim(&ListaVertice, i, &VerticesAdicionados);
    }

    for(i = 0; i < arestas; i++)
    {
      fscanf(Arquivo, "%d\t%d", &v1, &v2);
      AdicionaAresta(&ListaVertice, v1, v2);
    }


    ExcluiVertice(&ListaVertice, 3, &VerticesAdicionados);
    printf("Excluído o vértice 3\n\n");

    ExcluiAresta(&ListaVertice, 0, 4);
    printf("Excluída a aresta 0, 4\n\n");

    ImprimeGrafo(ListaVertice);

    LimpaListaVertice(&ListaVertice);
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
