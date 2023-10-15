#include "grafo_simples.hpp"


/**
 * Cria a matriz e lista de adjacências de um grafo simples a partir de um arquivo de texto
 * com formato/organização pré-definido
*/
bool GrafoSimples::LerArquivo(std::string nomeArquivo) {
    std::ifstream arquivoLeitura(nomeArquivo);

    // Testa se a abertura do arquivo foi bem-sucedida            
    if (!arquivoLeitura.is_open())
        return false;
    

    /* Leitura do arquivo e atribuição dos valores à Matriz e à Lista de Adjacências */            
    int n_vertices;
    int tem_ligacao; // 1 - Se há ligação entre os vértives "i" e "j"
                        // 0 - Se não há ligação entre os vértices "i" e "j"

    arquivoLeitura >> n_vertices;
    matriz = std::vector<std::vector<int>>(n_vertices, std::vector<int>(n_vertices)); // Mudando a matriz para o tamanho
                                                                                      // n_vertices X n_vertices
    lista = std::vector<std::vector<int>>(n_vertices); // Há n_vertices linhas, mas nenhuma coluna (no momento,
                                                // nenhum vértice possui ligação)

    qtdArestas = 0; // Inicialmente, nenhuma aresta foi contada
    for (int i = 0; i < n_vertices; i++)
    {
        for (int j = 0; j < n_vertices; j++)
        {
            arquivoLeitura >> tem_ligacao;

            matriz[i][j] = tem_ligacao;
            if (tem_ligacao)
            {
                lista[i].push_back(j);
                qtdArestas++;
            }
        }
    }
    qtdArestas /= 2; // Como cada aresta foi contada duas vezes, devemos dividir pela metade
                     // o valor de "qtdArestas"


    // Criação do grafo foi bem-sucedida
    return true;
}


/**
 * Retorna a quantidade de arestas do grafo
*/
int GrafoSimples::QuantidadeArestas() {
    return qtdArestas;
}


/**
 * Retorna a quantidade de vértices do grafo
*/
int GrafoSimples::QuantidadeVertices() {
    return matriz.size();
}