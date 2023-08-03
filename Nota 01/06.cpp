/*
Um grafo é regular se todos os seus vértices possuem o mesmo grau.
Se o grau de todos os vértices for igual a k, diz-se que o grafo é k-regular.
Escreva uma função que informe se G é regular, deixando claro o valor do grau em caso afirmativo.
*/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#define ARQUIVO "Grafos/02.txt"


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
         * Verifica se o gráfo é regular.
         * Quando verdadeiro, a função retorna o grau dos vértices.
         * Caso contrário, retorna -1.
        */
        int EhRegular() {
            if (QuantidadeVertices() == 0)
                return -1;
            
            // Não precisamos verificar se o índice 0 não é vazio, pois a condição anterior
            // nos garante que temos pelo menos um vértice no grafo
            int grau = lista[0].size();
            for (int i = 1; i < lista.size(); i++)
            {
                if (lista[i].size() != grau)
                    return -1;
            }

            // Como nenhum vértice tem grau diferente do primeiro, então o grafo é regular
            return grau;
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));

    if (grafo.EhRegular() != -1)
    {
        cout << "O grafo eh " << grafo.EhRegular() << "-regular!" << endl;
    }
    else
    {
        cout << "O grafo NAO eh regular!" << endl;
    }


    return 0;
}