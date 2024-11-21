#pragma once
#include <vector>
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
using namespace physx;

class Particle
{
public:
	Particle(physx::PxTransform* pos, Vector3 vel, Vector3 accel, double vida,double m, Vector4 Color);
	~Particle();

	void integrate(double t);
	double masa() { return masaa; }
	void apply_force(physx::PxVec3& f) { fuerza = f; }
	Vector3 getPosition() const;
	bool debeDestruirse(double tiempo);

private:
	Vector3 vel;
	Vector3 fuerza;
	physx::PxTransform* pose;
	RenderItem* renderItem = nullptr;
	double tiempoVida;
	double tiempoExistencia;
	const double damping = 0.998;
	double masaa;
	Vector3 acceleracion;
	Vector4 Color;
};

