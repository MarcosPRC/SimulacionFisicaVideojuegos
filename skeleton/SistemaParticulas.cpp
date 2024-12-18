#include "SistemaParticulas.h"
#include "SpringForceGenerator.h"
#include "ElasticSpringFG.h"
#include <iostream>

void SistemaParticulas::borrarGeneradores()
{
	for (auto g : generadores) {
		delete g;
	}
	generadores.clear();
}
void SistemaParticulas::GenerateElasticSpringDemo() {
    muelle2 = true;

    Particle* p1e = new Particle(
        new physx::PxTransform(10.0f, 10.0f, 0.0f), 
        Vector3(0, 0, 0),                          
        Vector3(0, 0, 0),                          
        10.0,                                       
        1.0,                                       
        Vector4(1.0, 0.0, 0.0, 1.0)                
    );

    Particle* p2e = new Particle(
        new physx::PxTransform(-10.0f, 10.0f, 0.0f),  
        Vector3(0, 0, 0),                          
        Vector3(0, 0, 0),                          
        10.0,                                       
        2.0,                                       
        Vector4(0.0, 0.0, 1.0, 1.0)                
    );

    SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2e);
    SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1e);
    _springParticles.push_back(p1e);
    _springParticles.push_back(p2e);

    p1e->añadirFuerzas(f1);
    p2e->añadirFuerzas(f2);
    //
    Particle* p3e = new Particle(
        new physx::PxTransform(-10.0f, 20.0f, 0.0f),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        10.0,
        0.85,
        Vector4(0.0, 0.0, 1.0, 1.0)
    );

    ElasticSpringFG* f3 = new ElasticSpringFG(1, 10,{10.0,20.0,0.0});

    
    _springParticles.push_back(p3e);
    p3e->añadirFuerzas(f3);

}
void SistemaParticulas::GenerateSpringDemo() {
    muelle1 = true;
    // Crear la partícula
    physx::PxTransform* posicion = new physx::PxTransform(0.0f, 10.0f, 0.0f);
    particula = new Particle(posicion, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 60.0, 1.0, Vector4(0.7, 0.7, 1, 1));


    // Crear el resorte conectado a un punto fijo
    resorte = new SpringForceGenerator(10.0, 5.0, new Particle(new physx::PxTransform(0.0f, 15.0f, 0.0f), Vector3(0.0f), Vector3(0.0f), 0.0f, 0.0f, Vector4(1, 0, 0, 1))); // Longitud reposo = 5.0, k = 10.0

    // Inicializar la fuerza temporal
    fuerzaTemporal = Vector3(0.0f, 0.0f, 0.0f);
}