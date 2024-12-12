#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include <vector>
#include "SolidoRigido.h"
#include "WindRigid.h"
#include <ctime> 
using namespace physx;

class SistemaSolidoRigido {
private:
    PxScene* gScene;
    PxPhysics* gPhysics;
    PxMaterial* materialBase;

    double tiemporegen = 10;
    int regen = 0;
    WindRigid* viento;                          

public:
    std::vector<SolidoRigido*> solidosDinamicos; // Sólidos dinámicos
    std::vector<SolidoRigido*> player; // player
    std::vector<SolidoRigido*> solidosDinamicosEnemigos; // Enemigos
    SistemaSolidoRigido(PxScene* scene, PxPhysics* physics, WindRigid* wind)
        : gScene(scene), gPhysics(physics), viento(wind) {
        // Crear material base con coeficientes iniciales
        srand(static_cast<unsigned int>(time(NULL)));
        materialBase = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
        
    }

    ~SistemaSolidoRigido() {
        limpiarTodosLosSolidos();
    }
    void pdate(double t) {
        _destruir(t);
        //tiemporegen -= t;
        //if (tiemporegen <= 0)
        //{
        //    PxVec3 dimensionesPlano = { 1000.0f, 0.1f, 33.0f };
        //    PxVec3 dimensionesObstaculo = { 1.0f, 1.0f, 1.0f };
        //    PxReal densidad = 1.0f;
        //    float distanciaMinima = 12.0f; // Distancia mínima entre obstáculos
        //    Vector4 color = { 0.0f, 1.0f, 0.0f, 1.0f };
        //    generarObstaculosConDistancia(dimensionesPlano, dimensionesObstaculo, distanciaMinima, densidad, color);

        //    PxVec3 dimensionesP = { 1000.0f, 0.1f, 35.0f };
        //    PxVec3 dimensionesObstaculoP = { 1.0f, 1.0f, 1.0f };
        //    float distanciaMinimaEnemigos = 30.0f; // Distancia mínima mayor para los obstáculos enemigos
        //    PxReal densidadP = 1.0f; // Densidad del material
        //    Vector4 colorEnemigos = { 1.0f, 0.0f, 0.0f, 1.0f }; // Color rojo para los enemigos


        //    
        //    
        //    generarObstaculosEnemigosConDistancia(dimensionesP, dimensionesObstaculoP, distanciaMinimaEnemigos, densidadP, colorEnemigos);
        //    tiemporegen = 10;
        //    regen++;
        //    if (regen >= 3)
        //    {
        //        tiemporegen = 10000;
        //    }
        //    else {

        //    }
        //    
        //}
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
    double t;
    void generarSolidoDinamico(const PxVec3& pos, const PxVec3& dimensiones, PxReal densidad, const PxVec3& velInicial, const PxVec3& velAngular, Vector4 color, int Player, int esRojo) {
        float volumen = dimensiones.x * dimensiones.y * dimensiones.z * 8;
        double masa = densidad * volumen;
        if (Player == 0)
        {

           t = 10000.0;
        }
        else {
           t = 20.0;
        }

        SolidoRigido* solido = new SolidoRigido(gPhysics, gScene, pos, velInicial, velAngular, dimensiones, masa,color, Player,t);
        if (Player == 0)
        {

            player.push_back(solido);
        }

        if (esRojo == 0) {
            // Desactivar colisión con los verdes
            for (auto& verde : solidosDinamicos) {
                desactivarColision(solido->getActor(), verde->getActor());
            }
            solidosDinamicosEnemigos.push_back(solido); // Agregar a rojos
        }
        else if (esRojo == 1)
        {
            // Desactivar colisión con los rojos
            for (auto& rojo : solidosDinamicosEnemigos) {
                desactivarColision(solido->getActor(), rojo->getActor());
            }
            solidosDinamicos.push_back(solido); // Agregar a verdes
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
                    if ((posicion - posExistente).magnitude() < distanciaMinima || posicion.x > 20) {
                        posicionValida = false;
                        break;
                    }
                }

            } while (!posicionValida);

            // Guardar posición válida
            posicionesGeneradas.push_back(posicion);

            // Crear el sólido dinámico en la posición generada
            generarSolidoDinamico(posicion, dimensionesObstaculo, densidad, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, color, 1,1);
        }
    }
    void generarObstaculosEnemigosConDistancia(const PxVec3& dimensionesPlano, const PxVec3& dimensionesObstaculo,
        float distanciaMayor, PxReal densidad, const Vector4& colorRojo) {
        // Limites del plano
        float xMin = -dimensionesPlano.x / 2;
        float xMax = dimensionesPlano.x / 2;
        float zMin = -dimensionesPlano.z / 2;
        float zMax = dimensionesPlano.z / 2;

        // Vector para almacenar posiciones ya generadas
        std::vector<PxVec3> posicionesGeneradas;

        // Generar enemigos aleatoriamente
        for (int i = 0; i < 20; ++i) { // Menos cantidad por la distancia mayor
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
                    if ((posicion - posExistente).magnitude() < distanciaMayor || posicion.x > 20) {
                        posicionValida = false;
                        break;
                    }
                }

            } while (!posicionValida);

            // Guardar posición válida
            posicionesGeneradas.push_back(posicion);

            // Crear el enemigo rojo en la posición generada
            generarSolidoDinamico(posicion, dimensionesObstaculo, densidad, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, colorRojo,1, 0);
        }
    }

    void aplicarFuerzas() {
        for (auto solido : solidosDinamicos) {
            viento->aplicarFuerza(solido->getActor());
        }
        for (auto solido : solidosDinamicosEnemigos) {
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
    void _destruir(double timepo) {
        for (auto it = solidosDinamicos.begin(); it != solidosDinamicos.end();) {
            if ((*it)->_debeDestruirse(timepo)) {

                delete* it;
                it = solidosDinamicos.erase(it);
            }
            else {
                ++it;
            }
        }
        for (auto it = solidosDinamicosEnemigos.begin(); it != solidosDinamicosEnemigos.end();) {
            if ((*it)->_debeDestruirse(timepo)) {
                delete* it;
                it = solidosDinamicosEnemigos.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    void desactivarColision(PxRigidActor* actor1, PxRigidActor* actor2) {
        PxShape* shapes1[1], * shapes2[1];
        actor1->getShapes(shapes1, 1);
        actor2->getShapes(shapes2, 1);

        for (PxShape* shape1 : shapes1) {
            for (PxShape* shape2 : shapes2) {
                shape1->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
                shape2->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
            }
        }
    }
};
