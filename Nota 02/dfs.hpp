#ifndef DFS_HPP
#define DFS_HPP

#include <vector>
#include <string>
#include "grafo_simples.hpp"



class DFS {
    public:
        /**
         * Definição de tipo que será usado na coloração das
         * arestas
        */
        enum COR_ARESTA {
            AZUL,      // Aresta que liga um "pai" ao seu "filho"
            VERMELHO,  // Aresta de retorno
            NAO_EXISTE // Aresta não existe
        };
 
 
        /**
         * Realiza a busca em profundidade no grafo, gerando o arquivo de saída
         * no formato GDF
        */
        static void BuscaProfundidade(GrafoSimples, std::string);

        static void CriaArquivoGDF(std::vector<std::vector<DFS::COR_ARESTA>>&, std::string);

        /**
         * Mostra a tabela de entrada e saída do grafo
        */
        static void PrintTabelaES(GrafoSimples, std::vector<int>&, std::vector<int>&);

        static std::string TextoCor(DFS::COR_ARESTA);
};


#endif