#pragma once
#include <vector>
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
using namespace physx;

class Particle
{
public:
	Particle(physx::PxTransform* pos, Vector3 vel, Vector3 accel);
	~Particle();

	void integrate(double t);
private:
	Vector3 vel;
	physx::PxTransform* pose;
	RenderItem* renderItem = nullptr;

	const double damping = 0.998;
	Vector3 acceleracion;
};

