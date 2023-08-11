#include <iostream>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>

#define ARQUIVO "Grafos/01.txt"
#define TESTES_VIZINHANCA 3


using namespace std;


/******************************/
/* Classe de um Grafo Simples */
/******************************/

class GrafoSimples {
    private:

        vector<vector<int>> matriz; // Matriz de Adjacências
        vector<vector<int>> lista; // Lista de Adjacências
    

    public:


        /********************* Exercício 01 *********************/
        /*
        Faça um código que leia o grafo de um arquivo e o represente nas duas formas vistas em sala: matriz de adjacências e lista de adjacências.
        Nas próximas questões, leve em conta que as duas representações do grafo estarão disponı́veis para tornar as implementações mais eficientes. 
        */
        /********************************************************/


        /**
         * Cria a matriz e lista de adjacências de um grafo simples a partir de um arquivo de texto
         * com formato/organização pré-definido
        */
        bool LerArquivo(string nomeArquivo) {
            ifstream arquivoLeitura(nomeArquivo);

            // Testa se a abertura do arquivo foi bem-sucedida            
            if (!arquivoLeitura.is_open())
                return false;
            

            /* Leitura do arquivo e atribuição dos valores à Matriz e à Lista de Adjacências */            
            int n_vertices;
            int tem_ligacao; // 1 - Se há ligação entre os vértives "i" e "j"
                             // 0 - Se não há ligação entre os vértices "i" e "j"

            arquivoLeitura >> n_vertices;
            matriz = vector<vector<int>>(n_vertices, vector<int>(n_vertices)); // Mudando a matriz para o tamanho
                                                                               // n_vertices X n_vertices
            lista = vector<vector<int>>(n_vertices); // Há n_vertices linhas, mas nenhuma coluna (no momento,
                                                     // nenhum vértice possui ligação)

            for (int i = 0; i < n_vertices; i++)
            {
                for (int j = 0; j < n_vertices; j++)
                {
                    arquivoLeitura >> tem_ligacao;

                    matriz[i][j] = tem_ligacao;
                    if (tem_ligacao)
                        lista[i].push_back(j);
                }
            }

            // Criação do grafo foi bem-sucedida
            return true;
        }


        /**
         * Exiba a Matriz de Adjacências do grafo
        */
        void ExibeMatrizAdjacencias() {

                cout << endl;
                cout << "Matriz de Adjacencias:" << endl;

                for (int i = 0; i < matriz.size(); i++)
                {
                    for (int j = 0; j < matriz.size(); j++)
                    {
                        cout << matriz[i][j]  << " ";
                    }
                    cout << endl;
                }
        }


        /**
         * Exibe a Lista de Adjacências do grafo
        */
        void ExibeListaAdjacencias() {

            cout << endl;
            cout << "Lista de Adjacencias:" << endl;

            for (int i = 0; i < lista.size(); i++)
            {
                cout << i << ": ";
                for (int j = 0; j < lista[i].size(); j++)
                {
                    cout << lista[i][j];
                    if (j < (lista[i].size()-1))
                        cout << ", ";
                }

                cout << endl;
            }
        }


        /********************* Exercício 02 *********************/
        /*
        Escreva uma função que calcule os graus mínimo δ(G) e máximo Δ(G) de G. Para o grafo da Figura 1, temos que δ(G)=2 e Δ(G)=5.
        */
        /********************************************************/


        /**
         * Retorna o Grau Mínimo do grafo
        */
        int GrauMinimo() {
            // Não houver nenhum vértice (o grafo é vazio) não há um grau mínimo
            if (lista.size() == 0)
                return -1;

            // Como o grafo é simples, temos a certeza que nenhum vértice terá número de ligações igual ao número
            // de vértices, pois para isso seria necessário a ocorrência de um laço ou aresta paralela.
            // Sendo assim, com certeza a variável "minimo" terá o real valor mínimo ao final do laço "for"
            int minimo = lista.size();
            for (int i = 0; i < lista.size(); i++)
                minimo = min(minimo, (int) lista[i].size());

            return minimo;
        }


