/*
O complemento de  G  é um grafo  G¯=(V,E¯)  que possui os mesmos vértices de  G , mas cujo conjunto de arestas é o complemento
do conjunto de arestas de  G . Portanto, uma aresta  (i,j)  pertence a  E¯  se, e somente se, ela não pertece a  E.
O grafo abaixo corresponde ao complemento do grafo ilustrado na Figura 1.

Escreva uma função que receba um grafo como parâmetro e retorne o seu complemento.
Observe que o retorno da função consiste em um grafo.
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
         * Exiba a Matriz de Adjacências do grafo
        */
        void ExibeMatrizAdjacencias() {

                cout << endl;
                cout << "Matriz de Adjacencias:" << endl;

                for (int i = 0; i < matriz.size(); i++)
                {
                    for (int j = 0; j < matriz.size(); j++)
                    {
                        cout << matriz[i][j]  << " ";
                    }
                    cout << endl;
                }
        }


        /**
         * Exibe a Lista de Adjacências do grafo
        */
        void ExibeListaAdjacencias() {

            cout << endl;
            cout << "Lista de Adjacencias:" << endl;

            for (int i = 0; i < lista.size(); i++)
            {
                cout << i << ": ";
                for (int j = 0; j < lista[i].size(); j++)
                {
                    cout << lista[i][j];
                    if (j < (lista[i].size()-1))
                        cout << ", ";
                }

                cout << endl;
            }
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
         * Cria e retorna o complemento do grafo como referência
        */
        GrafoSimples CriaComplemento() {
            GrafoSimples complemento;

            // Inicializa a matriz e a lista de adjacências do complemento
            complemento.matriz = vector<vector<int>>(QuantidadeVertices(), vector<int>(QuantidadeVertices()));
            complemento.lista = vector<vector<int>>(QuantidadeVertices());

            // Percorre toda a matriz de adjacências para poder atribuir valor tanto
            // à matriz quanto à lista de adjacências do complemento
            for (int i = 0; i < matriz.size(); i++)
            {
                for (int j = 0; j < matriz[i].size(); j++)
                {
                    if (matriz[i][j] == 0 && i != j)
                    {
                        complemento.matriz[i][j] = 1;
                        complemento.lista[i].push_back(j);
                    }
                    else // matriz[i][j] == 1 || i == j
                    {
                        complemento.matriz[i][j] = 0;
                    }
                }
            }

            return complemento;
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));


    cout << endl;
    cout << "Dados do Grafo Complemento:" << endl;

    GrafoSimples grafoComplemento = grafo.CriaComplemento();
    grafoComplemento.ExibeMatrizAdjacencias();
    grafoComplemento.ExibeListaAdjacencias();

    cout << endl;
    cout << "Fim do Grafo Complemento!" << endl;


    return 0;
}