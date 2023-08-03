/*
Escreva uma função que que determine se dois vértices distintos u e v são vizinhos (ou adjacentes).
Lembrando que eles são vizinhos se a aresta entre eles existir, ou seja, se (u,v)∈E.
Em caso afirmativo, diz-se que u e v são os extremos de tal aresta.
*/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>

#define ARQUIVO "Grafos/01.txt"
#define TESTES_VIZINHANCA 3


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
         * Verifica se dois vértices "u" e "v" são vizinhos.
         * Se um (ou ambos) dos vértices for inválido, o resultado será "false"
        */
        bool VerticesVizinhos(int u, int v) {
            if (!VerticeValido(u) || !VerticeValido(v))
                return false;
            
            return matriz[u][v];
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(ARQUIVO);

    srand(time(NULL));
    for (int i = 0; i < TESTES_VIZINHANCA; i++)
    {
        int v1 = rand() % grafo.QuantidadeVertices();
        int v2 = rand() % grafo.QuantidadeVertices();
        
        if (grafo.VerticesVizinhos(v1, v2))
        {
            cout << "Os vertices " << v1 << " e " << v2 << " sao vizinhos!" << endl;
        }
        else
        {
            cout << "Os vertices " << v1 << " e " << v2 << " NAO sao vizinhos!" << endl;
        }
    }


    return 0;
}