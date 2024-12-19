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
    int lvl = 0;
public:
    int puntos = 0;
    std::vector<SolidoRigido*> solidosDinamicos;
    std::vector<SolidoRigido*> player; // player
    std::vector<SolidoRigido*> solidosDinamicosEnemigos; // Enemigos
    std::vector<SolidoRigido*> solidosDinamicosWin; // Bloques de victoria
    SistemaSolidoRigido(PxScene* scene, PxPhysics* physics, WindRigid* wind)
        : gScene(scene), gPhysics(physics), viento(wind) {
        srand(static_cast<unsigned int>(time(NULL)));
        materialBase = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
        
    }

    ~SistemaSolidoRigido() {
        limpiarTodosLosSolidos();
    }
    void pdate(double t) {
        _destruir(t);
    }
    void crearSuelo() {
        PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0, 0, 0 }));
        PxShape* shapeSuelo = CreateShape(PxBoxGeometry(2000, 0.1, 20));
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
    void generarSolidoDinamico(const PxVec3& pos, const PxVec3& dimensiones, PxReal densidad, const PxVec3& velInicial, const PxVec3& velAngular, Vector4 color, int Player, int esRojo,bool vict, bool cuadrado) {
        float volumen = dimensiones.x * dimensiones.y * dimensiones.z * 8;
        double masa = densidad * volumen;
        if (Player == 0)
        {

           t = 80.0;
        }
        else {
           t = 60.0;
        }

        SolidoRigido* solido = new SolidoRigido(gPhysics, gScene, pos, velInicial, velAngular, dimensiones, masa,color, Player,t,cuadrado);
        if (Player == 0)
        {

            player.push_back(solido);
        }

        if (esRojo == 0) {
            for (auto& verde : solidosDinamicos) {
                desactivarColision(solido->getActor(), verde->getActor());
            }
            solidosDinamicosEnemigos.push_back(solido);
        }
        else if (esRojo == 1)
        {
            for (auto& rojo : solidosDinamicosEnemigos) {
                desactivarColision(solido->getActor(), rojo->getActor());
            }
            solidosDinamicos.push_back(solido);
        }
        if (vict)
        {
            for (auto& verde : solidosDinamicos) {
                desactivarColision(solido->getActor(), verde->getActor());
            }
            for (auto& rojo : solidosDinamicosEnemigos) {
                desactivarColision(solido->getActor(), rojo->getActor());
            }
            solidosDinamicosWin.push_back(solido);
        }
    }
    void generarObstaculosConDistancia(const PxVec3& dimensionesPlano, const PxVec3& dimensionesObstaculo,
        float distanciaMinima, PxReal densidad, const Vector4& color)
    {
        float xMin;
        float xMax;
        float zMin;
        float zMax;
        // Limites del plano
            xMin = -dimensionesPlano.x / 2;
            xMax = dimensionesPlano.x / 2;
            zMin = -dimensionesPlano.z / 2;
            zMax = dimensionesPlano.z / 2;
     
        

        std::vector<PxVec3> posicionesGeneradas;

        for (int i = 0; i < 100; ++i) {
            PxVec3 posicion;
            bool posicionValida;

            do {
                posicionValida = true;
                posicion = {
                    xMin + static_cast<float>(rand()) / RAND_MAX * (xMax - xMin),
                    dimensionesObstaculo.y / 2,
                    zMin + static_cast<float>(rand()) / RAND_MAX * (zMax - zMin)
                };

                for (const auto& posExistente : posicionesGeneradas) {
                    if ((posicion - posExistente).magnitude() < distanciaMinima || posicion.x > 500) {
                        posicionValida = false;
                        break;
                    }
                }

            } while (!posicionValida);

            posicionesGeneradas.push_back(posicion);

            generarSolidoDinamico(posicion, dimensionesObstaculo, densidad, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, color, 1,1,false,true);
        }
    }
   

    void generarObstaculosEnemigosConDistancia(const PxVec3& dimensionesPlano, const PxVec3& dimensionesObstaculo,
        float distanciaMayor, PxReal densidad, const Vector4& colorRojo) {
        // Limites del plano
        float xMin = -dimensionesPlano.x / 2;
        float xMax = dimensionesPlano.x / 2;
        float zMin = -dimensionesPlano.z / 2;
        float zMax = dimensionesPlano.z / 2;

        std::vector<PxVec3> posicionesGeneradas;
        PxVec3 posicionMasAlejada = { 0, 0, 0 };

        for (int i = 0; i < 50; ++i) {
            PxVec3 posicion;
            bool posicionValida;

            do {
                posicionValida = true;
                posicion = {
                    xMin + static_cast<float>(rand()) / RAND_MAX * (xMax - xMin),
                    dimensionesObstaculo.y / 2,
                    zMin + static_cast<float>(rand()) / RAND_MAX * (zMax - zMin)
                };

                for (const auto& posExistente : posicionesGeneradas) {
                    if ((posicion - posExistente).magnitude() < distanciaMayor || posicion.x > 500) {
                        posicionValida = false;
                        break;
                    }
                }

            } while (!posicionValida);

            posicionesGeneradas.push_back(posicion);
            generarSolidoDinamico(posicion, dimensionesObstaculo, densidad, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, colorRojo, 1, 0,false,true);

            if (player.size() > 0 && (posicion.x - player[0]->getActor()->getGlobalPose().p.x) <
                (posicionMasAlejada.x - player[0]->getActor()->getGlobalPose().p.x)) {
                posicionMasAlejada = posicion;
            }
        }

        // Crear la fila de bloques amarillos a lo largo del eje Z
        float distanciaLineal = 50.0f;
        PxVec3 posicionInicioAmarillos = posicionMasAlejada + PxVec3(distanciaLineal, 0, 0);
        Vector4 colorAmarillo = { 1.0f, 1.0f, 0.0f, 1.0f }; // Color amarillo
        int cantidadBloquesFila = static_cast<int>(dimensionesPlano.z / dimensionesObstaculo.z);

        for (int i = 0; i < cantidadBloquesFila; ++i) {
            PxVec3 posicion = posicionInicioAmarillos + PxVec3(0, 0, (i - cantidadBloquesFila / 2) * dimensionesObstaculo.z * 2);
            generarSolidoDinamico(posicion, dimensionesObstaculo, densidad, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, colorAmarillo, 1, 2, true,true);
        }
    }



    void aplicarFuerzas() {
        for (auto solido : solidosDinamicos) {
            viento->aplicarFuerza(solido->getActor());
        }
        for (auto solido : solidosDinamicosEnemigos) {
            viento->aplicarFuerza(solido->getActor());
        }
        for (auto solido :solidosDinamicosWin) {
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
                puntos++;
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
        for (auto it = solidosDinamicosWin.begin(); it != solidosDinamicosWin.end();) {
            if ((*it)->_debeDestruirse(timepo)) {
                delete* it;
                it = solidosDinamicosWin.erase(it);
            }
            else {
                ++it;
            }
        }
        for (auto it = player.begin(); it != player.end();) {
            if ((*it)->_debeDestruirse(timepo)) {

                delete* it;
                it = player.erase(it);
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