        /**
         * Retorna o Grau Máximo do grafo
        */
        int GrauMaximo() {
            // Não houver nenhum vértice (o grafo é vazio) não há um grau máximo
            if (lista.size() == 0)
                return -1;

            // Como o Grau Mínimo de qualquer vértice é zero, se houver algum vértice com grau maior com certeza
            // a variável irá mudar de valor.
            // Sendo assim, é certo que a variavel "maximo" terá o valor correto após a execução do laço "for"
            int maximo = 0;
            for (int i = 0; i < lista.size(); i++)
                maximo = max(maximo, (int) lista[i].size());
            
            return maximo;
        }


        /********************* Exercício 03 *********************/
        /*
        Escreva uma função que determine a sequência de graus de G.
        */
        /********************************************************/


        /**
         * Exibe a sequência de graus do grafo
        */
        void ExibeSequenciaGraus() {
            vector<int> graus(lista.size());

            for (int i = 0; i < lista.size(); i++)
                graus[i] = lista[i].size();
            
            // Ordenando os graus de forma crescente
            sort(graus.begin(), graus.end());

            // Exibe os graus
            cout << endl;
            cout << "Sequencia de graus do grafo: ";
            for (int i = 0; i < graus.size(); i++)
            {
                cout << graus[i];
                if (i < (graus.size() - 1))
                    cout << ", ";
            }
            cout << endl;
        }


        /********************* Exercício 04 *********************/
        /*
        Escreva uma função que determine o grau e as vizinhanças aberta e fechada de um vértice v.
        */
        /********************************************************/


        /**
         * Informa se um determinado vértice é válido (está no grafo) ou não
        */
        bool VerticeValido(int v) {
            return (v >= 0 && v < matriz.size());
        }


        /**
         * Retorna o valor do grau do vértice "v".
         * Se o vértice for inválido, retorna -1
        */
        int GrauVertice(int v) {
            if (!VerticeValido(v))
                return -1;

            return lista[v].size();
        }


        /**
         * Exibe a vizinhança aberta de um determinado vértice "v"
        */
        void ExibeVizinhancaAberta(int v) {
            if (!VerticeValido(v))
            {
                cout << "O vertice " << v << " eh invalido!" << endl;
                return;
            }


            cout << "Vizinhanca aberta do vertice " << v << ": ";
            for (int i = 0; i < lista[v].size(); i++)
            {
                cout << lista[v][i];
                if (i < (lista[v].size() - 1))
                    cout << ", ";
            }
            cout << endl;
        }


        /**
         * Exibe a vizinhança fechada de um determinado vértice "v"
        */
        void ExibeVizinhancaFechada(int v) {
            if (!VerticeValido(v))
            {
                cout << "O vertice " << v << " eh invalido!" << endl;
                return;
            }


            cout << "Vizinhanca fechada do vertice " << v << ": ";
            for (int i = 0; i < lista[v].size(); i++)
            {
                cout << lista[v][i] << ", ";
            }
            cout << v << endl;
        }


        /********************* Exercício 05 *********************/
        /*
        Escreva uma função que que determine se dois vértices distintos u e v são vizinhos (ou adjacentes).
        Lembrando que eles são vizinhos se a aresta entre eles existir, ou seja, se (u,v)∈E.
        Em caso afirmativo, diz-se que u e v são os extremos de tal aresta.
        */
        /********************************************************/


        /**
         * Retorna a quantidade de vértices do grafo
        */
        int QuantidadeVertices() {
            return matriz.size();
        }


        /**
         * Verifica se dois vértices "u" e "v" são vizinhos.
         * Se um (ou ambos) dos vértices for inválido, o resultado será "false"
        */
        bool VerticesVizinhos(int u, int v) {
            if (!VerticeValido(u) || !VerticeValido(v))
                return false;
            
            return matriz[u][v];
        }


        /********************* Exercício 06 *********************/
        /*
        Um grafo é regular se todos os seus vértices possuem o mesmo grau.
        Se o grau de todos os vértices for igual a k, diz-se que o grafo é k-regular.
        Escreva uma função que informe se G é regular, deixando claro o valor do grau em caso afirmativo.
        */
        /********************************************************/


