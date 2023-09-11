#include "dfs.hpp"
#include <iostream>
#include <functional>
#include <fstream>



/**
 * Realiza a busca em profundidade no grafo, gerando o arquivo de saída
 * no formato GDF
*/
void DFS::BuscaProfundidade(GrafoSimples grafo, std::string arquivo) {
    std::vector<int> profund_entrada(grafo.QuantidadeVertices(), 0);
    std::vector<int> profund_saida(grafo.QuantidadeVertices(), 0);
    int contador_global = 0;

    // Inicializando a matriz de cores.
    // Todas as arestas começam marcados como NAO_EXISTE, mas se existirem elas serão
    // incluídas no algoritmo dfs
    std::vector<std::vector<DFS::COR_ARESTA>> matrizCores = std::vector<std::vector<DFS::COR_ARESTA>>(
        grafo.QuantidadeVertices(),
        std::vector<DFS::COR_ARESTA>(grafo.QuantidadeVertices(), DFS::COR_ARESTA::NAO_EXISTE)
    );


    // Função que realiza a busca em largura, colorindo as arestas
    // e definindo os valores de profundidade de entrada e de saída
    std::function<void(int, int)> dfs;
    dfs = [&](int vertice, int pai) {
        // Atualizando o valor da profundidade de entrada do vértice
        contador_global++;
        profund_entrada[vertice] = contador_global;

        /*******************************************/

        for (int vizinho : grafo.lista[vertice])
        {
            // Arestas azuis são aquelas pertencentes à árvore gerada pela
            // Busca em Profundidade
            if (profund_entrada[vizinho] == 0)
            {
                matrizCores[vertice][vizinho] = DFS::COR_ARESTA::AZUL;
                matrizCores[vizinho][vertice] = DFS::COR_ARESTA::AZUL;
                dfs(vizinho, vertice);
            }
            // Arestas de retorno são aquelas em que um vértice, na Busca em Profundidade,
            // olha para um dos seus antecessores que não é seu pai
            else if (profund_saida[vizinho] == 0 && vizinho != pai)
            {
                matrizCores[vertice][vizinho] = DFS::COR_ARESTA::VERMELHO;
                matrizCores[vizinho][vertice] = DFS::COR_ARESTA::VERMELHO;
            }
        }

        /*******************************************/

        // Saindo do vértice
        contador_global++;
        profund_saida[vertice] = contador_global;
    };

    // Realização da Busca em Profundidade
    dfs(0, 0);

    // Criação do arquivo de output e limpeza de matrizCores
    CriaArquivoGDF(matrizCores, arquivo);
    matrizCores.clear();
}


void DFS::CriaArquivoGDF(std::vector<std::vector<DFS::COR_ARESTA>>& matrizCores, std::string arquivo) {
    std::ofstream gdf(arquivo);
    if (!gdf.is_open())
    {
        std::cout << ">>>> Erro ao abrir arquivo de output GDF (DFS)!" << std::endl;
        exit(EXIT_FAILURE);
    }

    /**
     * Parte inicial do arquivo .gdf, quase fixa
    */
    gdf << "nodedef>name VARCHAR,label VARCHAR" << std::endl;
    for (int i = 0; i < matrizCores.size(); i++)
    {
        gdf << (i+1) << "," << (i+1) << std::endl;
    }
    gdf << "edgedef>node1 VARCHAR,node2 VARCHAR,directed BOOLEAN,color VARCHAR" << std::endl;

    /**
     * Parte do arquivo .gdf referente às arestas e suas colorações
    */
    for (int i = 0; i < matrizCores.size(); i++)
    {
        for (int j = i+1; j < matrizCores.size(); j++)
        {
            if (matrizCores[i][j] != DFS::COR_ARESTA::NAO_EXISTE)
            {
                gdf << (i+1) << "," << (j+1) << ",false," << TextoCor(matrizCores[i][j]) << std::endl;
            }
        }
    }
}


/**
 * Mostra a tabela de entrada e saída do grafo
*/
void DFS::PrintTabelaES(GrafoSimples grafo, std::vector<int>& profund_entrada, std::vector<int>& profund_saida) {
    for (int i = 0; i < grafo.QuantidadeVertices(); i++)
        std::cout << i+1 << "\t";
    std::cout << std::endl;

    for (int i = 0; i < profund_entrada.size(); i++)
        std::cout << profund_entrada[i] << "\t";
    std::cout << std::endl;

    for (int i = 0; i < profund_saida.size(); i++)
        std::cout << profund_saida[i] << "\t";
    std::cout << std::endl;
}


std::string DFS::TextoCor(DFS::COR_ARESTA cor) {
    std::string texto;

    switch(cor) {
        case DFS::COR_ARESTA::AZUL:
            texto = "\'0,0,255\'";
            break;

        case DFS::COR_ARESTA::VERMELHO:
            texto = "\'255,0,0\'";
            break;

        case DFS::COR_ARESTA::NAO_EXISTE:
            texto = "\'0,0,0\'";
            break;
    }

    return texto;
}