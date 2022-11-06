#include "SistemaFuzzy.h"

float SistemaFuzzy::leSujeira()
{
	bool flag = false;
	float sujeira;
	do {
		cout << endl << "Digite o nivel de sujeira (de 0 a 100)" << endl;
		cin >> sujeira;
		if (sujeira >= 0 && sujeira <= 100)
			flag = true;
		else
			cout << endl << "Valor invalido, digite novamente.";
	} while (!flag);
	return sujeira;
}

float SistemaFuzzy::leManchas()
{
	bool flag = false;
	float manchas;
	do {
		cout << endl << "Digite o nivel de manchas (de 0 a 100)" << endl;
		cin >> manchas;
		if (manchas >= 0 && manchas <= 100)
			flag = true;
		else
			cout << endl << "Valor invalido, digite novamente.";
	} while (!flag);
	return manchas;
}

float SistemaFuzzy::calculaSujeiraPequenoGrau(float sujeira)
{
	if (sujeira == 0)
		return 1;
	else if (sujeira < 50)
		return (50 - sujeira) / 50;
	else
		return 0;
}

float SistemaFuzzy::calculaSujeiraMedioGrau(float sujeira)
{

	if (sujeira == 0)
		return 0;

	//subida: (x-início) / delta
	else if (sujeira > 0 && sujeira < 50)
		return (sujeira) / 50;

	else if (sujeira == 50)
		return 1;

	//descida: (final-x) / delta
	else if (sujeira < 100)
		return (100 - sujeira) / 50;

	else
		return 0;
}

float SistemaFuzzy::calculaSujeiraGrandeGrau(float sujeira)
{
	if (sujeira <= 50)
		return 0;
	else if (sujeira < 100)
		return (sujeira - 50) / 50;
	else
		return 1;
}

float SistemaFuzzy::calculaManchasPequenoGrau(float manchas)
{
	if (manchas == 0)
		return 1;
	else if (manchas < 50)
		return (50 - manchas) / 50;
	else
		return 0;
}

float SistemaFuzzy::calculaManchasMedioGrau(float manchas)
{
	if (manchas == 0)
		return 0;

	//subida: (x-início) / delta
	else if (manchas > 0 && manchas < 50)
		return (manchas) / 50;

	else if (manchas == 50)
		return 1;

	//descida: (final-x) / delta
	else if (manchas < 100)
		return (100 - manchas) / 50;

	else
		return 0;
}

float SistemaFuzzy::calculaManchasGrandeGrau(float manchas)
{
	if (manchas < 50)
		return 0;
	else if (manchas < 100)
		return (manchas - 50) / 50;
	else
		return 1;
}

/*
float SistemaFuzzy::calculaTempoMuitoCurto(float tempo)
{
	//0 - 10
	if (tempo == 0)
		return 1;
	else if (tempo < 10)
		return (tempo) / 10;
	else
		return 0;
}

float SistemaFuzzy::calculaTempoCurto(float tempo)
{
	//0 - 10 / 10 - 25
	if (tempo == 0)
		return 0;
	else if (tempo > 0 && tempo < 10)
		return tempo / 10;
	else if (tempo == 10)
		return 1;
	else if (tempo < 25)
		return (25 - tempo) / 15;
	else
		return 0;
}

float SistemaFuzzy::calculaTempoMedio(float tempo)
{
	//10 - 25 / 25 - 40
	if (tempo == 10)
		return 0;
	else if (tempo > 10 && tempo < 25)
		return (tempo - 10) / 15;
	else if (tempo == 25)
		return 1;
	else if (tempo < 40)
		return (40 - tempo) / 15;
	else
		return 0;
}

float SistemaFuzzy::calculaTempoLongo(float tempo)
{
	//25 - 40 / 40 - 60
	if (tempo == 25)
		return 0;
	else if (tempo > 25 && tempo < 40)
		return (tempo - 25) / 15;
	else if (tempo == 40)
		return 1;
	else if (tempo < 60)
		return (60 - tempo) / 20;
	else
		return 0;
}

float SistemaFuzzy::calculaTempoMuitoLongo(float tempo)
{
	//40 - 60
	if (tempo == 40)
		return 0;
	else if (tempo < 60)
		return (60 - tempo) / 20;
	else if (tempo >= 60)
		return 1;
}
*/

