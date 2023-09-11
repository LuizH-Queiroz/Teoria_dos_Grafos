#include <iostream>
#include <functional>
#include <vector>
#include <fstream>
#include "grafo_simples.hpp"
#include "bfs.hpp"
#include "dfs.hpp"

#define PASTA_INPUT string("Grafos/")
#define MINHA_PASTA_OUT string("out_meu/")
#define PROF_PASTA_OUT string("out_prof/")

#define QTD_GRAFOS 20

using namespace std;


bool ArquivosIguais(string arq1, string arq2) {
    ifstream out1(arq1);
    ifstream out2(arq2);
    char c1;
    char c2;


    while(true)
    {
        out1.get(c1);
        out2.get(c2);
        if (out1.eof() || out2.eof())
            break;
        else if (c1 != c2)
            return false;
    }

    return (out1.eof() && out2.eof());
}




/*************************************************************/
/*                        Função Main                        */
/*************************************************************/
int main() {
    GrafoSimples grafo;
    string arquivo;
    string grafoStr;
    bool encontrouDiff = false;

    for (int i = 1; i <= QTD_GRAFOS; i++)
    {
        grafoStr = "graph_" + to_string(i);
        if (!grafo.LerArquivo(string(PASTA_INPUT) + grafoStr))
        {
            cout << ">>>> Erro ao abrir arquivo de numero " << i << "!!" << endl;
            exit(EXIT_FAILURE);
        }

        cout << "Dados do grafo " << i << ":" << endl;

        // Criando e comparando os arquivos de BFS
        arquivo = grafoStr + "_bfs.gdf";
        BFS::BuscaLargura(grafo, MINHA_PASTA_OUT + arquivo);
        if (!ArquivosIguais(MINHA_PASTA_OUT + arquivo, PROF_PASTA_OUT + arquivo))
        {
            cout << ">>>> Diferenca encontrada no arquivo " << i << " (BFS)!!" << endl;
            encontrouDiff = true;
        }


        // Criando e comparando os arquivos de DFS
        arquivo = grafoStr + "_dfs.gdf";
        DFS::BuscaProfundidade(grafo, MINHA_PASTA_OUT + arquivo);
        if (!ArquivosIguais(MINHA_PASTA_OUT + arquivo, PROF_PASTA_OUT + arquivo))
        {
            cout << ">>>> Diferenca encontrada no arquivo " << i << " (DFS)!!" << endl;
            encontrouDiff = true;
        }

        // Informando o raio, diâmetro e distância média do grafo
        cout << "Diametro = " << grafo.diametro << endl;
        cout << "Raio = " << grafo.raio << endl;
        cout << "Distancia Media = " << grafo.distMedia << endl;
        cout << endl;
    }

    if (!encontrouDiff)
    {
        cout << "Todos os arquivos de output sao compativeis!" << endl;
    }


    return 0;
}