        /**
         * Verifica se o gráfo é regular.
         * Quando verdadeiro, a função retorna o grau dos vértices.
         * Caso contrário, retorna -1.
        */
        int EhRegular() {
            if (QuantidadeVertices() == 0)
                return -1;
            
            // Não precisamos verificar se o índice 0 não é vazio, pois a condição anterior
            // nos garante que temos pelo menos um vértice no grafo
            int grau = lista[0].size();
            for (int i = 1; i < lista.size(); i++)
            {
                if (lista[i].size() != grau)
                    return -1;
            }

            // Como nenhum vértice tem grau diferente do primeiro, então o grafo é regular
            return grau;
        }


        /********************* Exercício 07 *********************/
        /*
        Escreva uma função que informe se G é completo, ou seja, se ele possui todas as arestas possíveis.
        Sendo n o número de vértices de G, vimos em sala que um grafo simples pode ter de 0 a n(n−1)/2 arestas.
        Portanto, o grafo completo com n vértices, denotado por Kn, possui n(n−1)/2 arestas. Abaixo ilustra-se o grafo K7.
        */
        /********************************************************/


        /**
         * Retorna verdadeiro se o grafo é completo.
         * Retorna falso caso contrário.
        */
        bool EhCompleto() {
            // Armazenará o somatório dos graus
            int somaGraus = 0;

            for (int i = 0; i < lista.size(); i++)
                somaGraus += lista[i].size();
            
            // Verifica se a soma dos graus é igual ao dobro do máximo de arestas
            return (somaGraus == (QuantidadeVertices() * (QuantidadeVertices()-1)));
        }


        /********************* Exercício 08 *********************/
        /*
        Escreva uma função que liste todos os vértices universais de G, que são os vérticesque estão ligados
        a todos os outros vértice do grafo.
        O grau de um vértice universal é, portanto, igual a n−1.
        */
        /********************************************************/


        /**
         * Lista todos os vértices universais do grafo
        */
        void ExibeVerticesUniversais() {
            // Quantidade de ligações necessárias para um vértice ser universal
            int ligacoesNecessarias = QuantidadeVertices() - 1;

            cout << "Vertices universais do grafo:";
            for (int i = 0; i < lista.size(); i++)
            {
                if (lista[i].size() == ligacoesNecessarias)
                    cout << " " << i;
            }
            cout << endl;
        }


        /********************* Exercício 09 *********************/
        /*
        Escreva uma função que liste todos os vértices isolados de G, que são os vértices que não possuem vizinhos.
        O grau de um vértice isolado é, portanto, igual a 0.
        */
        /********************************************************/


        /**
         * Lista todos os vértices isolados do grafo
        */
        void ExibeVerticesIsolados() {
            cout << "Vertices isolados do grafo:";
            for (int i = 0; i < lista.size(); i++)
            {
                if (lista[i].size() == 0)
                    cout << " " << i;
            }
            cout << endl;
        }


        /********************* Exercício 10 *********************/
        /*
        Escreva uma função que determine se uma lista de vértices e uma lista de arestas informadas pelo usuário representam
        um subgrafo H de G. Para H ser subgrafo de G, todos os seus vértices e suas arestas devem estar contidos,
        respectivamente, nos conjuntos de vértices e arestas de G. Além disso, os extremos de todas as arestas listadas
        pelo usuário devem estar contidos no conjunto de vértices informado, do contrário não se trata de um grafo pois
        teríamos uma aresta sem os dois extremos.
        */
        /********************************************************/


