#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <vector>

using namespace physx;

class WindRigid {
public:
    WindRigid(Vector3 velocidadViento, float k1, float k2, Vector3 areaMinima, Vector3 areaMaxima, bool modeloSimple)
        : velocidadViento(velocidadViento), k1(k1), k2(k2), areaMinima(areaMinima), areaMaxima(areaMaxima), modeloSimple(modeloSimple), activo(true) {}

    // Aplicar fuerza de viento a un sólido rígido
    void aplicarFuerza(PxRigidDynamic* solido) const {
        if (!activo || !estaEnArea(solido->getGlobalPose().p)) return;

        Vector3 diferenciaVelocidad = velocidadViento - Vector3(solido->getLinearVelocity().x,
            solido->getLinearVelocity().y,
            solido->getLinearVelocity().z);
        Vector3 fuerza;

        if (modeloSimple) {
            fuerza = k1 * diferenciaVelocidad;
        }
        else {
            fuerza = k1 * diferenciaVelocidad + k2 * diferenciaVelocidad.magnitude() * diferenciaVelocidad;
        }

        solido->addForce(PxVec3(fuerza.x, fuerza.y, fuerza.z), PxForceMode::eFORCE);
    }

    // Activa o desactiva el viento
    void toggleActivo() { activo = !activo; }
    bool isActivo() const { return activo; }

private:
    Vector3 velocidadViento;
    float k1, k2;           // Coeficientes de resistencia
    Vector3 areaMinima;
    Vector3 areaMaxima;
    bool modeloSimple;       // Modelo simple (k2 = 0) o avanzado
    bool activo;             // Control de activación

    bool estaEnArea(const PxVec3& posicion) const {
        return (posicion.x >= areaMinima.x && posicion.x <= areaMaxima.x &&
            posicion.y >= areaMinima.y && posicion.y <= areaMaxima.y &&
            posicion.z >= areaMinima.z && posicion.z <= areaMaxima.z);
    }
};


