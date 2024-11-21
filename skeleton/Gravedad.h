#pragma once
#include "ForceGenerator.h"
class Gravedad : public ForceGenerator
{
public:
	Gravedad();

	void apply_force() override;

private:
	Vector3 gravedad;
};