        /**
         * Retorna verdadeiro se o conjunto de vertices e o conjunto de arestas
         * formar um subgrafo.
         * Caso contrário, retorna falso.
        */
        bool EhSubgrafo(vector<int>& vertices, vector<vector<int>>& arestas) {
            // Se não há nenhum vértice, então não é um subgrafo.
            // O mesmo vale para quando o número de vértices é maior que o grafo.
            if (vertices.size() == 0 || vertices.size() > QuantidadeVertices())
                return false;
            

            /*
            matrizSubgrafo: Matriz de adjacências do subgrafo recebido como parâmetro.
                            Para não ocupar memória desnecessariamente, a matriz terá tamanho
                            K x K, sendo K o número de vértices no subgrafo.
                            
                            Para usar a matriz corretamente é necessário o uso da estrutura auxiliar
                            "verticesHash", para indicar corretamente o índice de um vértice
                            na matriz.


            vecticesHash:   Os vértices do grafo (nessa classe GrafoSimples) são classificados
                            com números inteiros positivos >= 0. Se o grafo tem K vértices, portanto,
                            eles estão no intervalo [0, K-1].
                            Sendo assim, se o vector de vértices recebido como parâmetro for válido,
                            seus vértices irão variar no intervalo [0, QuantidadeVertices()-1].

                            Para cada vértice "i", "verticesHash[i]" informa a posição do vértice "i"
                            na matriz de adjacências do subgrafo.
                            Se "verticesHash[i] == -1", então o vértice "i" não faz parte do subgrafo
            */
            vector<int> verticesHash(QuantidadeVertices(), -1);
            vector<vector<int>> matrizSubgrafo;
            int proximoIndice = 0; // Variável auxiliar para determinar o índice que um vértice válido
                                   // ocupará na matriz de adjacências


            // Verifica se todos os vértices no vector são válidos
            for (int i = 0; i < vertices.size(); i++)
            {
                if (!VerticeValido(vertices[i]))
                    return false;
                
                verticesHash[vertices[i]] = proximoIndice;
                proximoIndice++;
            }


            // Como todos os vértices são válidos, agora podemos criar a matriz de
            // adjacências.
            // A matriz terá tamanho "vertices.size() x vertices.size()", com todos os
            // valores iniciados com 0
            matrizSubgrafo = vector<vector<int>>(vertices.size(), vector<int>(vertices.size(), 0));


            // Testa todas as arestas.
            //
            // Uma aresta será inválida se:
            //      1 - Algum vértice não pertencer ao subgrafo;
            //      2 - For uma aresta paralela;
            //      3 - For um laço
            int vertice1;
            int indiceV1;

            int vertice2;
            int indiceV2;

            for (int i = 0; i < arestas.size(); i++)
            {
                vertice1 = arestas[i][0];
                vertice2 = arestas[i][1];

                /* Verifica se os vértices são e a aresta válidos */

                if (!VerticeValido(vertice1) || !VerticeValido(vertice2))
                    return false;
                
                if (matriz[vertice1][vertice2] == 0)
                    return false;

                if (verticesHash[vertice1] == -1 || verticesHash[vertice2] == -1 || vertice1 == vertice2)
                    return false;
                

                indiceV1 = verticesHash[vertice1];
                indiceV2 = verticesHash[vertice2];

                if (matrizSubgrafo[indiceV1][indiceV2] == 1) // Aresta Paralela
                    return false;

                /**************************************************/

                // Sendo a aresta válida, ela é incluída na matriz de adjacências
                matrizSubgrafo[indiceV1][indiceV2] = 1;
                matrizSubgrafo[indiceV2][indiceV1] = 1;
            }


            // Se todos os vértices e arestas são válidos, definitivamente
            // o subgrafo é válido
            return true;
        }


        /********************* Exercício 11 *********************/
        /*
        Uma sequência de k vértices v1,v2,...,vk é um passeio em G se, para todo 1≤i≤k−1, vale que vi e vi+1 são vizinhos.
        Isso equivale a dizer que vértices adjacentes na sequência devem ser vizinhos.
        Não há outra restrição a ser considerada na definição de passeio, sendo possível, por exemplo,
        repetir vértices e arestas. Um exemplo de passeio no grafo da Figura 1 é 1,2,3,4,3,6.

        Escreva uma função que determine se uma sequência de vértices constitui um passeio em G.
        */
        /********************************************************/


        /**
         * Retorna verdadeiro se o conjunto de vértices formar um passei no grafo.
         * Retorna falso caso contrário.
        */
        bool EhPasseio(vector<int>& vertices) {
            // Se não há nenhum vértice não tem como ser um passeio
            if (vertices.size() == 0)
                return false;

            // Se o conjunto de vértices tiver tamanho um, ele não será verificado
            // no laço "for" a seguir, então sua validade é verificada mais cedo
            if (!VerticeValido(vertices[0]))
                return false;
            

            // Verifica a validade dos vértices e arestas no passeio
            for (int i = 0; i < vertices.size()-1; i++)
            {
                if (!VerticeValido(vertices[i]) || !VerticeValido(vertices[i+1]))
                    return false;
                if (matriz[vertices[i]][vertices[i+1]] == 0)
                    return false;
            }

            // Se todos os vértices e arestas são válidos, então o passeio é válido
            return true;
        }


