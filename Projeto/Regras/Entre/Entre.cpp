#include "Entre.h"

Entre::Entre(double x, double y) : Regra("entre", x), param2(y){}

bool Entre::verificaRegra(double val) {
    return (val > getParam() && val < getParam2());
}

double Entre::getParam2() const {
    return param2;
}

Regra* Entre::duplica() const{
    return new Entre(*this);
}