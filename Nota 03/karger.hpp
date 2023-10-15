#ifndef KARGER_HPP
#define KARGER_HPP

#include <vector>
#include "grafo_simples.hpp"



class Karger {
    public:
        // Vetor de arestas do grafo recebido como parametro
        static std::vector<std::vector<int>> arestas;
        static std::vector<int> ordemEscolha;
        static int indiceEscolha;
    

        /************************************************************/
        /*                     Métodos Privados                     */
        /************************************************************/


        /**
         * Cria a lista de arestas
        */
        static void CriaListaArestas(GrafoSimples&);


        /**
         * Retorna o índice da próxima aresta
        */
        static int ProximaAresta();


        /**
         * Randomiza a lista de arestas
        */
        static void RandomizaListaArestas();


        /**
         * Encontra um numero de arestas que forma um corte de arestas no grafo recebido.
         * Vale ressaltar que o valor da quantidade de arestas retornado pode não ser
         * o corte mínimo
        */
        static int CorteArestas(GrafoSimples&);
};


#endif