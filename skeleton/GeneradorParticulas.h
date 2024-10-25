#pragma once
#include "Particle.h"
#include <list>
using namespace std;
class GeneradorParticulas
{
private:
	Vector3 posInicial;
	double tiempo;
	list<Particle*> Lparticulas;
public:
	GeneradorParticulas(Vector3 pos) {
		posInicial = pos;
		tiempo = 0.0;
	}
	~GeneradorParticulas();

	void update(double tiempo);
	void destruirparticulas();
	void distribucionNormal();
};

