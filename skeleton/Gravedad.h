#pragma once
#include "ForceGenerator.h"
class Gravedad : public ForceGenerator
{
public:
	Gravedad();

	void aplicarFuerza() const override;

private:
	Vector3 gravedad;
};

