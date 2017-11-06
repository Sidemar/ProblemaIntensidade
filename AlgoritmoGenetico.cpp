#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <random>

using namespace std;

class Solucao {
public:
	int *x;
	double objetivos[3];
	Solucao(int N) {
		x = new int[N];
		for (int i = 0; i < N; ++i)
		{
			x[i] = -1;
		}
		objetivos[0] = -1;
		objetivos[1] = -1;
		objetivos[2] = -1;
	}
	
};

double calcularValorObjetivo(int solucao[], double **mat, int l, int c) {
	double vet[c] = {0};
	double valor;

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
	for (int i = 0; i < l; ++i)
	{
		soma += vet[i];
	}

	//cout << soma/l << endl;

	return soma;
}

int randInt(int menor, int maior) {
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	return rand()%(maior-menor+1) + menor;
}

/*int randInt(int begin, int end) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  	std::default_random_engine generator (seed);
	std::uniform_int_distribution<int> distribution(begin,end);
    return distribution(generator);
}*/

bool dominancia(double obj1[], double obj2[]) {
	if((obj1[0] < obj2[0]) && (obj1[1] <= obj2[1]) && (obj1[2] <= obj2[2])
		|| (obj1[0] <= obj2[0]) && (obj1[1] < obj2[1]) && (obj1[2] <= obj2[2])
		|| (obj1[0] <= obj2[0]) && (obj1[1] <= obj2[1]) && (obj1[2] < obj2[2])) {
		return true;
	} else {
		return false;
	}
}

void filter(vector<Solucao> &populacao, Solucao so) {
    bool dominado = false;
    
    for (int i = 0; i < populacao.size(); ++i)
    {
    	dominado = dominancia(populacao[i].objetivos, so.objetivos);

    	if (dominado || (so.objetivos[0] == populacao[i].objetivos[0] 
    		&& so.objetivos[1] == populacao[i].objetivos[1] 
    		&& so.objetivos[2] == populacao[i].objetivos[2])) return;
    	if (dominancia(so.objetivos, populacao[i].objetivos)) {
            std::swap(populacao[i], populacao.back());
            populacao.pop_back();
            i--;
        }
    }

    populacao.push_back(so);
}

