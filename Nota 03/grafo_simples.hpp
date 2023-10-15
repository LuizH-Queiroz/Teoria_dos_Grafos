#ifndef GRAFO_SIMPLES_HPP
#define GRAFO_SIMPLES_HPP

#include <vector>
#include <string>
#include <fstream>


class GrafoSimples {
    public:
        std::vector<std::vector<int>> matriz;
        std::vector<std::vector<int>> lista;
        int qtdArestas;

        /**
         * Cria a matriz e lista de adjacências de um grafo simples a partir de um arquivo de texto
         * com formato/organização pré-definido
        */
        bool LerArquivo(std::string);

        /**
         * Retorna a quantidade de arestas do grafo
        */
        int QuantidadeArestas();

        /**
         * Retorna a quantidade de vértices do grafo
        */
        int QuantidadeVertices();
};


#endif