        /********************* Exercício 12 *********************/
        /*
        Um caminho é um passeio que não repete vértices. O passeio 1,2,3,4 é um caminho no grafo da Figura 1.

        Escreva uma função que determine se uma dada sequência de vértices constitui um caminho em G.
        */
        /********************************************************/


        /**
         * Retorna verdadeiro se o conjunto de vértices formar um caminho no grafo.
         * Retorna falso caso contrário.
        */
        bool EhCaminho(vector<int>& vertices) {
            // Se não há nenhum vértice, não é um caminho
            if (vertices.size() == 0)
                return false;
            
            // Se o conjunto de vértices tiver tamanho um, ele não será verificado
            // no laço "for" a seguir, então sua validade é verificada mais cedo
            if (!VerticeValido(vertices[0]))
                return false;


            // vector usado para indicar se um vértice já foi usado ou não no caminho
            vector<bool> usado(QuantidadeVertices(), false);
            usado[vertices[0]] = true; // Como vamos começar a percorrer o caminho a partir
                                       // de vertices[0], ele já começa marcado como usado

            // Verifica a validade dos vértices e arestas no caminho
            for (int i = 0; i < vertices.size()-1; i++)
            {
                if (!VerticeValido(vertices[i]) || !VerticeValido(vertices[i+1]))
                    return false;
                
                if (matriz[vertices[i]][vertices[i+1]] == 0) // Não há aresta conectando os vértices
                    return false;
                
                if (usado[vertices[i+1]]) // O próximo vértice é repetido
                    return false;
                
                // Vértices e aresta válidos
                usado[vertices[i+1]] = true;
            }

            // Se todos os vértices e arestas são válidos, então o caminho é válido
            return true;
        }


        /********************* Exercício 13 *********************/
        /*
        Um ciclo é um passeio que não repete vértices, com exceção do primeiro e último vértices, que são iguais.
        O passeio 1,2,4,3,1 é um ciclo no grafo da Figura 1.

        Escreva uma função que determine se uma dada sequência de vértices constitui um ciclo em G.
        */
        /********************************************************/


        /**
         * Retorna verdadeiro se o conjunto de vértices formar um ciclo no grafo.
         * Retorna falso caso contrário.
        */
        bool EhCiclo(vector<int>& vertices) {
            // São necessários 3 vértices, no mínimo, para formar um ciclo
            if (vertices.size() <= 2)
                return false;

            // Antes de analisar a sequencia de vértices, podemos verificar se
            // o primeiro e último são iguais            
            if (vertices[0] != vertices.back())
                return false;


            // vector usado para indicar se um vértice já foi usado ou não no ciclo
            vector<bool> usado(QuantidadeVertices(), false);
            usado[vertices[0]] = true; // Como vamos começar a percorrer o ciclo a partir
                                       // de vertices[0], ele já começa marcado como usado

            // Verifica a validade dos vértices e arestas no ciclo
            for (int i = 0; i < vertices.size()-1; i++)
            {
                if (!VerticeValido(vertices[i]) || !VerticeValido(vertices[i+1]))
                    return false;
                
                if (matriz[vertices[i]][vertices[i+1]] == 0) // Não há aresta conectando os vértices
                    return false;
                
                // Verifica se o próximo vértice é repetido mas não é o último
                if (usado[vertices[i+1]] && (i+1 < vertices.size()-1))
                    return false;
                
                // Vértices e aresta válidos
                usado[vertices[i+1]] = true;
            }

            // Se todos os vértices e arestas são válidos, então o ciclo é válido
            return true;
        }


        /********************* Exercício 14 *********************/
        /*
        Uma trilha é um passeio que não repete arestas.

        Escreva uma função que determine se uma dada sequência de vértices constitui uma trilha em  G.
        */
        /********************************************************/


