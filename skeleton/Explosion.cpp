//#include "Explosion.h"
//Explosion::Explosion(Vector3 centro, float intensidad_, float radioMaximo_, float constanteTiempo_)
//    : centroExplosión(centro), intensidad(intensidad_), radioMaximo(radioMaximo_),constanteTiempo(constanteTiempo_), tiempoActual(0.0f), activa(false) {}
//void Explosion::aplicarFuerza() {
//    if (!activa) return;
//
//    for (auto sistema : partsis) {
//        for (auto particula : sistema->GetLparticulas()) {
//
//            Vector3 posicion = particula->getPosition();
//            Vector3 direccion = posicion - centroExplosión;
//            float distancia = direccion.magnitude();
//
//            if (distancia <= radioMaximo) {
//                direccion.normalize();
//
//                // Calculamos la fuerza
//                float fuerzaMagnitud = (intensidad / (distancia * distancia)) * std::exp(-tiempoActual / constanteTiempo);
//                Vector3 fuerza = direccion * fuerzaMagnitud;
//
//                particula->aplicarFuerza(fuerza);
//            }
//        }
//    }
//}
//void Explosion::iniciarExplosion() {
//    activa = true;
//    tiempoActual = 0.0f; 
//}
//bool Explosion::estaDentroDelRadio(const Vector3& posicion) const {
//    return (posicion - centroExplosión).magnitude() <= radioMaximo;
//}
//
//void Explosion::actualizarTiempo(float tiempo) {
//    if (activa) {
//        tiempoActual += tiempo;
//
//        if (tiempoActual >= 4 * constanteTiempo) {
//            activa = false;
//        }
//    }
//}