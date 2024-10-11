#pragma once
#include <cmath>


class Vector3D
{
public:

	float x, y, z;

	Vector3D() : x(0), y(0), z(0) {};
	Vector3D(float x, float y, float z) : x(x), y(y), z(z) {};
	
	
	Vector3D Normalizar() const {
		float const magnitudes = Magnitud();
		if (magnitudes == 0) {
			return Vector3D(0, 0, 0);
		}
		return Vector3D(x / magnitudes, y / magnitudes, z / magnitudes);
	}
	float Magnitud() const {
		return std::sqrt(x * x + y * y + z * z);
	}
	float Producto(const Vector3D aux) const {
		return(x * aux.x, y * aux.y, z * aux.z);
	}
	float MultiplicarEscalar(float escalar) const {
		return(x * escalar, y * escalar, z * escalar);
	}

	//sobrecargar operadores p0
	Vector3D& operator=(const Vector3D& aux) {
		if (this != &aux) {
			x = aux.x;
			y = aux.y;
			z = aux.z;
		}
		return *this;
	}
	Vector3D operator+(const Vector3D& aux) const {
		return Vector3D(x + aux.x, y + aux.y, z + aux.z);
	}
	Vector3D operator-(const Vector3D& aux) const {
		return Vector3D(x - aux.x, y - aux.y, z - aux.z);
	}
	Vector3D operator*(float escalar) const {
		return Vector3D(x * escalar, y * escalar, z * escalar);
	}


};

