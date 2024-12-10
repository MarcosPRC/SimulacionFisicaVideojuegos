#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "SolidoRigido.h"
#include <vector>

using namespace physx;
class SistemaSolidoRigido
{
private:
    PxScene* gScene;
    PxPhysics* gPhysics;
    PxMaterial* materialBase;
    
public:
    std::vector<SolidoRigido*> solidosDinamicos;
    SistemaSolidoRigido(PxScene* scene, PxPhysics* physics) : gScene(scene), gPhysics(physics) {
        // Crear material base con coeficientes iniciales
        materialBase = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
    }

    void crearSuelo() {
        PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0, 0, 0 }));
        PxShape* shapeSuelo = CreateShape(PxBoxGeometry(100, 0.1, 100));
        suelo->attachShape(*shapeSuelo);
        gScene->addActor(*suelo);

        // Renderizar suelo
        new RenderItem(shapeSuelo, suelo, { 0.8f, 0.8f, 0.8f, 1.0f });
    }

    void crearObstaculoEstatico(const PxVec3& pos, const PxVec3& dimensiones) {
        PxRigidStatic* obstaculo = gPhysics->createRigidStatic(PxTransform(pos));
        PxShape* shapeObstaculo = CreateShape(PxBoxGeometry(dimensiones));
        obstaculo->attachShape(*shapeObstaculo);
        gScene->addActor(*obstaculo);

        // Renderizar obstaculo
        new RenderItem(shapeObstaculo, obstaculo, { 0.5f, 0.5f, 0.5f, 1.0f });
    }

    void generarSolidoDinamico(const PxVec3& pos, const PxVec3& dimensiones, PxReal densidad, const PxVec3& velInicial, const PxVec3& velAngular) {
        float volumen = dimensiones.x * dimensiones.y * dimensiones.z * 8; // Volumen total
        double masa = densidad * volumen;

        SolidoRigido* solido = new SolidoRigido(gPhysics, gScene, pos, velInicial, velAngular, dimensiones, masa);
        solidosDinamicos.push_back(solido);
    }
    void limpiarTodosLosSolidos() {
        for (SolidoRigido* solido : solidosDinamicos) {
            delete solido;
        }
        solidosDinamicos.clear();
    }
    void borrarCadaCincoSegundos(float tiempoTranscurrido) {
        static float tiempoAcumulado = 0.0f;
        tiempoAcumulado += tiempoTranscurrido;

        if (tiempoAcumulado >= 5.0f) {
            limpiarTodosLosSolidos();
            tiempoAcumulado = 0.0f;
        }
    }

};

