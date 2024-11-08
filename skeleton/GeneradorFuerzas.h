#pragma once
#include <list>
#include <random>
#include <vector>
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
using namespace physx;
using namespace std;
class GeneradorFuerzas
{

private:
	Vector3 posInicial;
	double tiempo;
	default_random_engine generator;
	char Tipo;

public:
	void update(double tiempo);
	void destruirparticulas(double tiempo);

	GeneradorFuerzas(Vector3 pos, char tipo) {
		Tipo = tipo;
		posInicial = pos;
		tiempo = 0.0;
	}
	~GeneradorFuerzas() {
	}
	void CrearGeneradorGravedad();
	void CrearGeneradorviento();
	void CrearGeneradorTorbellino();
	void CrearGeneradorExplosion();
};

