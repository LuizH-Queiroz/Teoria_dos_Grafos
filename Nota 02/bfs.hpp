#ifndef BFS_HPP
#define BFS_HPP


#include <vector>
#include <string>
#include "grafo_simples.hpp"



class BFS {
    public:
        /**
         * Definição de tipo que será usado na coloração das
         * arestas
        */
        enum COR_ARESTA {
            AZUL,      // Aresta que liga um "pai" ao seu "filho"

            VERMELHO,  // Aresta que liga dois vértices "irmãos", ou seja, vértices que estão
                       // no mesmo nível e têm o mesmo "pai"

            VERDE,     // Conecta um "tio" ao seu "sobrinho", ou seja, vértices de níveis
                       // diferentes que não estão no mesmo ramo da árvore gerada na busca

            AMARELO,   // Vértices são primos, ou seja, estão no mesmo nível mas em
                       // ramos diferentes da árvore gerada na busca

            NAO_EXISTE // Aresta não existe
        };


        /***************************************************************/
        /*                           Métodos                           */
        /***************************************************************/


        /**
         * Realiza a Busca em Largura em todos os vértices do grafo recebido como parâmetro.
         * O grafo terá seus valores de raio, diâmetro e distância média alterados pelo
         * método; que também chamará o método "CriaArquivoGDF" para gerar o arquivo de
         * output.
        */
        static void BuscaLargura(GrafoSimples&, std::string);

        /**
         * Calcula a distância entre todos os pares de vértices do grafo, atualizando seus
         * valores de raio, diâmetro e distância média
        */
        static void CalculaDistancias(GrafoSimples&);

        /**
         * Realiza Busca em Largura para colorir as arestas do grafo e, então
         * criar o arquivo GDF chamando o método CriaArquivoGDF()
        */
        static void ColorirArestas(GrafoSimples&, std::string);

        static void CriaArquivoGDF(std::vector<std::vector<BFS::COR_ARESTA>>&, std::string);

        static std::string TextoCor(BFS::COR_ARESTA);
};



#endif