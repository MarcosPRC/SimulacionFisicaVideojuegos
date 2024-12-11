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
#include "SistemaParticulas.h"
#include "ForceGenerator.h"
#include "Gravedad.h"
#include "SolidoRigido.h"
#include "SistemaSolidoRigido.h"
#include "WindRigid.h"
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
SistemaParticulas* sistemaParticulas;
ForceGenerator* gravedad = nullptr;
SistemaSolidoRigido* sistemaSolidos;
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



	//---------------------------PRACTICA FINAL---------------------------
	WindRigid* vientoR = new WindRigid({300 , 0,0 }, 0.5f, 0.3f, { -500000, 0, -5000000 }, { 500000, 500, 5000000 }, true);
	sistemaSolidos = new SistemaSolidoRigido(gScene, gPhysics,vientoR);
	sistemaSolidos->crearSuelo();
	PxVec3 posicionInicial = { 90, 2, 0 };   // Altura inicial para evitar colisión inmediata
	PxVec3 dimensiones = { 1.5,2, 1.5 };        // Dimensiones del cubo
	PxVec3 velocidadInicial = { 0, 0, 0 };  // Movimiento hacia adelante en el eje X
	PxVec3 velocidadAngular = { 0, 0, 0 };   // Sin rotación inicial
	PxReal densidad = 1.0f;                  // Densidad del material
	sistemaSolidos->generarSolidoDinamico(posicionInicial, dimensiones, densidad, velocidadInicial, velocidadAngular, Vector4({1,1,0,1}), true);

	PxVec3 dimensionesPlano = { 1000.0f, 0.1f, 35.0f };
	PxVec3 dimensionesObstaculo = { 1.0f, 1.0f, 1.0f };
	float distanciaMinima = 12.0f; // Distancia mínima entre obstáculos
	Vector4 color = { 0.0f, 1.0f, 0.0f, 1.0f };

	sistemaSolidos->generarObstaculosConDistancia(dimensionesPlano, dimensionesObstaculo, distanciaMinima, densidad, color);
	//------PRACTICA SOLIDOSRIGIDOS-------
	////Generar suelo
	//PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	//PxShape* shapee = CreateShape(PxBoxGeometry(100, 0.1, 100));
	//suelo->attachShape(*shapee);
	//gScene->addActor(*suelo);
	////pintar suelo
	//RenderItem* item;
	//item = new RenderItem(shapee, suelo, {0.8,0.8,0.8,1});
	////solidorigido
	//SolidoRigido* solido = new SolidoRigido(gPhysics, gScene, PxVec3(-70, 200, -70), PxVec3(0, 5, 0), PxVec3(0, 0, 0), PxVec3(5, 5, 5),1.0);

	// Crear sistema de sólidos rígidos
	//WindRigid* vientoR = new WindRigid({ 100, 0, 0 }, 0.5f, 0.3f, { -500, 0, -500 }, { 500, 500, 500 }, false);
	//sistemaSolidos = new SistemaSolidoRigido(gScene, gPhysics,vientoR);

	// Crear suelo
	//sistemaSolidos->crearSuelo();

	// Crear obstáculos
	//sistemaSolidos->crearObstaculoEstatico({ 10, 1, 10 }, { 2, 2, 2 });
	//sistemaSolidos->crearObstaculoEstatico({ -10, 1, -10 }, { 2, 2, 2 });

	// Crear sólidos dinámicos
	/*for (int i = 0; i < 5; ++i) {
		PxVec3 pos = { float(rand() % 20 - 10), float(5 + rand() % 10), float(rand() % 20 - 10) };
		PxVec3 dimensiones = { float(rand() % 3 + 1), float(rand() % 3 + 1), float(rand() % 3 + 1) };
		PxVec3 velInicial = { float(rand() % 5 - 2), float(rand() % 5), float(rand() % 5 - 2) };
		PxVec3 velAngular = { float(rand() % 3), float(rand() % 3), float(rand() % 3) };
		PxReal densidad = float(rand() % 10 + 1);

		sistemaSolidos->generarSolidoDinamico(pos, dimensiones, densidad, velInicial, velAngular);
	}*/




	//Crear Shape y centro
	 PxShape* shape = CreateShape(PxSphereGeometry(1));
	// centro = new RenderItem(shape, new PxTransform(v0.x, v0.y, v0.z), Vector4(1, 1, 1, 1));
	// Crear el rojo
	//ejeX = new RenderItem(shape, new PxTransform(v1.x, v1.y, v1.z), Vector4(1, 0, 0, 1));
	// Crear el Verde
	//ejeY = new RenderItem(shape, new PxTransform(v2.x, v2.y, v2.z), Vector4(0, 1, 0, 1));
	// Crear el azul
	//ejeZ = new RenderItem(shape, new PxTransform(v3.x, v3.y, v3.z), Vector4(0, 0, 1, 1));
	//particula = new Particle(new PxTransform(0, 0, 0), Vector3{2,0,0}, Vector3{1,0,0});
	 sistemaParticulas = new SistemaParticulas();
	 sistemaParticulas->añadirGenerador('g', sistemaSolidos);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	//particula->integrate(t);
	gScene->simulate(t);
	gScene->fetchResults(true);
	sistemaParticulas->update(t);
	//GetCamera()->MueveCamara();

	//for (auto proyectil : proyectiles) {
	//	proyectil->disparar(t);  // Actualiza la física del proyectil
	//}

	
	/*if (sistemaSolidos->solidosDinamicos.size() < 30)
	{
		PxVec3 pos = { float(rand() % 20 - 10), float(5 + rand() % 10), float(rand() % 20 - 10) };
		PxVec3 dimensiones = { float(rand() % 3 + 1), float(rand() % 3 + 1), float(rand() % 3 + 1) };
		PxVec3 velInicial = { float(rand() % 5 - 2), float(rand() % 5), float(rand() % 5 - 2) };
		PxVec3 velAngular = { float(rand() % 3), float(rand() % 3), float(rand() % 3) };
		PxReal densidad = float(rand() % 10 + 1);
		sistemaSolidos->generarSolidoDinamico(pos, dimensiones, densidad, velInicial, velAngular);
	}*/
	sistemaSolidos->aplicarFuerzas();
	//sistemaSolidos->borrarCadaCincoSegundos(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	/*for (auto proyectil : proyectiles) {
		delete proyectil;
	}
	proyectiles.clear();*/
	delete sistemaParticulas; // Libera el sistema de partículas
	sistemaParticulas = nullptr;
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
	//case 'B':
	//{
	//	// Creamos proyectil  desde la camara
	//	Vector3 direccionCamara = GetCamera()->getDir();
	//	Vector3 posicionIniCamara = { camera.p.x, camera.p.y, camera.p.z };

	//	// Creamos el proyectil vel inicial y pos de la camara
	//	Proyectil* nuevoProyectil = new Proyectil(500.0, 10.0, direccionCamara, posicionIniCamara);
	//	proyectiles.push_back(nuevoProyectil);
	//	break;
	//}
	/*case ' ':
	{
		break;
	}*/

	case '1':
		//sistemaParticulas->añadirGenerador('f');
		break;
	case '2':
		//sistemaParticulas->añadirGenerador('f');
		break;
	case '3':
		//sistemaParticulas->añadirGenerador('c');
		break;
	case '4':
		//sistemaParticulas->añadirGenerador('e');
		break;
	case '5':
		//sistemaParticulas->GenerateSpringDemo();
		break;
	case '6':
		//sistemaParticulas->GenerateElasticSpringDemo();
		break;
	case '9':
		//sistemaSolidos->toggleViento();
		cout << "pum";
		break;
	case 'X': // Aplicar fuerza temporal hacia arriba
		//sistemaParticulas->aplicarFuerzaTemporal(Vector3(0.0f, -50.0f, 0.0f), 0.2); // Fuerza de 50 unidades por 0.2 segundos
		break;
	case 'C': // Incrementar constante del resorte
		//sistemaParticulas->modificarConstanteMuelle(1.0); // Aumentar k en 1.0
		break;
	case 'V': // Decrementar constante del resorte
		//sistemaParticulas->modificarConstanteMuelle(-1.0); // Reducir k en 1.0
		break;
	case 'L':
		sistemaSolidos->player[0]->moverIzquierda(10.0f);
		sistemaParticulas->cambio(true);
		break;
	case 'R':
		sistemaSolidos->player[0]->moverDerecha(10.0f);
		sistemaParticulas->cambio(false);
		break;
	//case 'e':
		//sistemaParticulas->activarExplosion(Vector3(0, 0, 0));
	default:
		sistemaSolidos->player[0]->detener();
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