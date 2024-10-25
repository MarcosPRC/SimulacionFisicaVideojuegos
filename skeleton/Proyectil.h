#pragma once
#include "Particle.h"

const double gravedad = 9.8;

class Proyectil
{
private:
    Particle* particula;
    double masaReal;
    double masaEscalada;
    double velocidadEscalada;
    double velocidadReal;
    double gravedadEscalada;

public:
    Proyectil(double velocidadInicial, double masaInicial, Vector3 posicion, Vector3 inicio): masaReal(masaInicial), velocidadReal(velocidadInicial) {

        velocidadEscalada = 10.0;  
        //calcularMasaEscalada();   // Calcula la masa escalada.
        ajustarGravedad();        // Ajusta la gravedad en función de la velocidad

        Vector3 direccion = posicion;
        direccion.normalize();

        PxTransform* pose = new PxTransform(inicio);  // PxTransform para la posición.
        particula = new Particle(pose, direccion * velocidadEscalada, Vector3(0, -gravedadEscalada, 0),10.0, Vector4(1,1,1,1));
    };

    /*void calcularMasaEscalada() {
        masaEscalada = masaReal * (pow(velocidadReal, 2) / pow(velocidadEscalada, 2));
    }*/

    // ajusta la gravedad escalada segun las velocidades
    void ajustarGravedad() {
        gravedadEscalada = pow(velocidadEscalada, 2) * gravedad / pow(velocidadReal, 2);
    }

    void disparar(double tiempo) {
        particula->integrate(tiempo);
    }


};


