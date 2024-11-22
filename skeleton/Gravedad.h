#pragma once
#include "ForceGenerator.h"
class Gravedad : public ForceGenerator
{
public:
	Gravedad();

	void aplicarFuerza() override;

private:
	Vector3 gravedad;
};

