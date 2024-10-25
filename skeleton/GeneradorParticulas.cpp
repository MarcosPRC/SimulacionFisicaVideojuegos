#include "GeneradorParticulas.h"
#include <random>
#include <iostream>
void GeneradorParticulas::update(double tiempo) {
    switch (Tipo)
    {
    case 'g':
        crearGrifo();
        break;
    case 'f':

        crearFuente();
        break;
    default:
        break;
    }
    for (auto p : Lparticulas) {
        p->integrate(tiempo);
    }

    destruirparticulas(tiempo);
}
//distribuciones
Vector3 GeneradorParticulas::distribucionUniforme(Vector3 min, Vector3 max) {
    uniform_real_distribution<double> distribucionX(min.x, max.x);
    uniform_real_distribution<double> distribucionY(min.y, max.y);
    uniform_real_distribution<double> distribucionZ(min.z, max.z);
    return Vector3(distribucionX(generator), distribucionY(generator), distribucionZ(generator));
}

Vector3 GeneradorParticulas::distribucionNormal(Vector3 media, double varianza) {
    normal_distribution<double> x(media.x, varianza);
    normal_distribution<double> y(media.y, varianza);
    normal_distribution<double> z(media.z, varianza);

    return Vector3(x(generator), y(generator), z(generator));
}

//tipos
void GeneradorParticulas::crearFuente() {
    Vector3 aceleracion(0, -10.0, 0);
    Vector3 velMin(-2, 10, -2);
    Vector3 velMax(2, 40, 2);
    Vector3 velocidad = distribucionUniforme(velMin, velMax);
    physx::PxTransform* nuevaPos = new physx::PxTransform(posInicial.x, posInicial.y, posInicial.z);
    Particle* nuevaParticula = new Particle(nuevaPos, velocidad, aceleracion, 2.0, Vector4(1,0,1,1));
    Lparticulas.push_back(nuevaParticula);
}

void GeneradorParticulas::crearGrifo() {
    Vector3 posVariada = posInicial + distribucionNormal(Vector3(0,0,0), 0.5); 
    Vector3 aceleracion(0, -10.0, 0);
    Vector3 velocidad = distribucionNormal(velocidad, 1.0); 
    physx::PxTransform* nuevaPos = new physx::PxTransform(posVariada.x, posVariada.y, posVariada.z);
    Particle* nuevaParticula = new Particle(nuevaPos, velocidad, aceleracion, 5.0, Vector4(0.7, 0.7, 1, 1));
    Lparticulas.push_back(nuevaParticula);
}

double numeroAleatorioEntre0y1() {
    static std::default_random_engine generador(std::random_device{}());
    std::uniform_real_distribution<double> distribucion(0.0, 1.0);
    return distribucion(generador);
}
void GeneradorParticulas::crearCohete() {
    Vector3 aceleracion(0, -10.0, 0);
    Vector3 velocidad(0, 30.0, 0); 
    physx::PxTransform* nuevaPos = new physx::PxTransform(posInicial.x, posInicial.y, posInicial.z);
    Particle* cohete = new Particle(nuevaPos, velocidad, aceleracion, 3.0, Vector4(0, 0, 0, 1));
    Lparticulas.push_back(cohete);
    Vector3 posExplosion = cohete->getPosition();

        for (int i = 0; i < 150; ++i) {
            Vector3 velocidadExplosion = distribucionNormal(Vector3(10, 10, 10), 5.0);
            physx::PxTransform* nuevaPosExplosion = new physx::PxTransform(posExplosion.x, posExplosion.y, posExplosion.z);
            Particle* particulaExplosion = new Particle(nuevaPosExplosion, velocidadExplosion, Vector3(0, -10.0, 0), 5.0, Vector4(numeroAleatorioEntre0y1(),numeroAleatorioEntre0y1(), numeroAleatorioEntre0y1(), 1.0));
            Lparticulas.push_back(particulaExplosion);
        }
}

void GeneradorParticulas::destruirparticulas(double timepo) {
    for (auto it = Lparticulas.begin(); it != Lparticulas.end();) {
        if ((*it)->debeDestruirse(timepo)) {

            delete* it;
            it = Lparticulas.erase(it);
        }
        else {
            ++it;
        }
    }
}