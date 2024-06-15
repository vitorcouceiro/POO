//
// Created by nunes on 06/12/2023.
//

#include "Igual.h"
bool Igual::verificaRegra(double x) {
    return x == getParam();
}

Regra* Igual::duplica() const{
    return new Igual(*this);
}