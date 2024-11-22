#pragma once
#include "ForceGenerator.h"
#include <vector>

class Wind : public ForceGenerator {
public:
    Wind(Vector3 velocidadViento, float k1, float k2, Vector3 areaMinima, Vector3 areaMaxima, bool modeloSimple = true);

    void aplicarFuerza() override;

private:
    Vector3 velocidadViento; // Velocidad del viento
    float k1, k2;           // Coeficientes de resistencia
    Vector3 areaMinima;      
    Vector3 areaMaxima;
    bool modeloSimple;       // Modelo simple (k2 = 0) o avanzado

    bool estaEnArea(const Vector3& posicion) const;
};