int main(int argc, char const *argv[])
{

	int N, MT, MN, MC;
	int TLB, NUB, CUB;

	cin >> N >> MT >> MN >> MC;

	cin >> TLB >> NUB >> CUB;

	double **At = new double*[MT/N];
	double **An = new double*[MN/N];
	double **Ac = new double*[MC/N];
 
    for(int i = 0; i < MT/N; ++i)
        At[i] = new double[N];

    for(int i = 0; i < MN/N; ++i)
        An[i] = new double[N];

    for(int i = 0; i < MC/N; ++i)
        Ac[i] = new double[N];


    for (int i = 0; i < MT/N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> At[i][j];
		}
	}

	for (int i = 0; i < MN/N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> An[i][j];
		}
	}

	for (int i = 0; i < MC/N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> Ac[i][j];
		}
	}

	//double fT = 0.0;
	//double fN = 0.0;
	//double fC = 0.0;

	//int solucao[N] = {100,100,100};

	
	//return 0;

	//cout << calcularValorObjetivo(solucao, At, N/MT, N)/MT << endl;

	//return 0;

	int tamPopulacao = 50;

	vector<Solucao> populacao;

	for (int i = 0; i < tamPopulacao; ++i)
	{
		Solucao s1(N);

		//int *x = new int[N];
		for (int j = 0; j < N; ++j)
		{
			s1.x[j] = randInt(0, 200);
		}

		s1.objetivos[0] = (TLB - calcularValorObjetivo(s1.x, At, MT/N, N)/MT)/TLB;
		s1.objetivos[1] = (calcularValorObjetivo(s1.x, An, MN/N, N)/MN - NUB)/NUB;
		s1.objetivos[2] = (calcularValorObjetivo(s1.x, Ac, MC/N, N)/MC - CUB)/CUB;

		filter(populacao, s1);

		//populacao.push_back(s1);

	}

	// Calcular as funcoes objetivos da populacao
	//return 0;

	cout << endl;
	for (int i = 0; i < populacao.size(); ++i)
	{
		
		/*for (int j = 0; j < N; ++j)
		{
			cout << populacao[i].x[j] << " ";
		}*/

		cout << populacao[i].objetivos[0] << " " << populacao[i].objetivos[1] << " " << populacao[i].objetivos[2] << endl;
	}
	cout << endl;


	int geracoes = 50;

	int valor1 = 0;
	int valor2 = 0;
	int quebraMudanca = 0;
	int opcao = 0;
	for (int i = 0; i < geracoes; ++i)
	{
		opcao = randInt(0, 1);

		//if(true) {
		if(populacao.size() < 2 || opcao == 0) { // Mutacao

			valor1 = randInt(0, populacao.size()-1);

			valor2 = randInt(0, N-1);


			//cout << endl << valor1 << " " << valor2;

			quebraMudanca = randInt(0, 200);


			/*cout << endl << "Novo valor: " << quebraMudanca << endl;

			for (int j = 0; j < N; ++j)
			{
				cout << populacao[valor1][j] << " ";
			}

			cout << endl;*/
			
			populacao[valor1].x[valor2] = quebraMudanca;

			/*for (int j = 0; j < N; ++j)
			{
				cout << populacao[valor1][j] << " ";
			}

			cout << endl;*/

			populacao[valor1].objetivos[0] = (TLB - calcularValorObjetivo(populacao[valor1].x, At, MT/N, N)/MT)/TLB;
			populacao[valor1].objetivos[1] = (calcularValorObjetivo(populacao[valor1].x, An, MN/N, N)/MN - NUB)/NUB;
			populacao[valor1].objetivos[2] = (calcularValorObjetivo(populacao[valor1].x, Ac, MC/N, N)/MC - CUB)/CUB;


		} else { // Recombinar
			valor1 = randInt(0, populacao.size()-1);

			do {
				valor2 = randInt(0, populacao.size()-1);
			}while(valor1 == valor2);
			
			quebraMudanca = randInt(0, N-1);

			Solucao filho1(N);
			Solucao filho2(N);

			//int *filho1 = new int[N];
			//int *filho2 = new int[N];

			//cout << endl << "QUEBRA: " << quebra << endl;

			for (int j = 0; j < quebraMudanca; ++j)
			{
				filho1.x[j] = populacao[valor1].x[j];
				filho2.x[j] = populacao[valor2].x[j];
			}

			for (int j = quebraMudanca; j < N; ++j)
			{
				filho1.x[j] = populacao[valor2].x[j];
				filho2.x[j] = populacao[valor1].x[j];
			}

			//populacao.push_back(filho1);
			//populacao.push_back(filho2);

			filho1.objetivos[0] = (TLB - calcularValorObjetivo(filho1.x, At, MT/N, N)/MT)/TLB;
			filho1.objetivos[1] = (calcularValorObjetivo(filho1.x, An, MN/N, N)/MN - NUB)/NUB;
			filho1.objetivos[2] = (calcularValorObjetivo(filho1.x, Ac, MC/N, N)/MC - CUB)/CUB;

			filho2.objetivos[0] = (TLB - calcularValorObjetivo(filho2.x, At, MT/N, N)/MT)/TLB;
			filho2.objetivos[1] = (calcularValorObjetivo(filho2.x, An, MN/N, N)/MN - NUB)/NUB;
			filho2.objetivos[2] = (calcularValorObjetivo(filho2.x, Ac, MC/N, N)/MC - CUB)/CUB;

			//cout << endl << "= (" << filho1.objetivos[0] << ", " << filho1.objetivos[1] <<", " << filho1.objetivos[2] << ")" << endl;

			filter(populacao, filho1);
			filter(populacao, filho2);


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

	cout << endl;
	for (int i = 0; i < populacao.size(); ++i)
	{
		
		/*for (int j = 0; j < N; ++j)
		{
			cout << populacao[i].x[j] << " ";
		}*/

		cout << populacao[i].objetivos[0] << " " << populacao[i].objetivos[1] << " " << populacao[i].objetivos[2] << endl;
	}
	cout << endl;
	

	return 0;
}