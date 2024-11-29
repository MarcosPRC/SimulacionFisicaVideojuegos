#pragma once
#include "ForceGenerator.h"
#include "Particle.h"
class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double l, Particle* other);

	virtual ~SpringForceGenerator() = default;

	void actualizarFuerza(Particle* particle) const;

	inline void nuevo_k(const double k) { _k = k; }
	double getK() { return _k; }
	virtual void aplicarFuerza() const ;

protected:
	double _k;
	double _length;
	Particle* _other;
};

