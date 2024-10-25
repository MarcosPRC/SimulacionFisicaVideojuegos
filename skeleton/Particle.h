#pragma once
#include <vector>
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
using namespace physx;

class Particle
{
public:
	Particle(physx::PxTransform* pos, Vector3 vel, Vector3 accel, double vida, Vector4 Color);
	~Particle();

	void integrate(double t);

	Vector3 getPosition() const;
	bool debeDestruirse(double tiempo);
private:
	Vector3 vel;
	physx::PxTransform* pose;
	RenderItem* renderItem = nullptr;
	double tiempoVida;
	double tiempoExistencia;
	const double damping = 0.998;
	Vector3 acceleracion;
	Vector4 Color;
};