//nas regras de pertinência, haverá um x1 e um x2
//x1 = delta1 y + inicio
//x2 = (delta2 y - fim) * -1

float SistemaFuzzy::calculaX1(float delta, float y, float inicio)
{
	if (y == 0)
		return 0;
	else
		return (delta * y) + inicio;
}

float SistemaFuzzy::calculaX2(float delta, float y, float fim)
{
	if (y == 0)
		return 0;
	else
		return ((delta * y) - fim) * -1;
}

//MC -> 0 - 10
//C -> 0 - 10 / 10 - 25
//M -> 10 - 25 / 25 - 40
//L -> 25 - 40 / 40 - 60
//ML -> 40 - 60

float SistemaFuzzy::regra_SP_MP_MC(float sujeira, float manchas)
{
	//01 - se pouca sujeira e pouca mancha, então muito curto
	//MC -> 0 - 10

	float y =  min(calculaSujeiraPequenoGrau(sujeira), calculaManchasPequenoGrau(manchas));
	float x1 = 0;
	float x2 = calculaX2(10, y, 10);
	if (y == 0)
		return 0;
	else
		return (x1 + x2) / 2;
}

float SistemaFuzzy::regra_SP_MM_M(float sujeira, float manchas)
{
	//02 - se pouca sujeira e media mancha, entao medio
	//M -> 10 - 25 / 25 - 40

	float y = min(calculaSujeiraPequenoGrau(sujeira), calculaManchasMedioGrau(manchas));
	float x1 = calculaX1(15, y, 10);
	float x2 = calculaX2(15, y, 40);
	return (x1 + x2) / 2;
}

float SistemaFuzzy::regra_SP_MG_L(float sujeira, float manchas)
{
	//03 - se pouca sujeira e grande mancha, entao longo
	//L -> 25 - 40 / 40 - 60

	float y = min(calculaSujeiraPequenoGrau(sujeira), calculaManchasGrandeGrau(manchas));
	float x1 = calculaX1(15, y, 25);
	float x2 = calculaX2(20, y, 60);
	return (x1 + x2) / 2;
}

float SistemaFuzzy::regra_SM_MP_C(float sujeira, float manchas)
{
	//04 - se media sujeira e pouca mancha, entao curto
	//C -> 0 - 10 / 10 - 25

	float y = min(calculaSujeiraMedioGrau(sujeira), calculaManchasPequenoGrau(manchas));
	float x1 = calculaX1(10, y, 0);
	float x2 = calculaX2(15, y, 25);
	return (x1 + x2) / 2;
}

float SistemaFuzzy::regra_SM_MM_M(float sujeira, float manchas)
{
	//05 - se media sujeira e media mancha, entao medio
	//M -> 10 - 25 / 25 - 40

	float y = min(calculaSujeiraMedioGrau(sujeira), calculaManchasMedioGrau(manchas));
	float x1 = calculaX1(15, y, 10);
	float x2 = calculaX2(15, y, 40);
	return (x1 + x2) / 2;
}

float SistemaFuzzy::regra_SM_MG_L(float sujeira, float manchas)
{
	//06 - se media sujeira e grande mancha, entao longo
	//L -> 25 - 40 / 40 - 60

	float y = min(calculaSujeiraMedioGrau(sujeira), calculaManchasGrandeGrau(manchas));
	float x1 = calculaX1(15, y, 25);
	float x2 = calculaX2(20, y, 60);
	return (x1 + x2) / 2;
}

