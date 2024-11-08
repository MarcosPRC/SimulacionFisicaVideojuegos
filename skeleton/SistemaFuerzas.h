#pragma once
#include <vector>
#include "RenderUtils.hpp"
#include "GeneradorFuerzas.h"
class SistemaFuerzas
{
private:
    vector<GeneradorFuerzas*> generadores;

public:
	SistemaFuerzas() {

	}
    ~SistemaFuerzas() {
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
        case 'g': // gravedad
            borrarGeneradores();
            //generadores.push_back(new GeneradorParticulas(Vector3(0, 0, 0), 'f'));
            //generadores.back()->crearFuente();
            break;
        case 'v': // viento
            borrarGeneradores();
            //generadores.push_back(new GeneradorParticulas(Vector3(0, 5, 0), 'g'));
            //generadores.back()->crearGrifo();
            break;
        case 't': // tornado
            borrarGeneradores();
            //generadores.push_back(new GeneradorParticulas(Vector3(0, 0, 0), 'c'));
           // generadores.back()->crearCohete();
            break;
        case 'e': // explosion
            borrarGeneradores();
            //generadores.push_back(new GeneradorParticulas(Vector3(0, 0, 0), 'c'));
           // generadores.back()->crearCohete();
            break;
        default:
            break;
        }
    }
    void borrarGeneradores() {
        for (auto g : generadores) {
            delete g;
        }
        generadores.clear();
    }
};

