#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
using namespace physx;

class SolidoRigido
{

private:
   
	PxRigidDynamic* actor;   // Actor dinámico de PhysX
	RenderItem* renderItem; // Item de renderizado
    PxShape* shape;
public:
    double _tiempoVida;
    // Constructor
    SolidoRigido(PxPhysics* gPhysics, PxScene* gScene, const PxVec3& position, const PxVec3& linearVelocity, const PxVec3& angularVelocity, const PxVec3& dimensions,double masa, Vector4 color, int Player, double t) {
        _tiempoVida = t;
        // Crear el actor dinámico
        actor = gPhysics->createRigidDynamic(PxTransform(position));
        
        // Bloquear todas las rotaciones
        actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
        actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
        actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);
        if (Player == 0)
        {
            actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_X, true);
        }
        else {
            actor->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, true);
        }
        // Configurar velocidades
        actor->setLinearVelocity(linearVelocity);
        actor->setAngularVelocity(angularVelocity);

        PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.0f); // Restitución (bounciness) = 0.0f

        // Crear la forma del objeto
        shape = CreateShape(PxBoxGeometry(dimensions.x, dimensions.y, dimensions.z), material);
        actor->attachShape(*shape);

       //agregar inercia manual
        PxRigidBodyExt::updateMassAndInertia(*actor, 0.15);
        Vector3 aux = CalculaTensor(masa);
        actor->setMassSpaceInertiaTensor(aux);
        actor->setMass(masa);
        // Agregar el actor a la escena
        gScene->addActor(*actor);
        // Crear el item de renderizado
        renderItem = new RenderItem(shape, actor,color);
    }

    // Destructor
    ~SolidoRigido() {
        DeregisterRenderItem(renderItem);
        renderItem = nullptr;
    }
    void moverDerecha(float velocidad) {
        PxVec3 posicion = actor->getGlobalPose().p;
        if (posicion.z > -17) { // Verificar límite derecho
            actor->setLinearVelocity(PxVec3( 0, 0, -velocidad));
        }
        else {
            detener(); // Detener si llega al límite
        }
    }
    void detener() {
        actor->setLinearVelocity(PxVec3(0, 0, 0));
    }
    Vector3 Getpos() {return actor->getGlobalPose().p ; }
    void moverIzquierda(float velocidad) {
        PxVec3 posicion = actor->getGlobalPose().p;
        if (posicion.z < 17) { // Verificar límite izquierdo
            actor->setLinearVelocity(PxVec3( 0, 0, velocidad));
        }
        else {
            detener(); // Detener si llega al límite
        }
    }

    PxRigidDynamic* getActor(){ return actor; }
    Vector3 CalculaTensor(float m) {
        PxGeometryType::Enum tipo = shape->getGeometryType();
        if (tipo == PxGeometryType::eBOX )
        {
            PxBoxGeometry cubo;
            shape->getBoxGeometry(cubo);
            float x = 2 * cubo.halfExtents.x;
            float y = 2 * cubo.halfExtents.y;
            float z = 2 * cubo.halfExtents.z;

            return Vector3((1.0f / 12.0f) * m * (y * y + z * z), (1.0f / 12.0f) * m * (x * x + z * z), (1.0f / 12.0f) * m * (x * x + y * y));
        }
        else if (tipo == PxGeometryType::eSPHERE)
        {
            PxSphereGeometry esfera;
            shape->getSphereGeometry(esfera);

            float aux = (2.0f / 5.0f) * m * esfera.radius * esfera.radius;
            return Vector3(aux, aux, aux);
        }
        else {
            return Vector3(1.0, 1.0, 1.0);
        }
    }
    
    bool _debeDestruirse(double t) {
        _tiempoVida -= t;
        return _tiempoVida <= 0;

    }
};

