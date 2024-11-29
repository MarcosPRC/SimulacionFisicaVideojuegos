#pragma once
#include "SpringForceGenerator.h"
#include "Particle.h"
#include "core.hpp"

class ElasticSpringFG : public SpringForceGenerator {
public:
    ElasticSpringFG(double k, double restingLength, const Vector3& anchor_pos);
    ~ElasticSpringFG();
};



