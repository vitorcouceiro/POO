#include <sstream>
#include <utility>
#include "Regra.h"
#include "../Sensores/Sensor.h"

using namespace std;
int Regra::contRegras = 0;


Regra::Regra(std::string regra, double x): tipo(std::move(regra)), param(x), sensor(nullptr){
    ostringstream os;
    os << "r" <<  ++contRegras;
    id = os.str();
}

double Regra::getParam() const {
    return param;
}

const string &Regra::getId() const {
    return id;
}

const string &Regra::getTipo() const {
    return tipo;
}

Sensor *Regra::getSensor() const {
    return sensor;
}

bool Regra::associaSensor(Sensor *sen){
    if(sensor == nullptr) {
        sensor = sen;
        return true;
    }

    return false;
}