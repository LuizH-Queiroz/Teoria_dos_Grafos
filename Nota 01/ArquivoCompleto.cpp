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
                    cout << (lista[i][j] + 1);
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


    return 0;
}