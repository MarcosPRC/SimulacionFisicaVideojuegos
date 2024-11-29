#include "Torbellino.h"
#include "Particle.h"

Torbellino::Torbellino(Vector3 centro, Vector3 areaInfluencia, float intensidad)
    : centroTorbellino(centro), areaInfluencia(areaInfluencia), intensidad(intensidad) {}

void Torbellino::aplicarFuerza() const {
    for (auto ps : partsis) {
        for (auto p : ps->GetLparticulas()) {
            if (estaEnArea(p->getPosition())) {
                const Vector3 posicionParticula = p->getPosition();
                const Vector3 diferencia = posicionParticula - centroTorbellino;

                Vector3 fuerzaTorbellino = {
                    -intensidad * (diferencia.z),
                    intensidad * (50 - diferencia.y),
                    intensidad * (diferencia.x)
                };

                p->aplicarFuerza(fuerzaTorbellino);
            }
        }
    }
}

bool Torbellino::estaEnArea(const Vector3& posicion) const {
    return (posicion.x >= centroTorbellino.x - areaInfluencia.x && posicion.x <= centroTorbellino.x + areaInfluencia.x &&
        posicion.y >= centroTorbellino.y - areaInfluencia.y && posicion.y <= centroTorbellino.y + areaInfluencia.y &&
        posicion.z >= centroTorbellino.z - areaInfluencia.z && posicion.z <= centroTorbellino.z + areaInfluencia.z);
}