        /**
         * Retorna verdadeiro se o conjunto de vértices formar uma trilha no grafo.
         * Retorna falso caso contrário.
        */
        bool EhTrilha(vector<int>& vertices) {
            // Se não há nenhum vértice, não é uma trilha (mas é permitido
            // não ter nenhuma aresta)
            if (vertices.size() == 0)
                return false;

            // Se o conjunto consistir de um único vértice, só é necessário
            // verificar se o vértice é válido ou não
            if (vertices.size() == 1)
                if (VerticeValido(vertices[0]))
                    return true;
                else
                    return false;
            

            /*
            matrizTrilha:   Matriz de adjacências do conjunto de vértices recebido como parâmetro.
                            Para não ocupar memória desnecessariamente, a matriz terá tamanho
                            K x K, sendo K o número de vértices no conjunto.
                                
                            Para usar a matriz corretamente é necessário o uso da estrutura auxiliar
                            "verticesHash", para indicar corretamente o índice de um vértice
                            na matriz.


            vecticesHash:   Os vértices do grafo (nessa classe GrafoSimples) são classificados
                            com números inteiros positivos >= 0. Se o grafo tem K vértices, portanto,
                            eles estão no intervalo [0, K-1].
                            Sendo assim, se o vector de vértices recebido como parâmetro for válido,
                            seus vértices irão variar no intervalo [0, QuantidadeVertices()-1].

                            Para cada vértice "i", "verticesHash[i]" informa a posição do vértice "i"
                            na matriz de adjacências.
                            Se "verticesHash[i] == -1", então o vértice "i" não faz parte do conjunto
            */
            vector<int> verticesHash(QuantidadeVertices(), -1);
            vector<vector<int>> matrizTrilha;
            int proximoIndice = 0; // Variável auxiliar para determinar o índice que um vértice válido
                                   // ocupará na matriz de adjacências (matrizTrilha)

            // Verifica se todos os vértices no vector são válidos
            for (int i = 0; i < vertices.size(); i++)
            {
                if (!VerticeValido(vertices[i]))
                    return false;
                
                verticesHash[vertices[i]] = proximoIndice;
                proximoIndice++;
            }


            // Se todos os vértices no conjunto são válidos, podemos inicializar matrizTrilha
            // com o tamanho correto.
            // A matriz começa com todos os valores iguais a 0, ou seja, indicando que
            // no momento não foi marcada nenhuma aresta
            matrizTrilha = vector<vector<int>>(vertices.size(), vector<int>(vertices.size(), 0));


            // Verifica se há aresta repetida
            int indiceV1;
            int indiceV2;

            for (int i = 0; i < vertices.size()-1; i++)
            {
                indiceV1 = verticesHash[vertices[i]];
                indiceV2 = verticesHash[vertices[i+1]];

                if (matrizTrilha[indiceV1][indiceV2] == 1) // A aresta é repetida
                    return false;
                
                // Como a aresta não é repetida, marcamos ela na matriz
                matrizTrilha[indiceV1][indiceV2] = 1;
                matrizTrilha[indiceV2][indiceV1] = 1;
            }


            // Como nenhuma aresta se repete, a sequência de vértices constitui
            // uma Trilha
            return true;
        }


        /********************* Exercício 15 *********************/
        /*
        Um subconjunto de vértices  S⊆V  é um clique de  G  se, para quaisquer dois vértices distintos  i,j ∈ S ,
        existe a aresta  (i,j)  no grafo. Portanto, os vértices de um clique estão dois a dois conectados por uma aresta.
        Os seguintes conjuntos são exemplos de clique do grafo da Figura 1:  {1,2},{1,2,3},{1,2,3,4}.

        Escreva uma função que determine se um dado conjunto de vértices constitui um clique de  G .
        */
        /********************************************************/


        /**
         * Retorna verdadeiro se o conjunto de vértices formar um clique.
         * Retorna falso caso contrário.
        */
        bool EhClique(vector<int>& vertices) {
            // Não tem como ser um clique se não há nenhum vértice
            if (vertices.size() == 0)
                return false;
            

            // Verifica se todos os vértices são válidos
            for (int i = 0; i < vertices.size(); i++)
            {
                if (!VerticeValido(vertices[i]))
                    return false;
            }


            // Verifica se o conjunto de vértices tem todas as ligações necessárias para
            // formar um clique
            for (int i = 0; i < vertices.size()-1; i++)
            {
                for (int j = i+1; j < vertices.size(); j++)
                {
                    if (matriz[vertices[i]][vertices[j]] == 0)
                        return false;
                }
            }

            // Se todos os vértices são válidos e todas as arestas necessárias existem,
            // então o conjunto é um clique 
            return true;
        }


