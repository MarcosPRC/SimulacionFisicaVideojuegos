#pragma once
#include <cmath>
class Vector3D
{
public:

	Vector3D() : x(0), y(0), z(0) {};
	Vector3D(float x, float y, float z) : x(x), y(y), z(z) {};
	
	//metodos basicos p0
	Vector3D Normalizar() const;
	float Magnitud() const;
	float Producto(const Vector3D aux) const;
	float MultiplicarEscalar(float escalar) const;

	//sobrecargar operadores p0
	Vector3D& operator=(const Vector3D& aux);
	Vector3D operator+(const Vector3D& aux) const;
	Vector3D operator-(const Vector3D& aux) const;
	Vector3D operator*(float escalar) const;
private:
	float x, y, z;
};

