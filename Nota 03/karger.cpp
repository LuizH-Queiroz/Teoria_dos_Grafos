#include "karger.hpp"
#include "union_find.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>


std::vector<std::vector<int>> Karger::arestas;
std::vector<int> Karger::ordemEscolha;
int Karger::indiceEscolha = 0;


/**
 * Cria a lista de arestas
*/
void Karger::CriaListaArestas(GrafoSimples& grafo) {
    arestas.resize(grafo.QuantidadeArestas(), std::vector<int>(2));
    int indice = 0;

    for (int i = 0; i < grafo.lista.size(); i++)
    {
        for (int j = 0; j < grafo.lista[i].size(); j++)
        {
            if (i < grafo.lista[i][j])
            {                
                arestas[indice][0] = i;
                arestas[indice][1] = grafo.lista[i][j];
                indice++;
            }
        }
    }

    ordemEscolha.resize(grafo.QuantidadeArestas());
    for (int i = 0; i < ordemEscolha.size(); i++)
    {
        ordemEscolha[i] = i;
    }
}


/**
 * Retorna o índice da próxima aresta
*/
int Karger::ProximaAresta() {
    if (indiceEscolha == ordemEscolha.size())
        return -1;

    indiceEscolha++;
    return ordemEscolha[indiceEscolha-1];
}


/**
 * Randomiza a lista de arestas
*/
// void Karger::RandomizaListaArestas() {
//     int qtdTrocas = 2 * arestas.size();
//     int indice1;
//     int indice2;
//     int temp;

//     for (int i = 0; i < qtdTrocas; i++)
//     {
//         indice1 = rand() % arestas.size();
//         indice2 = rand() % arestas.size();

//         temp = ordemEscolha[indice1];
//         ordemEscolha[indice1] = ordemEscolha[indice2];
//         ordemEscolha[indice2] = temp;
//     }

//     indiceEscolha = 0;
// }


/**
 * Encontra um numero de arestas que forma um corte de arestas no grafo recebido.
 * Vale ressaltar que o valor da quantidade de arestas retornado pode não ser
 * o corte mínimo
*/
int Karger::CorteArestas(GrafoSimples& grafo) {
    // Procedimentos necessários para se realizar o algoritmo de Karger
    // RandomizaListaArestas();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(ordemEscolha.begin(), ordemEscolha.end(), std::default_random_engine(seed));
    indiceEscolha = 0;

    // Variáveis do algoritmo
    UnionFind vertices(grafo.QuantidadeVertices());
    int qtdJuncoes = grafo.QuantidadeVertices()-2;
    int indiceAresta;

    for (int i = 0; i < qtdJuncoes; i++)
    {
        // Enquanto os vértices da aresta escolhida forem iguais (já tiverem sido juntados/unidos),
        // escolha uma nova aresta
        indiceAresta = ProximaAresta();
        while (vertices.Find(arestas[indiceAresta][0]) == vertices.Find(arestas[indiceAresta][1]))
        {
            indiceAresta = ProximaAresta();
        }

        // Junte os vértices diferentes em um só
        vertices.Union(arestas[indiceAresta][0], arestas[indiceAresta][1]);
    }


    // O número de arestas para este corte é a quantidade de arestas que ainda
    // não foram escolhidas e que não conectam vértices que estão no mesmo
    // "supervértice"
    int corte = 0;
    while((indiceAresta = ProximaAresta()) != -1)
    {
        if (vertices.Find(arestas[indiceAresta][0]) != vertices.Find(arestas[indiceAresta][1]))
        {
            // std::cout << "Aresta " << (corte+1) << ": "
            //     << arestas[indiceAresta][0] << " " << arestas[indiceAresta][1] << std::endl;
            corte++;
        }
    }

    return corte;
}