        /********************* Exercício 16 *********************/
        /*
        Um clique  S⊆V  é dito maximal se não houver outro clique  S′  tal que  S′⊇S . Isto é, se não for possível expandir
        o conjunto  S  através da inserção de um ou mais vértices de modo que o conjunto resultante ainda seja um clique.
        Os seguintes conjuntos são exemplos de cliques maximais do grafo da Figura 1:  {1,2,3,4},{5,6,7} .
        Observe que o conjunto  {1,2,3} , apesar de ser clique, não é maximal pois ele poderia ser estendido através
        da adição do vértice 4.

        Escreva uma função que determine se um dado conjunto de vértices constitui um clique maximal de  G .
        */
        /********************************************************/


        /**
         * Retorna verdadeiro se o conjunto de vértices formar um clique maximal.
         * Retorna falso caso contrário.
        */
        bool EhCliqueMaximal(vector<int>& vertices) {
            // Não tem como ser um clique maximal se não é um clique
            if (!EhClique(vertices))
                return false;
            

            // Nesse vector, para cada vértice V, ligacoes[V] indica quantos vértices
            // do clique recebido como parâmetro apontam para V
            vector<int> ligacoes(QuantidadeVertices(), 0); // Todos os valores começam em 0

            // Percorre a lista de adjacências de todos os vértices recebidos e incrementa
            // o contador de ligações (vector ligacoes).
            // Se algum vértice atingir "vertices.size()" ligações, então há pelo menos
            // um vértice que poderia ser adicionado ao conjunto de forma que continuaria
            // sendo um clique, já que esse vértice teria ligações com todos os outros
            for (int i = 0; i < vertices.size(); i++)
            {
                for (int j = 0; j < lista[i].size(); j++)
                {
                    ligacoes[ lista[i][j] ]++;
                    
                    // Se for verdadeira a condição abaixo, então há um vértice que poderia
                    // ser adicionado ao conjunto e, portanto, o clique não é maximal
                    if (ligacoes[ lista[i][j] ] == vertices.size())
                        return false;
                }
            }

            // Como não há nenhum vértice que possa ser incluído, o clique é maximal
            return true;
        }


        /********************* Exercício 17 *********************/
        /*
        O complemento de  G  é um grafo  G¯=(V,E¯)  que possui os mesmos vértices de  G , mas cujo conjunto de arestas é o complemento
        do conjunto de arestas de  G . Portanto, uma aresta  (i,j)  pertence a  E¯  se, e somente se, ela não pertece a  E.
        O grafo abaixo corresponde ao complemento do grafo ilustrado na Figura 1.

        Escreva uma função que receba um grafo como parâmetro e retorne o seu complemento.
        Observe que o retorno da função consiste em um grafo.
        */
        /********************************************************/


        /**
         * Cria e retorna o complemento do grafo como referência
        */
        GrafoSimples CriaComplemento() {
            GrafoSimples complemento;

            // Inicializa a matriz e a lista de adjacências do complemento
            complemento.matriz = vector<vector<int>>(QuantidadeVertices(), vector<int>(QuantidadeVertices()));
            complemento.lista = vector<vector<int>>(QuantidadeVertices());

            // Percorre toda a matriz de adjacências para poder atribuir valor tanto
            // à matriz quanto à lista de adjacências do complemento
            for (int i = 0; i < matriz.size(); i++)
            {
                for (int j = 0; j < matriz[i].size(); j++)
                {
                    if (matriz[i][j] == 0 && i != j)
                    {
                        complemento.matriz[i][j] = 1;
                        complemento.lista[i].push_back(j);
                    }
                    else // matriz[i][j] == 1 || i == j
                    {
                        complemento.matriz[i][j] = 0;
                    }
                }
            }

            return complemento;
        }
};



