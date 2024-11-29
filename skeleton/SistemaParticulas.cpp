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
        new physx::PxTransform(0.0f, 10.0f, 0.0f), 
        Vector3(0, 0, 0),                          
        Vector3(0, 0, 0),                          
        10.0,                                       
        1.0,                                       
        Vector4(1.0, 0.0, 0.0, 1.0)                
    );

    Particle* p2e = new Particle(
        new physx::PxTransform(0.0f, 5.0f, 0.0f),  
        Vector3(0, 0, 0),                          
        Vector3(0, 0, 0),                          
        10.0,                                       
        2.0,                                       
        Vector4(0.0, 0.0, 1.0, 1.0)                
    );

   
    ElasticSpringFG* elasticSpring = new ElasticSpringFG(1.0, 10.0, p1e, p2e);


    _springParticles.push_back(p1);
    _springParticles.push_back(p2);

    _springForceGenerators.push_back(elasticSpring);
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