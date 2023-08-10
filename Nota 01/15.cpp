/*
Um subconjunto de vértices  S⊆V  é um clique de  G  se, para quaisquer dois vértices distintos  i,j ∈ S ,
existe a aresta  (i,j)  no grafo. Portanto, os vértices de um clique estão dois a dois conectados por uma aresta.
Os seguintes conjuntos são exemplos de clique do grafo da Figura 1:  {1,2},{1,2,3},{1,2,3,4}.

Escreva uma função que determine se um dado conjunto de vértices constitui um clique de  G .
*/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#define ARQUIVO "Grafos/01.txt"


using namespace std;



/******************************/
/* Classe de um Grafo Simples */
/******************************/

class GrafoSimples {
    private:

        vector<vector<int>> matriz; // Matriz de Adjacências
        vector<vector<int>> lista; // Lista de Adjacências
    

    public:


        /**
         * Cria a matriz e lista de adjacências de um grafo simples a partir de um arquivo de texto
         * com formato/organização pré-definido
        */
        bool LerArquivo(string nomeArquivo) {
            ifstream arquivoLeitura(nomeArquivo);

            // Testa se a abertura do arquivo foi bem-sucedida            
            if (!arquivoLeitura.is_open())
                return false;
            

            /* Leitura do arquivo e atribuição dos valores à Matriz e à Lista de Adjacências */            
            int n_vertices;
            int tem_ligacao; // 1 - Se há ligação entre os vértives "i" e "j"
                             // 0 - Se não há ligação entre os vértices "i" e "j"

            arquivoLeitura >> n_vertices;
            matriz = vector<vector<int>>(n_vertices, vector<int>(n_vertices)); // Mudando a matriz para o tamanho
                                                                               // n_vertices X n_vertices
            lista = vector<vector<int>>(n_vertices); // Há n_vertices linhas, mas nenhuma coluna (no momento,
                                                     // nenhum vértice possui ligação)

            for (int i = 0; i < n_vertices; i++)
            {
                for (int j = 0; j < n_vertices; j++)
                {
                    arquivoLeitura >> tem_ligacao;

                    matriz[i][j] = tem_ligacao;
                    if (tem_ligacao)
                        lista[i].push_back(j);
                }
            }

            // Criação do grafo foi bem-sucedida
            return true;
        }


        /**
         * Informa se um determinado vértice é válido (está no grafo) ou não
        */
        bool VerticeValido(int v) {
            return (v >= 0 && v < matriz.size());
        }


        /**
         * Retorna verdadeiro se o conjunto de vértices formar um clique.
         * Retorna falso caso contrário.
        */
        bool EhClique(vector<int>& vertices) {
            // Não tem como ser um clique se não há nenhum vértice
            if (vertices.size() == 0)
                return false;
            

            // Verifica se todos os vértices são válidos
            for (int i = 0; i < vertices.size(); i++)
            {
                if (!VerticeValido(vertices[i]))
                    return false;
            }


            // Verifica se o conjunto de vértices tem todas as ligações necessárias para
            // formar um clique
            for (int i = 0; i < vertices.size()-1; i++)
            {
                for (int j = i+1; j < vertices.size(); j++)
                {
                    if (matriz[vertices[i]][vertices[j]] == 0)
                        return false;
                }
            }

            // Se todos os vértices são válidos e todas as arestas necessárias existem,
            // então o conjunto é um clique 
            return true;
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));

    vector<int> verticesClique = {0, 1, 2, 3};

    if (grafo.EhClique(verticesClique))
    {
        cout << "O conjunto de vertices eh um Clique!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um Clique!" << endl;
    }


    return 0;
}