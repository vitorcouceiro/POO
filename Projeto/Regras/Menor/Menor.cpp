#include "Menor.h"
bool Menor::verificaRegra(double x) {
    return (x < getParam());
}

Regra* Menor::duplica() const{
    return new Menor(*this);
}