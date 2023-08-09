/*
Uma sequência de k vértices v1,v2,...,vk é um passeio em G se, para todo 1≤i≤k−1, vale que vi e vi+1 são vizinhos.
Isso equivale a dizer que vértices adjacentes na sequência devem ser vizinhos.
Não há outra restrição a ser considerada na definição de passeio, sendo possível, por exemplo,
repetir vértices e arestas. Um exemplo de passeio no grafo da Figura 1 é 1,2,3,4,3,6.

Escreva uma função que determine se uma sequência de vértices constitui um passeio em G.
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
         * Retorna verdadeiro se o conjunto de vértices formar um passei no grafo.
         * Retorna falso caso contrário.
        */
        bool EhPasseio(vector<int>& vertices) {
            // Se não há nenhum vértice não tem como ser um passeio
            if (vertices.size() == 0)
                return false;

            // Se o conjunto de vértices tiver tamanho um, ele não será verificado
            // no laço "for" a seguir, então sua validade é verificada mais cedo
            if (!VerticeValido(vertices[0]))
                return false;
            

            // Verifica a validade dos vértices e arestas no passeio
            for (int i = 0; i < vertices.size()-1; i++)
            {
                if (!VerticeValido(vertices[i]) || !VerticeValido(vertices[i+1]))
                    return false;
                if (matriz[vertices[i]][vertices[i+1]] == 0)
                    return false;
            }

            // Se todos os vértices e arestas são válidos, então o passeio é válido
            return true;
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));

    vector<int> verticesPasseio = {0, 1, 2, 3, 0, 2, 5};

    if (grafo.EhPasseio(verticesPasseio))
    {
        cout << "O conjunto de vertices eh um passeio!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um passeio!" << endl;
    }


    return 0;
}