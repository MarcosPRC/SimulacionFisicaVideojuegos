#include "GeneradorParticulas.h"
#include <random>
#include "Particle.h"
void GeneradorParticulas::update(double tiempo) {
	static std::default_random_engine generator;
	//crear particula cada frame
	Vector3 aceleracion(0, -10.0, 0);
	Vector3 velocidad(0,0,0);
	physx::PxTransform* nuevaPos = new physx::PxTransform(posInicial.x, posInicial.y, posInicial.z);
	Particle* nuevaParticula = new Particle(nuevaPos, velocidad, aceleracion);
	Lparticulas.push_back(nuevaParticula);
	//llamar a destruirparticulas para comprobar su tiempo de vida
	destruirparticulas();
}

void GeneradorParticulas::destruirparticulas() {

}