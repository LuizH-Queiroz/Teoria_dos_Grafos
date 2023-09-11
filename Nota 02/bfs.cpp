#include "bfs.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
#include <queue>


/**
 * Realiza a Busca em Largura em todos os vértices do grafo recebido como parâmetro.
 * O grafo terá seus valores de raio, diâmetro e distância média alterados pelo
 * método; que também chamará o método "CriaArquivoGDF" para gerar o arquivo de
 * output.
*/
void BFS::BuscaLargura(GrafoSimples& grafo, std::string arquivo) {
    ColorirArestas(grafo, arquivo);
    CalculaDistancias(grafo);
}


/**
 * Calcula a distância entre todos os pares de vértices do grafo, atualizando seus
 * valores de raio, diâmetro e distância média
*/
void BFS::CalculaDistancias(GrafoSimples& grafo) {
    // Vector para informar o nível do vértice (-1 se ainda não tiver sido visitado)
    std::vector<int> nivelVertice(grafo.QuantidadeVertices());

    // Fila auxiliar para a realização da Busca em Largura
    std::queue<int> q;

    // Variáveis para armazenar os valores que serão atualizados no grafo ao final do método
    int raio = grafo.QuantidadeVertices();
    int diametro = 0;
    int somaDistancias = 0; // Somatório de todas as distâncias mínimas.
                            // Vale ressaltar que ao final seu valor, na verdade
                            // será o dobro da soma das distâncias mínimas, já que
                            // contará cada distância duas vezes

    int tempExcentricidade; // Armazena a excentricidade do vértice inicial da
                            // Busca em Largura mais recente


    // Realiza a busca em largura em cada um dos N vértices do grafo
    for (int i = 0; i < grafo.QuantidadeVertices(); i++)
    {
        // Inicialmente, o vértice tem excentricidade 0, mas pode
        // aumentar ao longo da busca
        tempExcentricidade = 0;
        
        // No início da busca nenhum vértice foi nivelVertice (com exceção do primeiro)        
        std::fill(nivelVertice.begin(), nivelVertice.end(), -1);

        // O vértice "i" será o vértice inicial desta vez
        q.push(i);
        nivelVertice[i] = 0;


        while(!q.empty())
        {
            for (int vizinho : grafo.lista[q.front()])
            {
                if (nivelVertice[vizinho] == -1)
                {
                    q.push(vizinho);
                    nivelVertice[vizinho] = nivelVertice[q.front()] + 1;

                    // Atualização dos valores
                    tempExcentricidade = std::max(tempExcentricidade, nivelVertice[vizinho]);
                    diametro = std::max(diametro, tempExcentricidade);
                    somaDistancias += nivelVertice[vizinho];
                }
            }

            q.pop();
        }

        raio = std::min(raio, tempExcentricidade);
    }


    grafo.raio = raio;
    grafo.diametro = diametro;
    grafo.distMedia = ((float) somaDistancias/2) / (grafo.QuantidadeVertices() * (grafo.QuantidadeVertices()-1)/2);
}


/**
 * Realiza Busca em Largura para colorir as arestas do grafo e, então
 * criar o arquivo GDF chamando o método CriaArquivoGDF()
*/
void BFS::ColorirArestas(GrafoSimples& grafo, std::string arquivo) {
    // Fila usada para armazenar os vértices na ordem em que devem ser visitados
    std::queue<int> q;

    // Inicializando matrizCores e nivelVertice.
    // Note que, inicialmente, é considerado que não há nenhuma aresta e que os vértices
    // estão todos no nível -1, mas as arestas serão coloridas no decorrer do algoritmo
    // e o nível -1 serve para indicar que o vértice ainda não foi visitado
    std::vector<std::vector<BFS::COR_ARESTA>> matrizCores = std::vector<std::vector<BFS::COR_ARESTA>>(
        grafo.QuantidadeVertices(),
        std::vector<BFS::COR_ARESTA>(grafo.QuantidadeVertices(), BFS::COR_ARESTA::NAO_EXISTE)
    );
    std::vector<int> nivelVertice = std::vector<int>(grafo.QuantidadeVertices(), -1);
    std::vector<int> paiVertice = std::vector<int>(grafo.QuantidadeVertices(), -1);


    // O primeiro vértice é o único que pertence ao nível 0 e que não tem "pai"
    // (não foi descoberto por nenhum vértice)
    nivelVertice[0] = 0;
    q.push(0);
    while(!q.empty())
    {
        // Itera por todos os vizinhos do vértice atual (q.front())
        for (int vizinho : grafo.lista[q.front()])
        {
            // Não há o que fazer se o vértice vizinho for o pai do atual
            if (vizinho == paiVertice[q.front()])
                continue;

            // Neste caso, o vértice descobriu outro
            if (nivelVertice[vizinho] == -1)
            {
                q.push(vizinho);
                nivelVertice[vizinho] = nivelVertice[q.front()] + 1;
                paiVertice[vizinho] = q.front();

                // Colorindo a aresta
                matrizCores[q.front()][vizinho] = BFS::COR_ARESTA::AZUL;
                matrizCores[vizinho][q.front()] = BFS::COR_ARESTA::AZUL;
            }
            // Vértices que estão em níveis diferentes mas que um não descobriu o outro
            else if (nivelVertice[q.front()] != nivelVertice[vizinho])
            {
                matrizCores[q.front()][vizinho] = BFS::COR_ARESTA::VERDE;
                matrizCores[vizinho][q.front()] = BFS::COR_ARESTA::VERDE;
            }
            // Se estão no mesmo nível, basta saber se são irmãos ou não
            else if (paiVertice[q.front()] == paiVertice[vizinho])
            {
                matrizCores[q.front()][vizinho] = BFS::COR_ARESTA::VERMELHO;
                matrizCores[vizinho][q.front()] = BFS::COR_ARESTA::VERMELHO;
            }
            // Os vértices são primos
            else
            {
                matrizCores[q.front()][vizinho] = BFS::COR_ARESTA::AMARELO;
                matrizCores[vizinho][q.front()] = BFS::COR_ARESTA::AMARELO;
            }
        }

        // Terminamos de analisar o vértice da frente da fila
        q.pop();
    }


    // Criando o arquivo de output .gdf e limpando as estruturas de dados
    // da classe BFS
    CriaArquivoGDF(matrizCores, arquivo);
    matrizCores.clear();
    nivelVertice.clear();
}


void BFS::CriaArquivoGDF(std::vector<std::vector<BFS::COR_ARESTA>>& matrizCores, std::string arquivo) {
    std::ofstream gdf(arquivo);
    if (!gdf.is_open())
    {
        std::cout << ">>>> Erro ao abrir arquivo de output GDF (BFS)!" << std::endl;
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
            if (matrizCores[i][j] != BFS::COR_ARESTA::NAO_EXISTE)
            {
                gdf << (i+1) << "," << (j+1) << ",false," << TextoCor(matrizCores[i][j]) << std::endl;
            }
        }
    }
}


std::string BFS::TextoCor(BFS::COR_ARESTA cor) {
    std::string texto;

    switch(cor) {
        case BFS::COR_ARESTA::AZUL:
            texto = "\'0,0,255\'";
            break;

        case BFS::COR_ARESTA::VERMELHO:
            texto = "\'255,0,0\'";
            break;
        
        case BFS::COR_ARESTA::VERDE:
            texto = "\'0,255,0\'";
            break;
        
        case BFS::COR_ARESTA::AMARELO:
            texto = "\'255,255,0\'";
            break;

        case BFS::COR_ARESTA::NAO_EXISTE:
            texto = "\'0,0,0\'";
            break;
    }

    return texto;
}