#include "Particle.h"
#include <iostream>
#include <math.h>

Particle::Particle(physx::PxTransform* pos, Vector3 vel, Vector3 accel, double vida, Vector4 color) : pose(pos), vel(vel), acceleracion(accel), tiempoVida(vida),Color(color)
{
	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, pose, Color);
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
	tiempoExistencia += t;
}

bool Particle::debeDestruirse(double t) {
	tiempoVida -= t;
	return tiempoVida <= 0;

}

Vector3 Particle::getPosition() const {
	return Vector3(pose->p.x, pose->p.y, pose->p.z);
}