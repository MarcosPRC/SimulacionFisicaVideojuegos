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
    // Constructor
    SolidoRigido(PxPhysics* gPhysics, PxScene* gScene, const PxVec3& position, const PxVec3& linearVelocity, const PxVec3& angularVelocity, const PxVec3& dimensions,double masa) {
        // Crear el actor dinámico
        actor = gPhysics->createRigidDynamic(PxTransform(position));

        // Configurar velocidades
        actor->setLinearVelocity(linearVelocity);
        actor->setAngularVelocity(angularVelocity);

        // Crear la forma del objeto (cubo)
        shape = CreateShape(PxBoxGeometry(dimensions.x, dimensions.y, dimensions.z));
        actor->attachShape(*shape);

       //agregar inercia manual
        PxRigidBodyExt::updateMassAndInertia(*actor, 0.15);
        Vector3 aux = CalculaTensor(masa);
        actor->setMassSpaceInertiaTensor(aux);
        actor->setMass(masa);
        // Agregar el actor a la escena
        gScene->addActor(*actor);

        // Crear el item de renderizado
        renderItem = new RenderItem(shape, actor, { 0.0f, 1.0f, 0.0f, 1.0f }); // Rojo
    }

    // Destructor
    ~SolidoRigido() {
        delete renderItem;
        actor->release();
    }
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
};

