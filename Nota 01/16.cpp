/*
Um clique  S⊆V  é dito maximal se não houver outro clique  S′  tal que  S′⊇S . Isto é, se não for possível expandir
o conjunto  S  através da inserção de um ou mais vértices de modo que o conjunto resultante ainda seja um clique.
Os seguintes conjuntos são exemplos de cliques maximais do grafo da Figura 1:  {1,2,3,4},{5,6,7} .
Observe que o conjunto  {1,2,3} , apesar de ser clique, não é maximal pois ele poderia ser estendido através
da adição do vértice 4.

Escreva uma função que determine se um dado conjunto de vértices constitui um clique maximal de  G .
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
         * Retorna verdadeiro se o conjunto de vértices formar um clique.
         * Retorna falso caso contrário.
        */
        bool EhClique(vector<int>& vertices) {
            // Não tem como ser um clique se não há nenhum vértice
            if (vertices.size() == 0)
                return false;
            

            // Verifica se todos os vértices são válidos
            for (int i = 0; i < vertices.size(); i++)
            {
                if (!VerticeValido(vertices[i]))
                    return false;
            }


            // Verifica se o conjunto de vértices tem todas as ligações necessárias para
            // formar um clique
            for (int i = 0; i < vertices.size()-1; i++)
            {
                for (int j = i+1; j < vertices.size(); j++)
                {
                    if (matriz[vertices[i]][vertices[j]] == 0)
                        return false;
                }
            }

            // Se todos os vértices são válidos e todas as arestas necessárias existem,
            // então o conjunto é um clique 
            return true;
        }


        /**
         * Retorna verdadeiro se o conjunto de vértices formar um clique maximal.
         * Retorna falso caso contrário.
        */
        bool EhCliqueMaximal(vector<int>& vertices) {
            // Não tem como ser um clique maximal se não é um clique
            if (!EhClique(vertices))
                return false;
            

            // Nesse vector, para cada vértice V, ligacoes[V] indica quantos vértices
            // do clique recebido como parâmetro apontam para V
            vector<int> ligacoes(QuantidadeVertices(), 0); // Todos os valores começam em 0

            // Percorre a lista de adjacências de todos os vértices recebidos e incrementa
            // o contador de ligações (vector ligacoes).
            // Se algum vértice atingir "vertices.size()" ligações, então há pelo menos
            // um vértice que poderia ser adicionado ao conjunto de forma que continuaria
            // sendo um clique, já que esse vértice teria ligações com todos os outros
            for (int i = 0; i < vertices.size(); i++)
            {
                for (int j = 0; j < lista[i].size(); j++)
                {
                    ligacoes[ lista[i][j] ]++;
                    
                    // Se for verdadeira a condição abaixo, então há um vértice que poderia
                    // ser adicionado ao conjunto e, portanto, o clique não é maximal
                    if (ligacoes[ lista[i][j] ] == vertices.size())
                        return false;
                }
            }

            // Como não há nenhum vértice que possa ser incluído, o clique é maximal
            return true;
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    grafo.LerArquivo(string(ARQUIVO));

    vector<int> verticesCliqueMaximal = {2, 0, 1, 3};

    if (grafo.EhCliqueMaximal(verticesCliqueMaximal))
    {
        cout << "O conjunto de vertices eh um Clique Maximal!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um Clique Maximal!" << endl;
    }


    return 0;
}