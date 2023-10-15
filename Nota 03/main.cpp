#include <iostream>
#include <ctime>
#include <algorithm>
#include <string>

// Origem: https://github.com/InductiveComputerScience/pbPlots/tree/v0.1.9.1/Cpp
#include "lib/pbPlots.hpp"
#include "lib/supportLib.hpp"
/////////////////////////////

#include "grafo_simples.hpp"
#include "union_find.hpp"
#include "karger.hpp"
#include "ingenuo.hpp"

#define N_ITER_MIN 1
#define N_ITER_MAX 151
#define PULO_ITER 3

#define N_EXEC 1000

#define PROBABILIDADE_PARADA 0.99

#define QTD_TIPO_GRAFO 2
#define QTD_GRAFOS_POR_TIPO 3

#define PASTA_INPUT string("in/")
#define PASTA_OUT_PROF string("out_prof/")

using namespace std;


int lerCorteMinimo(string arq) {
    ifstream stream(arq);
    int corteMinimo;

    if (!stream.is_open())
    {
        cout << ">>>> Erro ao abrir arquivo " << arq << endl;
        return -1;
    }

    stream >> corteMinimo;
    return corteMinimo;
}


int main() {
    srand(time(NULL));
    GrafoSimples grafo;
    string arquivoStr;

    /******************************************************************/
    /**
     * Aqui estão as configurações iniciais necessárias para se desenhar os gráficos.
     * Os vetores "xs", "ysKarger" e "ysIngenuo" representarão os pontos que devem ser desenhados,
     * e as configurações são descritas abaixo.
     * 
     * Origem: https://github.com/InductiveComputerScience/pbPlots/blob/v0.1.9.1/Cpp/example2.cpp
    */
    bool success;
    StringReference *errorMessage = new StringReference();

	vector<double> xs;
	vector<double> ysKarger, ysIngenuo;

	ScatterPlotSeries *series1 = GetDefaultScatterPlotSeriesSettings();
	series1->xs = &xs;
	series1->ys = &ysKarger;
	series1->linearInterpolation = false;
    series1->pointType = toVector(L"dots");
	// series1->lineType = toVector(L"dotted");
	// series1->lineThickness = 2;
	series1->color = CreateRGBAColor(0, 1, 0, 1);

	ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
	series2->xs = &xs;
	series2->ys = &ysIngenuo;
	series2->linearInterpolation = false;
    series2->pointType = toVector(L"dots");
	// series2->lineType = toVector(L"dotted");
	// series2->lineThickness = 2;
	series2->color = CreateRGBAColor(1, 0, 0, 1);

	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 720;
	settings->height = 480;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"Corte Minimo: Karger x Ingenuo");
	settings->xLabel = toVector(L"Qtd. Iteracoes");
	settings->yLabel = toVector(L"Probabilidade");
	settings->scatterPlotSeries->push_back(series1);
	settings->scatterPlotSeries->push_back(series2);
    /******************************************************************/


    for (int tipoGrafo = 1; tipoGrafo <= QTD_TIPO_GRAFO; tipoGrafo++)
    {
        for(int numGrafo = 1; numGrafo <= QTD_GRAFOS_POR_TIPO; numGrafo++)
        {
            // Próximo grafo a ser analisado
            arquivoStr = "graph_type" + to_string(tipoGrafo) + "_" + to_string(numGrafo);
            grafo.LerArquivo(PASTA_INPUT + arquivoStr);
            Karger::CriaListaArestas(grafo);
            Ingenuo::DefineVertices(grafo.QuantidadeVertices());

            // Inicializando as estruturas que representam os pontos do gráfico.
            // (Pontos nos extremos do gráficos não são desenhados, então um pouco de
            // gambiarra se faz necessário xD)
            xs.resize(1);
            xs[0] = 0;

            ysKarger.resize(1);
            ysKarger[0] = 1.1;

            ysIngenuo.resize(1);
            ysIngenuo[0] = 1.1;

            // Corte mínimo do grafo atual
            int corteMinimo = lerCorteMinimo(PASTA_OUT_PROF + arquivoStr);
            double probabilidadeKarger = 0;
            double probabilidadeIngenuo = 0;

            /**************************************************/
            cout << "\n\n\n";
            cout << "DADOS DO GRAFO "<< arquivoStr << "!!!!" << endl;
            cout << "Corte Minimo: " << corteMinimo << endl;

            for (int nIter = N_ITER_MIN; max(probabilidadeKarger, probabilidadeIngenuo) < PROBABILIDADE_PARADA || nIter > N_ITER_MAX; nIter += PULO_ITER)
            {
                int contadorAcertosKarger = 0;
                int contadorAcertosIngenuo = 0;

                // Realizando N_EXEC execuções do algoritmo de Karger com nIter iterações.
                // A razão do total de acertos pelo total de execuções resultará na probabilidade
                // do algoritmo encontrar o melhor corte com nIter iterações
                for (int exec = 1; exec <= N_EXEC; exec++)
                {
                    int corteKarger = grafo.QuantidadeArestas()+1;
                    int corteIngenuo = grafo.QuantidadeArestas()+1;
                    for (int iter = 1; iter <= nIter; iter++)
                    {
                        corteKarger = min(corteKarger, Karger::CorteArestas(grafo));
                        corteIngenuo = min(corteIngenuo, Ingenuo::CorteMinimo(grafo));
                    }

                    // Um acerto é considerada a cada execução, não a cada iteração
                    if (corteKarger == corteMinimo)
                    {
                        contadorAcertosKarger++;
                    }
                    if (corteIngenuo == corteMinimo)
                    {
                        contadorAcertosIngenuo++;
                    }
                }

                probabilidadeKarger = ((double) contadorAcertosKarger) / ((double) N_EXEC);
                probabilidadeIngenuo = ((double) contadorAcertosIngenuo) / ((double) N_EXEC);

                // Adicionando os pontos para serem desenhados.
                // (Pontos nos extremos do gráficos não são desenhados, então um pouco de
                // gambiarra se faz necessário xD)
                xs.push_back(nIter);
                ysKarger.push_back(max(probabilidadeKarger, 0.000001));
                ysIngenuo.push_back(max(probabilidadeIngenuo, 0.000001));

                cout << endl;
                cout << "Acertos Karger com " << nIter << " iteracoes: " << contadorAcertosKarger << endl;
                cout << "ProbabilidadeKarger com " << nIter << " iteracoes: " << probabilidadeKarger << endl;
                cout << "Acertos Ingenuo com " << nIter << " iteracoes: " << contadorAcertosIngenuo << endl;
                cout << "ProbabilidadeIngenuo com " << nIter << " iteracoes: " << probabilidadeIngenuo << endl;
            }

            // (Pontos nos extremos do gráficos não são desenhados, então um pouco de
            // gambiarra se faz necessário xD)
            xs.push_back(xs.size()*PULO_ITER);
            ysKarger.push_back(0);
            ysIngenuo.push_back(0);

        	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
            success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);
            if(success){
                vector<double> *pngdata = ConvertToPNG(imageReference->image);
                WriteToFile(pngdata, arquivoStr+".png");
                DeleteImage(imageReference->image);
            }else{
                cerr << "Error: ";
                for(wchar_t c : *errorMessage->string){
                    wcerr << c;
                }
                cerr << endl;
            }
        }
    }


    return 0;
}