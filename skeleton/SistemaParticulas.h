#pragma once
#include <vector>
#include "RenderUtils.hpp"
#include "GeneradorParticulas.h"
#include "ForceGenerator.h"
#include "Gravedad.h"
using namespace std;
class SistemaParticulas
{
private:
    vector<GeneradorParticulas*> generadores;
public:
    ForceGenerator* gravedad = nullptr;
    GeneradorParticulas* generador = nullptr;
	SistemaParticulas() {
        gravedad = new Gravedad();
	}
    ~SistemaParticulas() {
        for (auto generador : generadores)
            delete generador;
    };

	void update(double tiempo) {

		for (auto e : generadores) {
			e->update(tiempo);
		}
        gravedad->apply_force();
	}

    void añadirGenerador(char l) {
        switch (l) {
        case 'f': // Fuente
            borrarGeneradores();
            generador = new GeneradorParticulas(Vector3(0, 0, 0), 'f');
            generadores.push_back(generador);
            gravedad->register_system(generador);
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

