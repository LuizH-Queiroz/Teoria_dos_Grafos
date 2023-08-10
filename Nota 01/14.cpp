/*
Uma trilha é um passeio que não repete arestas.

Escreva uma função que determine se uma dada sequência de vértices constitui uma trilha em  G.
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
         * Retorna verdadeiro se o conjunto de vértices formar uma trilha no grafo.
         * Retorna falso caso contrário.
        */
        bool EhTrilha(vector<int>& vertices) {
            // Se não há nenhum vértice, não é uma trilha (mas é permitido
            // não ter nenhuma aresta)
            if (vertices.size() == 0)
                return false;

            // Se o conjunto consistir de um único vértice, só é necessário
            // verificar se o vértice é válido ou não
            if (vertices.size() == 1)
                if (VerticeValido(vertices[0]))
                    return true;
                else
                    return false;
            

            /*
            matrizTrilha:   Matriz de adjacências do conjunto de vértices recebido como parâmetro.
                            Para não ocupar memória desnecessariamente, a matriz terá tamanho
                            K x K, sendo K o número de vértices no conjunto.
                                
                            Para usar a matriz corretamente é necessário o uso da estrutura auxiliar
                            "verticesHash", para indicar corretamente o índice de um vértice
                            na matriz.


            vecticesHash:   Os vértices do grafo (nessa classe GrafoSimples) são classificados
                            com números inteiros positivos >= 0. Se o grafo tem K vértices, portanto,
                            eles estão no intervalo [0, K-1].
                            Sendo assim, se o vector de vértices recebido como parâmetro for válido,
                            seus vértices irão variar no intervalo [0, QuantidadeVertices()-1].

                            Para cada vértice "i", "verticesHash[i]" informa a posição do vértice "i"
                            na matriz de adjacências.
                            Se "verticesHash[i] == -1", então o vértice "i" não faz parte do conjunto
            */
            vector<int> verticesHash(QuantidadeVertices(), -1);
            vector<vector<int>> matrizTrilha;
            int proximoIndice = 0; // Variável auxiliar para determinar o índice que um vértice válido
                                   // ocupará na matriz de adjacências (matrizTrilha)

            // Verifica se todos os vértices no vector são válidos
            for (int i = 0; i < vertices.size(); i++)
            {
                if (!VerticeValido(vertices[i]))
                    return false;
                
                verticesHash[vertices[i]] = proximoIndice;
                proximoIndice++;
            }


            // Se todos os vértices no conjunto são válidos, podemos inicializar matrizTrilha
            // com o tamanho correto.
            // A matriz começa com todos os valores iguais a 0, ou seja, indicando que
            // no momento não foi marcada nenhuma aresta
            matrizTrilha = vector<vector<int>>(vertices.size(), vector<int>(vertices.size(), 0));


            // Verifica se há aresta repetida
            int indiceV1;
            int indiceV2;

            for (int i = 0; i < vertices.size()-1; i++)
            {
                indiceV1 = verticesHash[vertices[i]];
                indiceV2 = verticesHash[vertices[i+1]];

                if (matrizTrilha[indiceV1][indiceV2] == 1) // A aresta é repetida
                    return false;
                
                // Como a aresta não é repetida, marcamos ela na matriz
                matrizTrilha[indiceV1][indiceV2] = 1;
                matrizTrilha[indiceV2][indiceV1] = 1;
            }


            // Como nenhuma aresta se repete, a sequência de vértices constitui
            // uma Trilha
            return true;
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));

    vector<int> verticesTrilha = {2, 0, 1, 3, 2, 5, 6, 4};

    if (grafo.EhTrilha(verticesTrilha))
    {
        cout << "O conjunto de vertices eh um Trilha!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um Trilha!" << endl;
    }


    return 0;
}