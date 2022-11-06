
#include <iostream>
#include <math.h>

using namespace std;

#define TEMPO_MC = 0;
#define TEMPO_C = 10;
#define TEMPO_M = 25;
#define TEMPO_L = 40;
#define TEMPO_ML = 60;

#ifndef SISTEMAFUZZY_H

#define SISTEMAFUZZY_H

class SistemaFuzzy
{
public:

	static float leSujeira();
	static float leManchas();

	static float calculaSujeiraPequenoGrau(float sujeira);
	static float calculaSujeiraMedioGrau(float sujeira);
	static float calculaSujeiraGrandeGrau(float sujeira);

	static float calculaManchasPequenoGrau(float manchas);
	static float calculaManchasMedioGrau(float manchas);
	static float calculaManchasGrandeGrau(float manchas);

	/*
	static float calculaTempoMuitoCurto(float tempo);
	static float calculaTempoCurto(float tempo);
	static float calculaTempoMedio(float tempo);
	static float calculaTempoLongo(float tempo);
	static float calculaTempoMuitoLongo(float tempo);
	*/

	static float calculaX1(float delta, float y, float inicio);
	static float calculaX2(float delta, float y, float fim);

	static float regra_SP_MP_MC(float sujeira, float manchas);
	static float regra_SP_MM_M(float sujeira, float manchas);
	static float regra_SP_MG_L(float sujeira, float manchas);
	static float regra_SM_MP_C(float sujeira, float manchas);
	static float regra_SM_MM_M(float sujeira, float manchas);
	static float regra_SM_MG_L(float sujeira, float manchas);
	static float regra_SG_MP_M(float sujeira, float manchas);
	static float regra_SG_MM_L(float sujeira, float manchas);
	static float regra_SG_MG_ML(float sujeira, float manchas);

	static float calculaTempoMedia(float sujeira, float manchas);

};

#endif 