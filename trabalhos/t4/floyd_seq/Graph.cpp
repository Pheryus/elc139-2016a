#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Graph.h"


Graph::Graph() : 
   n(0), 
   mat(NULL)
{ }
   

Graph::~Graph()
{
   delete[] mat;
}      


Graph& 
Graph::operator=(const Graph& g)
{
   if (this == &g) // auto-atribuição
      return *this;

   if (n != g.n)
   {
      n = g.n;
      delete[] mat;
      mat = new int[n*n];
   }
   
   for (int ni = 0; ni < n*n; ni++)
      mat[ni] = g.mat[ni];
   
   return *this;
}
     
/**
 Gera um grafo de tamanho s, criando arestas aleatoriamente.
 @param[in]   s   Tamanho do grafo.
 @param[in]   d   Densidade da matriz de adjacência (%)
 @param[in]   mw  Peso máximo de uma aresta.
 */
void 
Graph::generate(const int s, const int d, const int mw)
{
   assert(n == 0 && mat == NULL && s > 0); // O grafo tem que estar vazio
   
   n = s;
   mat = new int[n * n];
   
   // Inicialização do gerador de números aleatórios 
   // (para um mesmo n, deseja-se obter uma mesma seqüência de números).
   srand(n);
   
   for (int i = 0; i < n; i++)
   {   
      for (int j = 0; j < n; j++)
      {
         generateEdge(i, j, d, mw);
      }
   }
}

void
Graph::generateEdge(int i, int j, int d, int mw)
{
   assert(i < n && j < n);
   
   // O grafo é acíclico, portanto não há aresta se o nó destino
   // for igual ao nó origem.   
   if (i == j)
      mat[i*n+j] = noEdge;
   // Decide se haverá ou não uma aresta entre i e j,
   // levando em conta a densidade desejada para a matriz de custos.
   else if (rand() % (100/d) > 0)
      mat[i*n+j] = noEdge;
   else // Sorteia o peso da aresta entre i e j.
      mat[i*n+j] = rand() % mw + 1;   
}
      
int 
Graph::size() const
{
   return n;
}

int 
Graph::getWeight(int i, int j) const
{
   assert(i < n && j < n && hasEdge(i,j)); // A aresta deve existir.
   return mat[i*n+j];
}

void 
Graph::setWeight(int i, int j, int w)
{
   assert(i < n && j < n && hasEdge(i,j) && w > 0); // A aresta deve existir.
   mat[i*n+j] = w;
}

void
Graph::insertEdge(int i, int j, int w)
{
   assert(i < n && j < n && w > 0); // O peso deve ser positivo.
   mat[i*n+j] = w;
}

void
Graph::removeEdge(int i, int j)
{
   assert(i < n && j < n && hasEdge(i,j)); // A aresta deve existir.
   mat[i*n+j] = noEdge;
}

bool
Graph::hasEdge(int i, int j) const
{
   assert(i < n && j < n);
   return !(mat[i*n+j] == noEdge);
}


std::ostream&
operator<< (std::ostream& s, const Graph& g)
{
   if (g.n == 0)
      return s;
      
   s << g.n << std::endl;
   for (int i = 0; i < g.n; i++) 
   {
      for (int j = 0; j < g.n; j++) 
      {
         s << g.mat[i*g.n+j] << " ";
      }
      s << std::endl;
   }
   return s;
}

         
std::istream&
operator>> (std::istream& s, Graph& g)
{
   assert(g.n == 0 && g.mat == NULL);
   s >> g.n;
   g.mat = new int[g.n * g.n];
   
   for (int i = 0; i < g.n; i++) 
   {
      for (int j = 0; j < g.n; j++) 
      {
         s >> g.mat[i*g.n+j];
      }
   }
   return s;
}


int
Graph::writeTo(char* fname)
{
   std::ofstream fout(fname);
   if (!fout)
      return 0;
   fout << (*this);
   fout.close();
   return 1;
}

int
Graph::readFrom(char* fname)
{
   std::ifstream fin(fname);
   if (!fin)
      return 0;
   fin >> (*this);
   fin.close();
   return 1;
}

      
DotGraphEncoder::DotGraphEncoder(const Graph& g_) :
   g(g_)
{ }

std::ostream&
operator<< (std::ostream& s, const DotGraphEncoder& e)
{
   if (e.g.size() == 0)
      return s;
      
   s << "digraph G {" << std::endl;
   for (int i = 0; i < e.g.size(); i++) 
   {
      for (int j = 0; j < e.g.size(); j++) 
      {
         if (e.g.hasEdge(i,j))
            s << i << "->" << j << "[label=" << e.g.getWeight(i,j) 
              << "];" << std::endl;
      }
   }
   s << "}" << std::endl;
   return s;
}
