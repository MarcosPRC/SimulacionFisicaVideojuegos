#include "Vector3D.h"
Vector3D Vector3D::Normalizar() const {
    float const magnitudes = Magnitud();
    if (magnitudes == 0) {
        return Vector3D(0, 0, 0);
    }
    return Vector3D(x / magnitudes, y / magnitudes, z / magnitudes);
}

float Vector3D::Magnitud() const {
        return std::sqrt(x * x + y * y + z * z);
    }

float Vector3D::Producto(const Vector3D aux) const {
    return( x * aux.x, y * aux.y,z * aux.z);
}
float Vector3D::MultiplicarEscalar(float escalar) const {
    return(x * escalar, y* escalar, z * escalar);
}

Vector3D& Vector3D::operator=(const Vector3D& aux) {
    if (this != &aux) {
        x = aux.x;
        y = aux.y;
        z = aux.z;
    }
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D& aux) const {
    return Vector3D(x + aux.x, y + aux.y, z + aux.z);
}

Vector3D Vector3D::operator-(const Vector3D& aux) const {
    return Vector3D(x - aux.x, y - aux.y, z - aux.z);
}

Vector3D Vector3D::operator*(float escalar) const {
    return Vector3D(x * escalar, y * escalar, z * escalar);
}

