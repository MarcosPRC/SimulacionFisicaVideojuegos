#include "Gravedad.h"
#include "Particle.h"
Gravedad::Gravedad()
{
	gravedad = Vector3(0, -9.8, 0);
}

void Gravedad::apply_force()
{
	for (auto ps : partsis)
	{
		for (auto p : ps->GetLparticulas())
		{
			Vector3 gravityForce = (p->masa() * gravedad);
			p->apply_force(gravityForce);
		}
	}
}
