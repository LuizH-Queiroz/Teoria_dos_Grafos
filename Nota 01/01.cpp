/*
Faça um código que leia o grafo de um arquivo e o represente nas duas formas vistas em sala: matriz de adjacências e lista de adjacências.
Nas próximas questões, leve em conta que as duas representações do grafo estarão disponı́veis para tornar as implementações mais eficientes. 
*/

#include <iostream>
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
                    cout << (lista[i][j] + 1);
                    if (j < (lista[i].size()-1))
                        cout << ", ";
                }

                cout << endl;
            }
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));

    grafo.ExibeMatrizAdjacencias();
    grafo.ExibeListaAdjacencias();


    return 0;
}