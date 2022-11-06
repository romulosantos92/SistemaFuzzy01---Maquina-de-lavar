#include <iostream>

#include "SistemaFuzzy.h"

using namespace std;

int main()
{
	
	cout << "Calculando pela media" << endl;

	float sujeira = SistemaFuzzy::leSujeira();
	float manchas = SistemaFuzzy::leManchas();
	float resposta = SistemaFuzzy::calculaTempoMedia(sujeira, manchas);
	cout << endl << "O tempo sera " << resposta << " minutos." << endl;
}