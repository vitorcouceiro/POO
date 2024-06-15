#include "Maior.h"

bool Maior::verificaRegra(double x) {
    return x > getParam();
}

Regra* Maior::duplica() const{
    return new Maior(*this);
}