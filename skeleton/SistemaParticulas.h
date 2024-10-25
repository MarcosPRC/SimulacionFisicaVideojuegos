#pragma once
#include <vector>
#include "RenderUtils.hpp"
#include "GeneradorParticulas.h"
using namespace std;
class SistemaParticulas
{
private:
    vector<GeneradorParticulas*> generadores;
public:
	SistemaParticulas() {
		
	}
    ~SistemaParticulas() {
        for (auto generador : generadores)
            delete generador;
    };

	void update(double tiempo) {

		for (auto e : generadores) {
			e->update(tiempo);
		}
	}

    void añadirGenerador(char l) {
        switch (l) {
        case 'f': // Fuente
            borrarGeneradores();
            generadores.push_back(new GeneradorParticulas(Vector3(0, 0, 0),'f'));
            generadores.back()->crearFuente();
            break;
        case 'g': // Grifo
            borrarGeneradores();
            generadores.push_back(new GeneradorParticulas(Vector3(0, 5, 0), 'g'));
            generadores.back()->crearGrifo();
            break;
        case 'c': // Cohete
            borrarGeneradores();
            generadores.push_back(new GeneradorParticulas(Vector3(0, 0, 0), 'c'));
            generadores.back()->crearCohete();
            break;
        default:
            break;
        }
    }

    void borrarGeneradores();
};

