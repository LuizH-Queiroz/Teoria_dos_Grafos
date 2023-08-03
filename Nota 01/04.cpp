/*
Escreva uma função que determine o grau e as vizinhanças aberta e fechada de um vértice v.
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
         * Retorna o valor do grau do vértice "v".
         * Se o vértice for inválido, retorna -1
        */
        int GrauVertice(int v) {
            if (!VerticeValido(v))
                return -1;

            return lista[v].size();
        }


        /**
         * Exibe a vizinhança aberta de um determinado vértice "v"
        */
        void ExibeVizinhancaAberta(int v) {
            if (!VerticeValido(v))
            {
                cout << "O vertice " << v << " eh invalido!" << endl;
                return;
            }


            cout << "Vizinhanca aberta do vertice " << v << ": ";
            for (int i = 0; i < lista[v].size(); i++)
            {
                cout << lista[v][i];
                if (i < (lista[v].size() - 1))
                    cout << ", ";
            }
            cout << endl;
        }


        /**
         * Exibe a vizinhança fechada de um determinado vértice "v"
        */
        void ExibeVizinhancaFechada(int v) {
            if (!VerticeValido(v))
            {
                cout << "O vertice " << v << " eh invalido!" << endl;
                return;
            }


            cout << "Vizinhanca fechada do vertice " << v << ": ";
            for (int i = 0; i < lista[v].size(); i++)
            {
                cout << lista[v][i] << ", ";
            }
            cout << v << endl;
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));


    for (int i = 0; grafo.VerticeValido(i); i++)
    {
        cout << endl;
        cout << "Grau do vertice " << i << ": " << grafo.GrauVertice(i) << endl;
        grafo.ExibeVizinhancaAberta(i);
        grafo.ExibeVizinhancaFechada(i);
    }


    return 0;
}