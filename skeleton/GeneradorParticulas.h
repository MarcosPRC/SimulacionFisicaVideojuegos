#pragma once
#include "Particle.h"
#include <list>
#include <random>
using namespace std;
class GeneradorParticulas
{
private:
	Vector3 posInicial;
	double tiempo;
	list<Particle*> Lparticulas;
	default_random_engine generator;
	char Tipo;
public:
	list<Particle*> GetLparticulas() { return Lparticulas; }
	GeneradorParticulas(Vector3 pos, char tipo) {
		Tipo = tipo;
		posInicial = pos;
		tiempo = 0.0;
	}
	~GeneradorParticulas() {
		for (auto particula : Lparticulas) {
			delete particula;
		}
		Lparticulas.clear();
	}

	void update(double tiempo);
	void destruirparticulas(double tiempo);

	Vector3 distribucionUniforme(Vector3 min, Vector3 max);
	Vector3 distribucionNormal(Vector3 media, double varianza);

	void crearFuente();
	void crearGrifo();
	void crearCohete();
};

