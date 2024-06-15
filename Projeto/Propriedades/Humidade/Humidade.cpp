#include "Humidade.h"

Humidade::Humidade(double valor): Propriedade("humidade", valor, "%", "h", 0), max(100) {}


void Humidade::setValor(double valorApa) {
    if (valorApa > max) {
        Propriedade::setValor(max);
    } else {
        Propriedade::setValor(valorApa);
    }
}
