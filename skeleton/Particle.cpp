#include "Particle.h"
#include <iostream>
#include <math.h>

Particle::Particle(physx::PxTransform* pos, Vector3 vel, Vector3 accel) : pose(pos), vel(vel), acceleracion(accel)
{
	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, pose, Vector4(1, 1, 1, 1));
	RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	renderItem = nullptr;
}

void Particle::integrate(double t)
{
	// Actualiza vel
	vel += acceleracion * t;

	// Parte 3, aplicamos damping 
	vel = vel * pow(damping, t);

	// Actualiza pos
	pose->p += vel * t;
}
