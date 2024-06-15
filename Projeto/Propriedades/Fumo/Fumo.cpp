#include "Fumo.h"

Fumo::Fumo(double valor): Propriedade("fumo", valor, "%", "f",0) , max(100){}

void Fumo::setValor(double valorApa) {
    if (valorApa > max) {
        Propriedade::setValor(max);
    } else {
        Propriedade::setValor(valorApa);
    }
}
