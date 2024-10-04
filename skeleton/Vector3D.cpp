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

