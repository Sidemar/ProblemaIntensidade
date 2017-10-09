#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <random>

using namespace std;

/*int numeroAleatorio(int menor, int maior) {
	srand((unsigned)time(0));
	return rand()%(maior-menor+1) + menor;
}*/

double calcularValorObjetivo(int solucao[], double **mat, int l, int c) {
	double vet[c];
	double valor;

	//cout << endl;

	for (int i = 0; i < l; ++i)
	{
		valor = 0.0;
		for (int j = 0; j < c; ++j)
		{
			valor += mat[i][j] * solucao[j];
		}

		vet[i] = valor;
	}

	double soma = 0.0;
	for (int i = 0; i < c; ++i)
	{
		soma += vet[i];
	}

	return soma/l;
}

int randInt(int begin, int end) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  	std::default_random_engine generator (seed);
	std::uniform_int_distribution<int> distribution(begin,end);
    return distribution(generator);
}

int main(int argc, char const *argv[])
{

	int N, MT, MN, MC;
	int TLB, NUB, CUB;

	cin >> N >> MT >> MN >> MC;

	cin >> TLB >> NUB >> CUB;

	double **At = new double*[N/MT];
	double **An = new double*[N/MN];
	double **Ac = new double*[N/MC];
 
    for(int i = 0; i < N/MT; ++i)
        At[i] = new double[N];

    for(int i = 0; i < N/MN; ++i)
        An[i] = new double[N];

    for(int i = 0; i < N/MC; ++i)
        Ac[i] = new double[N];


    for (int i = 0; i < N/MT; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> At[i][j];
		}
	}

	for (int i = 0; i < N/MN; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> An[i][j];
		}
	}

	for (int i = 0; i < N/MC; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> Ac[i][j];
		}
	}

	double fT = 0.0;
	double fN = 0.0;
	double fC = 0.0;

	//int solucao[N] = {100,100,100};

	for (int i = 0; i < N/MT; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			//cout << At[i][j] << " ";
		}
		//cout << endl;
	}

	//cout << calcularValorObjetivo(solucao, At, N/MT, N)/MT << endl;

	return 0;

	int tamPopulacao = 10;

	vector<int*> populacao;

	for (int i = 0; i < tamPopulacao; ++i)
	{
		int *x = new int[N];
		for (int j = 0; j < N; ++j)
		{
			x[j] = randInt(0, 200);
		}

		populacao.push_back(x);
	}

	for (int i = 0; i < tamPopulacao; ++i)
	{
		
		for (int j = 0; j < N; ++j)
		{
			cout << populacao[i][j] << " ";
		}

		cout << endl;
	}


	int geracoes = 1;


	int valor1 = 0;
	int valor2 = 0;
	int quebraMudanca = 0;
	for (int i = 0; i < geracoes; ++i)
	{
		if(true) {
		//if(populacao.size() < 2) { // Mutacao
			valor1 = randInt(0, populacao.size());
			valor2 = randInt(0, N-1);

			quebraMudanca = randInt(0, 200);

			/*cout << endl << "Novo valor: " << quebraMudanca << endl;

			for (int j = 0; j < N; ++j)
			{
				cout << populacao[valor1][j] << " ";
			}

			cout << endl;*/

			populacao[valor1][valor2] = quebraMudanca;

			/*for (int j = 0; j < N; ++j)
			{
				cout << populacao[valor1][j] << " ";
			}

			cout << endl;*/

		} else { // Recombinar
			valor1 = randInt(0, populacao.size());

			do {
				valor2 = randInt(0, populacao.size());
			}while(valor1 == valor2);
			
			quebraMudanca = randInt(0, N-1);

			int *filho1 = new int[N];
			int *filho2 = new int[N];

			//cout << endl << "QUEBRA: " << quebra << endl;

			for (int j = 0; j < quebraMudanca; ++j)
			{
				filho1[j] = populacao[valor1][j];
				filho2[j] = populacao[valor2][j];
			}

			for (int j = quebraMudanca; j < N; ++j)
			{
				filho1[j] = populacao[valor2][j];
				filho2[j] = populacao[valor1][j];
			}


			/*cout << "Recombinacao" << endl;
			for (int j = 0; j < N; ++j)
			{
				cout << populacao[valor1][j] << " ";
			}

			cout << endl;

			for (int j = 0; j < N; ++j)
			{
				cout << populacao[valor2][j] << " ";
			}

			cout << endl;

			for (int j = 0; j < N; ++j)
			{
				cout << filho1[j] << " ";
			}

			cout << endl;

			for (int j = 0; j < N; ++j)
			{
				cout << filho2[j] << " ";
			}

			cout << endl;*/			

		}

		

	}

	return 0;
}