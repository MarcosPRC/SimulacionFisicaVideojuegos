#include <ctype.h>

#include <PxPhysicsAPI.h>
#include "Particle.h"
#include <vector>
#include "Vector3D.h"
#include "Vector3D.cpp"
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Proyectil.h"
#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
//lista items
RenderItem* centro;//p0
RenderItem* ejeX;//p0
RenderItem* ejeY;//p0
RenderItem* ejeZ;//p0
Particle* particula;//p1.1
std::vector<Proyectil*> proyectiles; //p1.2
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	//EJES
	PxSphereGeometry geo;
	geo.radius = 10;
	Vector3D v0 = { 0.0f, 0.0f, 0.0f };
	Vector3D v1 = { 10.0f, 0.0f, 0.0f };
	Vector3D v2 = { 0.0f, 10.0f, 0.0f };
	Vector3D v3 = { 0.0f, 0.0f, 10.0f };
	

	//Crear Shape y centro
	 PxShape* shape = CreateShape(PxSphereGeometry(1));
	// centro = new RenderItem(shape, new PxTransform(v0.x, v0.y, v0.z), Vector4(1, 1, 1, 1));
	// Crear el rojo
	//ejeX = new RenderItem(shape, new PxTransform(v1.x, v1.y, v1.z), Vector4(1, 0, 0, 1));
	// Crear el Verde
	//ejeY = new RenderItem(shape, new PxTransform(v2.x, v2.y, v2.z), Vector4(0, 1, 0, 1));
	// Crear el azul
	//ejeZ = new RenderItem(shape, new PxTransform(v3.x, v3.y, v3.z), Vector4(0, 0, 1, 1));
	particula = new Particle(new PxTransform(0, 0, 0), Vector3{2,0,0}, Vector3{1,0,0});
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	particula->integrate(t);
	gScene->simulate(t);
	gScene->fetchResults(true);
	for (auto proyectil : proyectiles) {
		proyectil->disparar(t);  // Actualiza la física del proyectil
	}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	for (auto proyectil : proyectiles) {
		delete proyectil;
	}
	proyectiles.clear();

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'B':
	{
		// Creamos proyectil  desde la camara
		Vector3 direccionCamara = GetCamera()->getDir();
		Vector3 posicionIniCamara = { camera.p.x, camera.p.y, camera.p.z };

		// Creamos el proyectil vel inicial y pos de la camara
		Proyectil* nuevoProyectil = new Proyectil(125.0, 10.0, direccionCamara, posicionIniCamara);
		proyectiles.push_back(nuevoProyectil);
		break;
	}
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}