#include <sstream>
#include <utility>
#include "Propriedade.h"

using namespace std;
int Propriedade::contadorProps = 0;

Propriedade::Propriedade(std::string  nome, double valor, std::string  unidadeMedida, const string& letra, double min)
: nome(std::move(nome)), valor(valor), unidadeMedida(std::move(unidadeMedida)), min(min) {
    ostringstream os;
    os << letra <<  ++contadorProps;
    id = os.str();
}

Propriedade::~Propriedade()= default;

const string &Propriedade::getNome() const {
    return nome;
}

double Propriedade::getValor() const {
    return valor;
}

const string &Propriedade::getId() const {
    return id;
}


void Propriedade:: setValor(double valorApa) {
    if(valorApa >= min){
        valor = valorApa;
    }else {
        valor = min;
    }
}



