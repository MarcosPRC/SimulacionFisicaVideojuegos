#include "Particle.h"
#include <iostream>
#include <math.h>
#include "SpringForceGenerator.h"
Particle::Particle(physx::PxTransform* pos, Vector3 vel, Vector3 accel, double vida, double m, Vector4 color) : pose(pos), vel(vel), acceleracion(accel), tiempoVida(vida),masaa(m),Color(color)
{
	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, pose, Color);
	fuerza = Vector3(0, 0, 0);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	renderItem = nullptr;
}

void Particle::integrate(double t)
{
	if (spring != nullptr)
	{
		//spring->actualizarFuerza(this);
	}
	// Actualiza vel
	//vel += acceleracion * t;

	// Parte 3, aplicamos damping 
	vel = vel * pow(damping, t);
	vel += fuerza;

	// Actualiza pos
	pose->p += vel * t;
	//std::cout << pose->p.x << std::endl;
	vel -= fuerza;
	tiempoExistencia += t;
}

bool Particle::debeDestruirse(double t) {
	tiempoVida -= t;
	return tiempoVida <= 0;

}
void Particle::añadirFuerzas(SpringForceGenerator* fuerzaaa) {
	spring = fuerzaaa;
}
Vector3 Particle::getPosition() const {
	return Vector3(pose->p.x, pose->p.y, pose->p.z);
}
Vector3 Particle::getvel() const {
	return vel;
}
