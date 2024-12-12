#pragma once
#include <vector>
#include "RenderUtils.hpp"
#include "GeneradorParticulas.h"
#include "ForceGenerator.h"
#include "Gravedad.h"
#include "Wind.h"
#include "Torbellino.h"
#include "Particle.h"
#include "SpringForceGenerator.h"
#include "ElasticSpringFG.h"
#include "SistemaSolidoRigido.h"
//#include "Explosion.h"
using namespace std;
class SistemaParticulas
{
private:
    
    
public:
    vector<GeneradorParticulas*> generadores;
    Vector3 pos;
    SistemaSolidoRigido* sistemaSo;
    Particle* p2;
    Particle* p1;
    SpringForceGenerator* _spring1;
    SpringForceGenerator* _spring2;
    ForceGenerator* gravedad = nullptr;
    ForceGenerator* viento = nullptr;
    ForceGenerator* torbellino = nullptr;
    SpringForceGenerator* resorte;
    Particle* particula;
    std::vector<Particle*> _springParticles;
    std::vector<SpringForceGenerator*>  _springForces;
    bool muelle1 = false; 
    bool muelle2 = false;
    double tiempoRestanteFuerza; // Duracion de la fuerza temporal
    Vector3 fuerzaTemporal; // Fuerza temporal aplicada
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
    void cambio(bool izq) {
        if (izq)
        {
            pos = Vector3(pos.x, pos.y, pos.z -2);
        }
        else {
            pos = Vector3(pos.x, pos.y, pos.z  +2);
        }
        
    }
	void update(double tiempo) {

		for (auto e : generadores) {
			e->update(tiempo);
		}
        //gravedad->aplicarFuerza();
        /*if (muelle1)
        {
           
            resorte->actualizarFuerza(particula);
            if (tiempoRestanteFuerza > 0.0) {
                particula->aplicarFuerza(fuerzaTemporal);
                tiempoRestanteFuerza -= tiempo;
            }
            particula->integrate(tiempo);
        }*/
        
        //viento->aplicarFuerza();
        //torbellino->aplicarFuerza();
        /*if (explosion) {
            explosion->aplicarFuerza();
            explosion->actualizarTiempo(static_cast<float>(tiempo));
        }*/
	}

    void añadirGenerador(char l, SistemaSolidoRigido*sis) {
         pos = Vector3(sis->player[0]->Getpos().x, sis->player[0]->Getpos().y, sis->player[0]->Getpos().z);
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
                pos = Vector3(sis->player[0]->Getpos().x, sis->player[0]->Getpos().y, sis->player[0]->Getpos().z);
            //borrarGeneradores();
            generadores.push_back(new GeneradorParticulas(pos, 'g'));
            generadores.back()->crearGrifo(pos);
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
    void GenerateSpringDemo();
    void GenerateElasticSpringDemo();

    void SistemaParticulas::aplicarFuerzaTemporal(const Vector3& fuerza, double duracion) {
        fuerzaTemporal = fuerza;
        tiempoRestanteFuerza = duracion;
    }

    void SistemaParticulas::modificarConstanteMuelle(double incremento) {
        resorte->nuevo_k(resorte->getK() + incremento);
    }
};

