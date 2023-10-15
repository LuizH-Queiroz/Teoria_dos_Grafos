#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <vector>



class UnionFind {
    private:
        std::vector<int> parent;


    public:

        /****************************************************************/
        /*                         Construtores                         */
        /****************************************************************/


        /**
         * O vetor de conjuntos começa vazio
        */
        UnionFind();


        /**
         * O vetor de conjuntos começa com o tamanho fornacido
        */
        UnionFind(int);


        /****************************************************************/
        /*                           Métodos                            */
        /****************************************************************/


        /**
         * Encontra o conjunto ao qual o inteiro pertence
        */
        int Find(int);


        /**
         * Inicializa um vetor de tamanho n.
         * Sendo assim, os conjuntos estarão no intervalo [0, n-1]
        */
        void Initialize(int);


        /**
         * Une os conjuntos recebidos como parâmetros
        */
        void Union(int, int);
};



#endif