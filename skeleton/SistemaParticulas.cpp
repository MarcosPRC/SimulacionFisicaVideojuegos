#include "SistemaParticulas.h"
#include "SpringForceGenerator.h"
#include <iostream>

void SistemaParticulas::borrarGeneradores()
{
	for (auto g : generadores) {
		delete g;
	}
	generadores.clear();
}
void SistemaParticulas::GenerateSpringDemo() {
    // Creamos dos partículas iniciales para el muelle
    physx::PxTransform* pos = new physx::PxTransform(-10.0, 10.0, 0.0);
    physx::PxTransform* pos2 = new physx::PxTransform(10.0, 10.0, 0.0);
    p1 = new Particle(pos,Vector3(0,0,0),Vector3(0,0,0),30.0,1.0,Vector4(0.7,0.7,0.7,1));
    p1 = new Particle(pos2, Vector3(0, 0, 0), Vector3(0, 0, 0), 30.0, 1.0, Vector4(0.7, 0.7, 1, 1));

    // Establecemos la masa de la segunda partícula
    p2->setMasa(2.0f);

    // Creamos dos generadores de fuerza de muelle (uno para cada dirección)
    _spring1 = new SpringForceGenerator(1.0, 10.0, p2);
    _spring2 = new SpringForceGenerator(1.0, 10.0, p1);
    // Registramos los muelles en las partículas correspondientes
    _spring1->actualizarFuerza(p1);
    _spring2->actualizarFuerza(p2);

    // Guardamos las partículas en el sistema para que se actualicen
    _springParticles.push_back(p1);
    _springParticles.push_back(p2);
}
void SistemaParticulas::GenerateSpringDemo2() {
    muelle1 = true;
    // Crear la partícula
    physx::PxTransform* posicion = new physx::PxTransform(0.0f, 10.0f, 0.0f);
    particula = new Particle(posicion, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 60.0, 1.0, Vector4(0.7, 0.7, 1, 1));


    // Crear el resorte conectado a un punto fijo
    resorte = new SpringForceGenerator(10.0, 5.0, new Particle(new physx::PxTransform(0.0f, 15.0f, 0.0f), Vector3(0.0f), Vector3(0.0f), 0.0f, 0.0f, Vector4(1, 0, 0, 1))); // Longitud reposo = 5.0, k = 10.0

    // Inicializar la fuerza temporal
    fuerzaTemporal = Vector3(0.0f, 0.0f, 0.0f);
}