#include "ElasticSpringFG.h"
#include <cmath>

ElasticSpringFG::ElasticSpringFG(double k, double restingLength, Particle* p1, Particle* p2)
    : SpringForceGenerator(k, restingLength, p1),_k(k), _p1(p1), _p2(p2) {}

ElasticSpringFG::~ElasticSpringFG() {}

void ElasticSpringFG::actualizarFuerza() const {
    if (_p1 && _p2){
        Vector3 diff = _p1->getPosition() - _p2->getPosition();
        double length = diff.magnitude();

        // Aplicar fuerza solo si la longitud supera la de reposo
        if (length > _restingLength) {

            Vector3 force = diff / length;
            double magnitude = -_k * (length - _restingLength);


            force *= magnitude;
            _p1->aplicarFuerza(force);
            _p2->aplicarFuerza(-force);
        }
    }

    
    
}

