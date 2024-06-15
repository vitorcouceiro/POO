#include "Aspersor.h"
#include "../../Propriedades/Propriedade.h"

Aspersor::Aspersor() : Aparelho("aspersor", "s"), contador(0), contadorDesliga(0),flag(0) {}

Aspersor* Aspersor::duplica() const {
    return new Aspersor(*this);
}

void Aspersor::liga() {
    if (!on) {
        on = true;
        addHumidade();
        addVibracao();
    } else {
        contador++;
    }
    if (contador == 2) {
        addFumo(); // Isso acontece uma única vez no segundo instante
    }
    if(flag == 1){
        contadorDesliga ++;
        if(contadorDesliga == 5){
            on = false;
            props.at(1)->setValor(props.at(1)->getValor() - 100);
            contador = 0;
            flag = 0;
            contadorDesliga = 0;
        }
    }
}

void Aspersor::desliga() {
    if (on) {
        flag = 1;
//        on = false;
//        props.at(1)->setValor(props.at(1)->getValor() - 100);
//
//        contadorDesliga = 5;
    }
}

void Aspersor::addHumidade() {
    if (props.at(0)->getValor() < 75) {
        props.at(0)->setValor(props.at(0)->getValor() + 50);
    }
}

void Aspersor::addVibracao() {
    props.at(1)->setValor(100);
}

void Aspersor::addFumo() {
    props.at(2)->setValor(0);
}