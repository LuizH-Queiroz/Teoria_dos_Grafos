#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>


using namespace std;



/******************************/
/* Classe de um Grafo Simples */
/******************************/

class GrafoSimples {
    private:

        vector<vector<int>> matriz; // Matriz de Adjacências
        vector<vector<int>> lista; // Lista de Adjacências
    

    public:


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
                cout << i+1 << ": ";
                for (int j = 0; j < lista[i].size(); j++)
                {
                    cout << (lista[i][j] + 1);
                    if (j < (lista[i].size()-1))
                        cout << ", ";
                }

                cout << endl;
            }
        }


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
