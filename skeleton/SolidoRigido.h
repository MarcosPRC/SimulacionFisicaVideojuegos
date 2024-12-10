#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
using namespace physx;

class SolidoRigido
{

private:

	PxRigidDynamic* actor;   // Actor dinámico de PhysX
	RenderItem* renderItem; // Item de renderizado
public:
    // Constructor
    SolidoRigido(PxPhysics* gPhysics, PxScene* gScene, const PxVec3& position, const PxVec3& linearVelocity, const PxVec3& angularVelocity, const PxVec3& dimensions) {
        // Crear el actor dinámico
        actor = gPhysics->createRigidDynamic(PxTransform(position));

        // Configurar velocidades
        actor->setLinearVelocity(linearVelocity);
        actor->setAngularVelocity(angularVelocity);

        // Crear la forma del objeto (cubo)
        PxShape* shape = CreateShape(PxBoxGeometry(dimensions.x, dimensions.y, dimensions.z));
        actor->attachShape(*shape);

        // Agregar el actor a la escena
        gScene->addActor(*actor);

        // Crear el item de renderizado
        renderItem = new RenderItem(shape, actor, { 1.0f, 0.0f, 0.0f, 1.0f }); // Rojo
    }

    // Destructor
    ~SolidoRigido() {
        delete renderItem;
        actor->release();
    }
};

