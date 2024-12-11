#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include <vector>
#include "SolidoRigido.h"
#include "WindRigid.h"

using namespace physx;

class SistemaSolidoRigido {
private:
    PxScene* gScene;
    PxPhysics* gPhysics;
    PxMaterial* materialBase;

    
    WindRigid* viento;                          

public:
    std::vector<SolidoRigido*> solidosDinamicos; // Sólidos dinámicos
    std::vector<SolidoRigido*> player; // player
    SistemaSolidoRigido(PxScene* scene, PxPhysics* physics, WindRigid* wind)
        : gScene(scene), gPhysics(physics), viento(wind) {
        // Crear material base con coeficientes iniciales
        materialBase = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
    }

    ~SistemaSolidoRigido() {
        limpiarTodosLosSolidos();
    }

    void crearSuelo() {
        PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0, 0, 0 }));
        PxShape* shapeSuelo = CreateShape(PxBoxGeometry(1000, 0.1, 20));
        suelo->attachShape(*shapeSuelo);
        gScene->addActor(*suelo);
        new RenderItem(shapeSuelo, suelo, { 0.545f, 0.271f, 0.075f, 1.0f });
    }

    void crearObstaculoEstatico(const PxVec3& pos, const PxVec3& dimensiones) {
        PxRigidStatic* obstaculo = gPhysics->createRigidStatic(PxTransform(pos));
        PxShape* shapeObstaculo = CreateShape(PxBoxGeometry(dimensiones));
        obstaculo->attachShape(*shapeObstaculo);
        gScene->addActor(*obstaculo);
        new RenderItem(shapeObstaculo, obstaculo, { 0.5f, 0.5f, 0.5f, 1.0f });
    }

    void generarSolidoDinamico(const PxVec3& pos, const PxVec3& dimensiones, PxReal densidad, const PxVec3& velInicial, const PxVec3& velAngular, Vector4 color, bool Player) {
        float volumen = dimensiones.x * dimensiones.y * dimensiones.z * 8;
        double masa = densidad * volumen;

        SolidoRigido* solido = new SolidoRigido(gPhysics, gScene, pos, velInicial, velAngular, dimensiones, masa,color, Player );
        if (Player)
        {

            player.push_back(solido);
        }
        else {
            solidosDinamicos.push_back(solido);
        }
        
    }
    void generarObstaculosConDistancia(const PxVec3& dimensionesPlano, const PxVec3& dimensionesObstaculo,
        float distanciaMinima, PxReal densidad, const Vector4& color)
    {
        // Limites del plano
        float xMin = -dimensionesPlano.x / 2;
        float xMax = dimensionesPlano.x / 2;
        float zMin = -dimensionesPlano.z / 2;
        float zMax = dimensionesPlano.z / 2;

        // Vector para almacenar posiciones ya generadas
        std::vector<PxVec3> posicionesGeneradas;

        // Generar obstáculos aleatoriamente
        for (int i = 0; i < 100; ++i) {
            PxVec3 posicion;
            bool posicionValida;

            do {
                posicionValida = true;
                // Generar posición aleatoria dentro de los límites del plano
                posicion = {
                    xMin + static_cast<float>(rand()) / RAND_MAX * (xMax - xMin),
                    dimensionesObstaculo.y / 2, // Elevar obstáculo para que repose sobre el suelo
                    zMin + static_cast<float>(rand()) / RAND_MAX * (zMax - zMin)
                };

                // Verificar que la posición cumple con la distancia mínima respecto a las existentes
                for (const auto& posExistente : posicionesGeneradas) {
                    if ((posicion - posExistente).magnitude() < distanciaMinima || posicion.x > 40) {
                        posicionValida = false;
                        break;
                    }
                }

            } while (!posicionValida);

            // Guardar posición válida
            posicionesGeneradas.push_back(posicion);

            // Crear el sólido dinámico en la posición generada
            generarSolidoDinamico(posicion, dimensionesObstaculo, densidad, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, color, false);
        }
    }


    void aplicarFuerzas() {
        for (auto solido : solidosDinamicos) {
            viento->aplicarFuerza(solido->getActor());
        }
    }

    void limpiarTodosLosSolidos() {
        for (SolidoRigido* solido : solidosDinamicos) {
            delete solido;
        }
        solidosDinamicos.clear();
    }

    void toggleViento() {
        viento->toggleActivo();
    }
};
