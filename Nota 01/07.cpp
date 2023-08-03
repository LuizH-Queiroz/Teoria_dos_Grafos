/*
Escreva uma função que informe se G é completo, ou seja, se ele possui todas as arestas possíveis.
Sendo n o número de vértices de G, vimos em sala que um grafo simples pode ter de 0 a n(n−1)/2 arestas.
Portanto, o grafo completo com n vértices, denotado por Kn, possui n(n−1)/2 arestas. Abaixo ilustra-se o grafo K7.
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
         * Retorna verdadeiro se o grafo é completo.
         * Retorna falso caso contrário.
        */
        bool EhCompleto() {
            // Armazenará o somatório dos graus
            int somaGraus = 0;

            for (int i = 0; i < lista.size(); i++)
                somaGraus += lista[i].size();
            
            // Verifica se a soma dos graus é igual ao dobro do máximo de arestas
            return (somaGraus == (QuantidadeVertices() * (QuantidadeVertices()-1)));
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));

    if (grafo.EhCompleto())
    {
        cout << "O grafo eh completo!" << endl;
    }
    else
    {
        cout << "O grafo NAO eh completo!" << endl;
    }


    return 0;
}