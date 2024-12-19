#pragma once
#include <vector>
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
using namespace physx;
class SpringForceGenerator;
class Particle
{
public:
	Particle(physx::PxTransform* pos, Vector3 vel, Vector3 accel, double vida,double m, Vector4 Color, float tam);
	~Particle();

	void integrate(double t);
	double masa() { return masaa; }
	void setMasa(double m){ masaa = m;}
	void aplicarFuerza(physx::PxVec3& f) { fuerza = f; }
	Vector3 getPosition() const;
	Vector3 getvel() const;
	bool debeDestruirse(double tiempo);
	void añadirFuerzas(SpringForceGenerator* fuerza);
private:
	Vector3 vel;
	Vector3 fuerza;
	physx::PxTransform* pose;
	float Tam;
	RenderItem* renderItem = nullptr;
	double tiempoVida;
	double tiempoExistencia;
	const double damping = 0.998;
	double masaa;
	Vector3 acceleracion;
	Vector4 Color;
	SpringForceGenerator* spring;
};

