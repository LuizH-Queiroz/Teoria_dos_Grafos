#include "ingenuo.hpp"
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>
#include <iostream>


std::vector<int> Ingenuo::vertices;


/**
 * Cria o vetor de vértices que será usado no método CorteMinimo
*/
void Ingenuo::DefineVertices(int numVertices) {
    vertices.resize(numVertices);

    for (int i = 0; i < numVertices; i++)
    {
        vertices[i] = i;
    }
}


/**
 * Encontra um numero de arestas que forma um corte de arestas no grafo recebido.
 * Vale ressaltar que o valor da quantidade de arestas retornado pode não ser
 * o corte mínimo
*/
int Ingenuo::CorteMinimo(GrafoSimples& grafo) {
    // Randomizando a lista de vértices
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(vertices.begin(), vertices.end(), std::default_random_engine(seed));

    // for (int i = 0; i < vertices.size(); i++)
    // {
    //     std::cout << vertices[i] << " ";
    // }
    // std::cout << std::endl;

    int inicioConjunto1 = 0;
    int inicioConjunto2 = 1 + (rand() % (vertices.size()-1));
    //std::cout << "inicioConjunto2 = " << inicioConjunto2 << std::endl;

    int corte = 0;
    for (int i = inicioConjunto1; i < inicioConjunto2; i++)
    {
        for (int j = inicioConjunto2; j < vertices.size(); j++)
        {
            if (grafo.matriz[vertices[i]][vertices[j]])
            {
                corte++;
            }
        }
    }

    return corte;
}