#pragma once
#include <vector>
#include "Vector3D.h"
#include <PxPhysicsAPI.h>
using namespace physx;

class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel);
	~Particle();

	void integrate(double t);
private:
	Vector3D vel;
	physx::PxTransform pose;
	
};

