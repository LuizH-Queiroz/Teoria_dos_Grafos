/*
Um ciclo é um passeio que não repete vértices, com exceção do primeiro e último vértices, que são iguais.
O passeio 1,2,4,3,1 é um ciclo no grafo da Figura 1.

Escreva uma função que determine se uma dada sequência de vértices constitui um ciclo em G.
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
         * Retorna verdadeiro se o conjunto de vértices formar um ciclo no grafo.
         * Retorna falso caso contrário.
        */
        bool EhCiclo(vector<int>& vertices) {
            // São necessários 3 vértices, no mínimo, para formar um ciclo
            if (vertices.size() <= 2)
                return false;

            // Antes de analisar a sequencia de vértices, podemos verificar se
            // o primeiro e último são iguais            
            if (vertices[0] != vertices.back())
                return false;


            // vector usado para indicar se um vértice já foi usado ou não no ciclo
            vector<bool> usado(QuantidadeVertices(), false);
            usado[vertices[0]] = true; // Como vamos começar a percorrer o ciclo a partir
                                       // de vertices[0], ele já começa marcado como usado

            // Verifica a validade dos vértices e arestas no ciclo
            for (int i = 0; i < vertices.size()-1; i++)
            {
                if (!VerticeValido(vertices[i]) || !VerticeValido(vertices[i+1]))
                    return false;
                
                if (matriz[vertices[i]][vertices[i+1]] == 0) // Não há aresta conectando os vértices
                    return false;
                
                // Verifica se o próximo vértice é repetido mas não é o último
                if (usado[vertices[i+1]] && (i+1 < vertices.size()-1))
                    return false;
                
                // Vértices e aresta válidos
                usado[vertices[i+1]] = true;
            }

            // Se todos os vértices e arestas são válidos, então o ciclo é válido
            return true;
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));

    vector<int> verticesCiclo = {0, 1, 3, 2, 0};

    if (grafo.EhCiclo(verticesCiclo))
    {
        cout << "O conjunto de vertices eh um ciclo!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um ciclo!" << endl;
    }


    return 0;
}