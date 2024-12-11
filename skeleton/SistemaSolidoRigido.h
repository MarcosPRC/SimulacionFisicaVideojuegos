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

    
    WindRigid* viento;                           // Instancia de viento para sólidos rígidos

public:
    std::vector<SolidoRigido*> solidosDinamicos; // Sólidos dinámicos
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
        new RenderItem(shapeSuelo, suelo, { 0.8f, 0.8f, 0.8f, 1.0f });
    }

    void crearObstaculoEstatico(const PxVec3& pos, const PxVec3& dimensiones) {
        PxRigidStatic* obstaculo = gPhysics->createRigidStatic(PxTransform(pos));
        PxShape* shapeObstaculo = CreateShape(PxBoxGeometry(dimensiones));
        obstaculo->attachShape(*shapeObstaculo);
        gScene->addActor(*obstaculo);
        new RenderItem(shapeObstaculo, obstaculo, { 0.5f, 0.5f, 0.5f, 1.0f });
    }

    void generarSolidoDinamico(const PxVec3& pos, const PxVec3& dimensiones, PxReal densidad, const PxVec3& velInicial, const PxVec3& velAngular) {
        float volumen = dimensiones.x * dimensiones.y * dimensiones.z * 8;
        double masa = densidad * volumen;

        SolidoRigido* solido = new SolidoRigido(gPhysics, gScene, pos, velInicial, velAngular, dimensiones, masa);
        solidosDinamicos.push_back(solido);
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
