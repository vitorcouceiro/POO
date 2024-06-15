#include "Fora.h"

Fora::Fora(double x, double y) : Regra("fora", x), param2(y){}

bool Fora::verificaRegra(double val) {
    return (val < getParam() || val > getParam2());
}

double Fora::getParam2() const {
    return param2;
}
Regra* Fora::duplica() const{
    return new Fora(*this);
}