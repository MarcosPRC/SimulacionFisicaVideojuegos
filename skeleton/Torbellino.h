#pragma once
#include "ForceGenerator.h"
#include <cmath>

class Torbellino : public ForceGenerator {

public:
        Torbellino(Vector3 centro, Vector3 areaInfluencia, float intensidad);

        void aplicarFuerza() override;

private:
        Vector3 centroTorbellino; 
        Vector3 areaInfluencia;   
        float intensidad;         

        bool estaEnArea(const Vector3& posicion) const;

};


