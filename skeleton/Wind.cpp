
#include "Wind.h"
#include "Particle.h"
#include <cmath>
using namespace std;
Wind::Wind(Vector3 velocidadVient, float k1_, float k2_, Vector3 areaMinim, Vector3 areaMaxim, bool modeloSimpl)
    : velocidadViento(velocidadVient), k1(k1_), k2(k2_), areaMinima(areaMinim), areaMaxima(areaMaxim), modeloSimple(modeloSimpl) {}

void Wind::aplicarFuerza() const {
    for (auto ps : partsis) {
        for (auto p : ps->GetLparticulas()) {
            if (estaEnArea(p->getPosition())) {
                Vector3 diferenciaVelocidad = velocidadViento - p->getvel();
                    Vector3 fuerza;

                    if (modeloSimple) {
                        fuerza = k1 * diferenciaVelocidad;
                    }
                    else {
                        fuerza = k1 * diferenciaVelocidad + k2 * diferenciaVelocidad.magnitude() * diferenciaVelocidad;
                    }

                p->aplicarFuerza(fuerza);
            }

            
        }
    }
}

bool Wind::estaEnArea(const Vector3& posicion) const {
    return (posicion.x >= areaMinima.x && posicion.x <= areaMaxima.x &&
        posicion.y >= areaMinima.y && posicion.y <= areaMaxima.y &&
        posicion.z >= areaMinima.z && posicion.z <= areaMaxima.z);
}
