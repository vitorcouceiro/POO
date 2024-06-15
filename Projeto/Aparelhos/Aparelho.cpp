#include <string>
#include <sstream>
#include <utility>
#include "Aparelho.h"
#include "../Propriedades/Propriedade.h"

using namespace std;

int Aparelho::contadorAparelhos = 0;

Aparelho::Aparelho (std::string tipo, const string& letra) : nome(std::move(tipo)), on(false){
    ostringstream os;
    os << letra <<  ++contadorAparelhos;
    id = os.str();
}

const std::string &Aparelho::getId() const {
    return id;
}

const std::string &Aparelho::getNome() const{
    return nome;
}

void Aparelho::liga(){
    if (!on)
        on = true;
}

void Aparelho::desliga(){
    if(on)
        on=false;
}

void Aparelho::associaProp(Propriedade * p){
    props.emplace_back(p);
}

string Aparelho::getComando(){
    string comando;
    if(on){
        comando = "ligado";
    }else{
        comando = "desligado";
    }
    return comando;
}

bool Aparelho::setEstado(const string& comandoUt){
    if(comandoUt == "desliga"){
        desliga();
        return true;
    }else if(comandoUt == "liga"){
        liga();
        return true;
    }
    return false;
}

