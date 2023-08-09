/*
Um caminho é um passeio que não repete vértices. O passeio 1,2,3,4 é um caminho no grafo da Figura 1.

Escreva uma função que determine se uma dada sequência de vértices constitui um caminho em G.
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
         * Retorna a quantidade de vértices do grafo
        */
        int QuantidadeVertices() {
            return matriz.size();
        }


        /**
         * Retorna verdadeiro se o conjunto de vértices formar um caminho no grafo.
         * Retorna falso caso contrário.
        */
        bool EhCaminho(vector<int>& vertices) {
            // Se não há nenhum vértice, não é um caminho
            if (vertices.size() == 0)
                return false;
            
            // Se o conjunto de vértices tiver tamanho um, ele não será verificado
            // no laço "for" a seguir, então sua validade é verificada mais cedo
            if (!VerticeValido(vertices[0]))
                return false;


            // vector usado para indicar se um vértice já foi usado ou não no caminho
            vector<bool> usado(QuantidadeVertices(), false);
            usado[vertices[0]] = true; // Como vamos começar a percorrer o caminho a partir
                                       // de vertices[0], ele já começa marcado como usado

            // Verifica a validade dos vértices e arestas no caminho
            for (int i = 0; i < vertices.size()-1; i++)
            {
                if (!VerticeValido(vertices[i]) || !VerticeValido(vertices[i+1]))
                    return false;
                
                if (matriz[vertices[i]][vertices[i+1]] == 0) // Não há aresta conectando os vértices
                    return false;
                
                if (usado[vertices[i+1]]) // O próximo vértice é repetido
                    return false;
                
                // Vértices e aresta válidos
                usado[vertices[i+1]] = true;
            }

            // Se todos os vértices e arestas são válidos, então o caminho é válido
            return true;
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));

    vector<int> verticesCaminho = {0, 1, 3, 2, 5, 4, 6, 5};

    if (grafo.EhCaminho(verticesCaminho))
    {
        cout << "O conjunto de vertices eh um caminho!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um caminho!" << endl;
    }


    return 0;
}