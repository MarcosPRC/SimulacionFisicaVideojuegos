#include "SistemaParticulas.h"

void SistemaParticulas::borrarGeneradores()
{
	for (auto g : generadores) {
		delete g;
	}
	generadores.clear();
}
