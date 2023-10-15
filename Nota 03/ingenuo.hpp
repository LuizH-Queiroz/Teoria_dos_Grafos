#ifndef INGENUO_HPP
#define INGENUO_HPP


#include "grafo_simples.hpp"
#include <vector>


class Ingenuo {
    public:
        static std::vector<int> vertices;


        /**
         * Cria o vetor de vértices que será usado no método CorteMinimo
        */
        static void DefineVertices(int);


        /**
         * Encontra um numero de arestas que forma um corte de arestas no grafo recebido.
         * Vale ressaltar que o valor da quantidade de arestas retornado pode não ser
         * o corte mínimo
        */
        static int CorteMinimo(GrafoSimples&);
};


#endif