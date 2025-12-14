//#include "Physics.h"
//
//Physics::Physics()
//{
//	m_Foundation = NULL;
//	m_Physics = NULL;
//    m_Dispatcher = NULL;
//	m_Scene = NULL;
//	m_Material = NULL;
//	m_Pvd = NULL;
//	// Init physx
//	m_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_DefaultAllocatorCallback, m_DefaultErrorCallback);
//	if (!m_Foundation) throw("PxCreateFoundation failed!");
//	m_Pvd = PxCreatePvd(*m_Foundation);
//	transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
//	m_Pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);
//
//}
//
//void Physics::InitPhysX()
//{
//	//m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, PxTolerancesScale(), true, m_Pvd);
//	m_ToleranceScale.length = 100;			// typical length of an object
//	m_ToleranceScale.speed = 981;			// typical speed of an object, gravity*1s is a reasonable choice
//	m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, m_ToleranceScale, true, m_Pvd);
//	//m_physics = PxCreatePhyscs(PX_PHYSICS_VERSION, *m_Foundation, m_ToleranceScale);
//	PxSceneDesc m_sceneDesc(m_Physics->getTolerancesScale());
//	m_sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
//	m_Dispatcher = PxDefaultCpuDispatcherCreate(2);
//	m_sceneDesc.cpuDispatcher = m_Dispatcher;
//	m_sceneDesc.filterShader = PxDefaultSimulationFilterShader;
//	m_Scene = m_Physics->createScene(m_sceneDesc);
//
//	pvdClient = m_Scene->getScenePvdClient();
//	if (pvdClient)
//	{
//		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
//		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
//		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
//	}
//}
//
//void Physics::CreateSimulation()
//{
//	m_Material = m_Physics->createMaterial(0.5f, 0.5f, 0.6f);
//	PxRigidStatic* groundPlane = PxCreatePlane(*m_Physics, PxPlane(0, 1, 0, 1), *m_Material);
//	m_Scene->addActor(*groundPlane);
//}
//
//void Physics::RunSimulation()
//{
//	while (true)
//	{
//		m_Scene->simulate(1.0 / 60.0f);
//		m_Scene->fetchResults(true);
//	}
//}