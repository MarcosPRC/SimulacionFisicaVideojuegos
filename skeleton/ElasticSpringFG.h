#pragma once
#include "SpringForceGenerator.h"
#include "Particle.h"
#include "core.hpp"

class ElasticSpringFG : public SpringForceGenerator {
public:
    ElasticSpringFG(double k, double restingLength, Particle* p1, Particle* p2);
    ~ElasticSpringFG();
    void actualizarFuerza() const;
private:
    double _k;
    Particle* _p1;
    Particle* _p2; 
    double _restingLength;
};



