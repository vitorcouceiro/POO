#include <string>
#include <sstream>
#include "Sensor.h"
#include "../Propriedades/Propriedade.h"

using namespace std;
int Sensor::contSensores = 0;

Sensor::Sensor(const std::string tipo, const std::string &letra) : nome(tipo), letra(letra), prop(nullptr){
    ostringstream os;
    os << letra <<  ++contSensores;
    id = os.str();
}
const std::string &Sensor::getId() const {
    return id;
}

const std::string &Sensor::getNome() const {
    return nome;
}

bool Sensor::associaPropriedade (Propriedade * propNova){
    if( prop == nullptr ) {
        prop = propNova;
        return true;
    }
    return false;
}

Propriedade* Sensor::getPropriedade() const {
    return prop;
}

int Sensor::getValor(){
    return prop->getValor();
}