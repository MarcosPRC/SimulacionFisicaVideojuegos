#include "ElasticSpringFG.h"
#include <cmath>

ElasticSpringFG::ElasticSpringFG(double k, double restingLength,const Vector3& anchor_pos)
    : SpringForceGenerator(k, restingLength, nullptr){
    
    _other = new Particle(new physx::PxTransform(anchor_pos.x, anchor_pos.y, anchor_pos.z), { 0,0,0 }, { 0,0,0 }, 20.0, 1e6, { 0,1,1,1 },0.5);
}

ElasticSpringFG::~ElasticSpringFG() {
    delete _other;
}