float SistemaFuzzy::regra_SG_MP_M(float sujeira, float manchas)
{
	//07 - se grande sujeira e pouca mancha, entao medio
	//M -> 10 - 25 / 25 - 40

	float y = min(calculaSujeiraGrandeGrau(sujeira), calculaManchasPequenoGrau(manchas));
	float x1 = calculaX1(15, y, 10);
	float x2 = calculaX2(15, y, 40);
	return (x1 + x2) / 2;
}

float SistemaFuzzy::regra_SG_MM_L(float sujeira, float manchas)
{
	//08 - se grande sujeira e media mancha, entao longo
	//L -> 25 - 40 / 40 - 60

	float y = min(calculaSujeiraGrandeGrau(sujeira), calculaManchasMedioGrau(manchas));
	float x1 = calculaX1(15, y, 25);
	float x2 = calculaX2(20, y, 60);
	return (x1 + x2) / 2;
}

float SistemaFuzzy::regra_SG_MG_ML(float sujeira, float manchas)
{
	//09 - se grande sujeira e grande mancha, entao muito longo
	//ML -> 40 - 60

	float y = min(calculaSujeiraGrandeGrau(sujeira), calculaManchasGrandeGrau(manchas));
	float x1 = calculaX1(20, y, 40);
	float x2 = 60;
	if (y == 0)
		return 0;
	else
		return (x1 + x2) / 2;
}

float SistemaFuzzy::calculaTempoMedia(float sujeira, float manchas)
{
	float tempo = 0;
	int aux = 0;

	cout << endl << endl << "Se SP E MP entao MC -> " << regra_SP_MP_MC(sujeira, manchas);
	cout << endl << "Se SP E MM entao M -> " << regra_SP_MM_M(sujeira, manchas);
	cout << endl << "Se SP E MG entao L -> " << regra_SP_MG_L(sujeira, manchas);
	cout << endl << "Se SM E MP entao C -> " << regra_SM_MP_C(sujeira, manchas);
	cout << endl << "Se SM E MM entao M -> " << regra_SM_MM_M(sujeira, manchas);
	cout << endl << "Se SM E MG entao L -> " << regra_SM_MG_L(sujeira, manchas);
	cout << endl << "Se SG E MP entao M -> " << regra_SG_MP_M(sujeira, manchas);
	cout << endl << "Se SG E MM entao L -> " << regra_SG_MM_L(sujeira, manchas);
	cout << endl << "Se SG e MG entao ML -> " << regra_SG_MG_ML(sujeira, manchas) << endl;

	if (regra_SP_MP_MC(sujeira, manchas))
	{
		aux++;
		tempo += regra_SP_MP_MC(sujeira, manchas);
	}

	if (regra_SP_MM_M(sujeira, manchas))
	{
		aux++;
		tempo += regra_SP_MM_M(sujeira, manchas);
	}

	if (regra_SP_MG_L(sujeira, manchas))
	{
		aux++;
		tempo += regra_SP_MG_L(sujeira, manchas);
	}

	if (regra_SM_MP_C(sujeira, manchas))
	{
		aux++;
		tempo += regra_SM_MP_C(sujeira, manchas);
	}

	if (regra_SM_MM_M(sujeira, manchas))
	{
		aux++;
		tempo += regra_SM_MM_M(sujeira, manchas);
	}

	if (regra_SM_MG_L(sujeira, manchas))
	{
		aux++;
		tempo += regra_SM_MG_L(sujeira, manchas);
	}

	if (regra_SG_MP_M(sujeira, manchas))
	{
		aux++;
		tempo += regra_SG_MP_M(sujeira, manchas);
	}

	if (regra_SG_MM_L(sujeira, manchas))
	{
		aux++;
		tempo += regra_SG_MM_L(sujeira, manchas);
	}

	if (regra_SG_MG_ML(sujeira, manchas))
	{
		aux++;
		tempo += regra_SG_MG_ML(sujeira, manchas);
	}
	
	if (aux == 0)
		return 0;
	else
		return tempo/aux;
}