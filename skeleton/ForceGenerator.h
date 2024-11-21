#pragma once
#include <list>
#include "GeneradorParticulas.h"
class ForceGenerator
{
protected:
	std::list<GeneradorParticulas*> partsis;
public:
	ForceGenerator() = default;

	virtual void apply_force() = 0;
	void register_system(GeneradorParticulas* ps) { partsis.push_back(ps); }
};

