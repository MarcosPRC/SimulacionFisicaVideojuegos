#pragma once
#include <list>
#include "GeneradorParticulas.h"
class ForceGenerator
{
protected:
	std::list<GeneradorParticulas*> partsis;
public:
	ForceGenerator() = default;

	virtual void aplicarFuerza() = 0;
	void registrarSistema(GeneradorParticulas* ps) { partsis.push_back(ps); }
};

