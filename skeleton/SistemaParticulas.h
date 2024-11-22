#pragma once
#include <vector>
#include "RenderUtils.hpp"
#include "GeneradorParticulas.h"
#include "ForceGenerator.h"
#include "Gravedad.h"
#include "Wind.h"
#include "Torbellino.h"
//#include "Explosion.h"
using namespace std;
class SistemaParticulas
{
private:
    vector<GeneradorParticulas*> generadores;
public:
    ForceGenerator* gravedad = nullptr;
    ForceGenerator* viento = nullptr;
    ForceGenerator* torbellino = nullptr;
    //Explosion* explosion = nullptr;
    GeneradorParticulas* generador = nullptr;
    
	SistemaParticulas() {
        gravedad = new Gravedad();
        viento = new Wind(Vector3(10,0, 0), 0.5f, 0.01f, Vector3(-100, -100, -100), Vector3(100, 100, 100), true);
        torbellino = new Torbellino(Vector3(0, 0, 0), Vector3(500, 500, 500), 0.8f);
        //explosion = new Explosion(Vector3(0,0,0),500.0,10.0,1.0);
	}
    ~SistemaParticulas() {
        for (auto generador : generadores)
            delete generador;
    };

	void update(double tiempo) {

		for (auto e : generadores) {
			e->update(tiempo);
		}
        gravedad->aplicarFuerza();
        viento->aplicarFuerza();
        torbellino->aplicarFuerza();
        /*if (explosion) {
            explosion->aplicarFuerza();
            explosion->actualizarTiempo(static_cast<float>(tiempo));
        }*/
	}

    void añadirGenerador(char l) {
        switch (l) {
        case 'f': // Fuente
            borrarGeneradores();
            generador = new GeneradorParticulas(Vector3(0, 0, 0), 'f');
            generadores.push_back(generador);
            gravedad->registrarSistema(generador);
            viento->registrarSistema(generador);
            torbellino->registrarSistema(generador);
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
       // case 'e':
            //borrarGeneradores();
           //generadores.push_back(new GeneradorParticulas(Vector3(0, 0, 0), 'e'));
           //generadores.back()->crearFuente();
           //break;
        default:
            break;
        }
    }
    /*void SistemaParticulas::activarExplosion(Vector3 centro) {
        auto* explosionn = dynamic_cast<Explosion*>(explosion);
        if (explosionn) {
            explosionn->iniciarExplosion();
        }
    }*/
    void borrarGeneradores();
};

