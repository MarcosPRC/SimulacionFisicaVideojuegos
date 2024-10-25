#pragma once
#include <vector>
#include "RenderUtils.hpp"
#include "GeneradorParticulas.h"
using namespace std;
class SistemaParticulas
{
private:
	vector<GeneradorParticulas*> generadorParticulas;
public:
	SistemaParticulas(char l) {
		//llamar al generador ingicado
		switch (l)
		{
		case 'f': //fuente
			generadorParticulas.push_back(new GeneradorParticulas(Vector3(0, 0, 0)));
			break;
		default:
			
			break;
		}
		
	}
	~SistemaParticulas();
	void update(double tiempo) {

		for (auto e : generadorParticulas) {
			e->update(tiempo);
		}
	}
};

