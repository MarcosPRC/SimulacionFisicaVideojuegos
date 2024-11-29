#include "SpringForceGenerator.h"
#include "core.hpp"

SpringForceGenerator::SpringForceGenerator(double k, double l, Particle* other) :
	_k(k), _length(l), _other(other)
{
}

void SpringForceGenerator::actualizarFuerza(Particle* particle) const
{
	Vector3 relativePos = _other->getPosition() - particle->getPosition();
	Vector3 force = Vector3(0, 0, 0);

	const float length = relativePos.normalize();
	const float dX = length - _length;

	force = relativePos * _k * dX;

	particle->aplicarFuerza(force);
}

void SpringForceGenerator::aplicarFuerza() const {
	// En esta implementación, simplemente actualizamos la fuerza del resorte
	if (_other) {
		actualizarFuerza(_other);
	}
}