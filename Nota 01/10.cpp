/*
Escreva uma função que determine se uma lista de vértices e uma lista de arestas informadas pelo usuário representam
um subgrafo H de G. Para H ser subgrafo de G, todos os seus vértices e suas arestas devem estar contidos,
respectivamente, nos conjuntos de vértices e arestas de G. Além disso, os extremos de todas as arestas listadas
pelo usuário devem estar contidos no conjunto de vértices informado, do contrário não se trata de um grafo pois
teríamos uma aresta sem os dois extremos.
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
         * Retorna a quantidade de vértices do grafo
        */
        int QuantidadeVertices() {
            return matriz.size();
        }


        /**
         * Informa se um determinado vértice é válido (está no grafo) ou não
        */
        bool VerticeValido(int v) {
            return (v >= 0 && v < matriz.size());
        }


        /**
         * Retorna verdadeiro se o conjunto de vertices e o conjunto de arestas
         * formar um subgrafo.
         * Caso contrário, retorna falso.
        */
        bool EhSubgrafo(vector<int>& vertices, vector<vector<int>>& arestas) {
            // Se não há nenhum vértice, então não é um subgrafo.
            // O mesmo vale para quando o número de vértices é maior que o grafo.
            if (vertices.size() == 0 || vertices.size() > QuantidadeVertices())
                return false;
            

            /*
            matrizSubgrafo: Matriz de adjacências do subgrafo recebido como parâmetro.
                            Para não ocupar memória desnecessariamente, a matriz terá tamanho
                            K x K, sendo K o número de vértices no subgrafo.
                            
                            Para usar a matriz corretamente é necessário o uso da estrutura auxiliar
                            "verticesHash", para indicar corretamente o índice de um vértice
                            na matriz.


            vecticesHash:   Os vértices do grafo (nessa classe GrafoSimples) são classificados
                            com números inteiros positivos >= 0. Se o grafo tem K vértices, portanto,
                            eles estão no intervalo [0, K-1].
                            Sendo assim, se o vector de vértices recebido como parâmetro for válido,
                            seus vértices irão variar no intervalo [0, QuantidadeVertices()-1].

                            Para cada vértice "i", "verticesHash[i]" informa a posição do vértice "i"
                            na matriz de adjacências do subgrafo.
                            Se "verticesHash[i] == -1", então o vértice "i" não faz parte do subgrafo
            */
            vector<int> verticesHash(QuantidadeVertices(), -1);
            vector<vector<int>> matrizSubgrafo;
            int proximoIndice = 0; // Variável auxiliar para determinar o índice que um vértice válido
                                   // ocupará na matriz de adjacências


            // Verifica se todos os vértices no vector são válidos
            for (int i = 0; i < vertices.size(); i++)
            {
                if (!VerticeValido(vertices[i]))
                    return false;
                
                verticesHash[vertices[i]] = proximoIndice;
                proximoIndice++;
            }


            // Como todos os vértices são válidos, agora podemos criar a matriz de
            // adjacências.
            // A matriz terá tamanho "vertices.size() x vertices.size()", com todos os
            // valores iniciados com 0
            matrizSubgrafo = vector<vector<int>>(vertices.size(), vector<int>(vertices.size(), 0));


            // Testa todas as arestas.
            //
            // Uma aresta será inválida se:
            //      1 - Algum vértice não pertencer ao subgrafo;
            //      2 - For uma aresta paralela;
            //      3 - For um laço
            int vertice1;
            int indiceV1;

            int vertice2;
            int indiceV2;

            for (int i = 0; i < arestas.size(); i++)
            {
                vertice1 = arestas[i][0];
                vertice2 = arestas[i][1];

                /* Verifica se os vértices são e a aresta válidos */

                if (!VerticeValido(vertice1) || !VerticeValido(vertice2))
                    return false;
                
                if (matriz[vertice1][vertice2] == 0)
                    return false;

                if (verticesHash[vertice1] == -1 || verticesHash[vertice2] == -1 || vertice1 == vertice2)
                    return false;
                

                indiceV1 = verticesHash[vertice1];
                indiceV2 = verticesHash[vertice2];

                if (matrizSubgrafo[indiceV1][indiceV2] == 1) // Aresta Paralela
                    return false;

                /**************************************************/

                // Sendo a aresta válida, ela é incluída na matriz de adjacências
                matrizSubgrafo[indiceV1][indiceV2] = 1;
                matrizSubgrafo[indiceV2][indiceV1] = 1;
            }


            // Se todos os vértices e arestas são válidos, definitivamente
            // o subgrafo é válido
            return true;
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));


    vector<int> vertices = {0, 1, 2, 3, 5};
    vector<vector<int>> arestas = {
        {0, 3},
        {2, 1},
        {2, 5}
    };

    if (grafo.EhSubgrafo(vertices, arestas))
    {
        cout << "O subgrafo eh valido!" << endl;
    }
    else
    {
        cout << "O subgrafo NAO eh valido!" << endl;
    }


    return 0;
}