/***********************************************************************/
/*                             Função Main                             */
/***********************************************************************/
int main() {
    GrafoSimples grafo;

    /* Exercício 01 */
    grafo.LerArquivo(string(ARQUIVO));

    grafo.ExibeMatrizAdjacencias();
    grafo.ExibeListaAdjacencias();


    /* Exercício 02 */
    cout << endl;
    cout << "Grau Maximo: " << grafo.GrauMaximo() << endl;
    cout << "Grau Minimo: " << grafo.GrauMinimo() << endl;


    /* Exercício 03 */
    grafo.ExibeSequenciaGraus();


    /* Exercício 04 */
    for (int i = 0; grafo.VerticeValido(i); i++)
    {
        cout << endl;
        cout << "Grau do vertice " << i << ": " << grafo.GrauVertice(i) << endl;
        grafo.ExibeVizinhancaAberta(i);
        grafo.ExibeVizinhancaFechada(i);
    }


    /* Exercício 05 */
    srand(time(NULL));

    cout << endl;
    for (int i = 0; i < TESTES_VIZINHANCA; i++)
    {
        int v1 = rand() % grafo.QuantidadeVertices();
        int v2 = rand() % grafo.QuantidadeVertices();
        
        if (grafo.VerticesVizinhos(v1, v2))
        {
            cout << "Os vertices " << v1 << " e " << v2 << " sao vizinhos!" << endl;
        }
        else
        {
            cout << "Os vertices " << v1 << " e " << v2 << " NAO sao vizinhos!" << endl;
        }
    }


    /* Exercício 06 */
    cout << endl;
    if (grafo.EhRegular() != -1)
    {
        cout << "O grafo eh " << grafo.EhRegular() << "-regular!" << endl;
    }
    else
    {
        cout << "O grafo NAO eh regular!" << endl;
    }


    /* Exercício 07 */
    if (grafo.EhCompleto())
    {
        cout << "O grafo eh completo!" << endl;
    }
    else
    {
        cout << "O grafo NAO eh completo!" << endl;
    }


    /* Exercício 08 */
    cout << endl;
    grafo.ExibeVerticesUniversais();


    /* Exercício 09 */
    grafo.ExibeVerticesIsolados();


    /* Exercício 10 */
    vector<int> vertices = {0, 1, 2, 3, 5};
    vector<vector<int>> arestas = {
        {0, 3},
        {2, 1},
        {2, 5}
    };

    cout << endl;
    if (grafo.EhSubgrafo(vertices, arestas))
    {
        cout << "O subgrafo eh valido!" << endl;
    }
    else
    {
        cout << "O subgrafo NAO eh valido!" << endl;
    }


    /* Exercício 11 */
    vector<int> verticesPasseio = {0, 1, 2, 3, 0, 2, 5};

    cout << endl;
    if (grafo.EhPasseio(verticesPasseio))
    {
        cout << "O conjunto de vertices eh um passeio!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um passeio!" << endl;
    }


    /* Exercício 12 */
    vector<int> verticesCaminho = {0, 1, 3, 2, 5, 4, 6, 5};

    if (grafo.EhCaminho(verticesCaminho))
    {
        cout << "O conjunto de vertices eh um caminho!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um caminho!" << endl;
    }


    /* Exercício 13 */
    vector<int> verticesCiclo = {0, 1, 3, 2, 0};

    if (grafo.EhCiclo(verticesCiclo))
    {
        cout << "O conjunto de vertices eh um ciclo!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um ciclo!" << endl;
    }


    /* Exercício 14 */
    vector<int> verticesTrilha = {2, 0, 1, 3, 2, 5, 6, 4};

    if (grafo.EhTrilha(verticesTrilha))
    {
        cout << "O conjunto de vertices eh um Trilha!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um Trilha!" << endl;
    }


    /* Exercício 15 */
    vector<int> verticesClique = {0, 1, 2, 3};

    cout << endl;
    if (grafo.EhClique(verticesClique))
    {
        cout << "O conjunto de vertices eh um Clique!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um Clique!" << endl;
    }


    /* Exercício 16 */
    vector<int> verticesCliqueMaximal = {2, 0, 1, 3};

    if (grafo.EhCliqueMaximal(verticesCliqueMaximal))
    {
        cout << "O conjunto de vertices eh um Clique Maximal!" << endl;
    }
    else
    {
        cout << "O conjunto de vertices NAO eh um Clique Maximal!" << endl;
    }


    /* Exercício 17 */
    cout << endl << endl;;
    cout << "Dados do Grafo Complemento:" << endl;

    GrafoSimples grafoComplemento = grafo.CriaComplemento();
    grafoComplemento.ExibeMatrizAdjacencias();
    grafoComplemento.ExibeListaAdjacencias();

    cout << endl;
    cout << "Fim do Grafo Complemento!" << endl;


    return 0;
}