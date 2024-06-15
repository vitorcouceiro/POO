#include "Processador.h"
#include "../Aparelhos/Aparelho.h"
#include "../Sensores/Sensor.h"
#include "../Regras/Entre/Entre.h"
#include "../Regras/Fora/Fora.h"
#include "../Regras/Igual/Igual.h"
#include "../Regras/Maior/Maior.h"
#include "../Regras/Menor/Menor.h"
#include <vector>
#include <sstream>
using namespace std;

int Processador::contProcessadores = 0;

Processador::Processador(std::string &cmd): comando(cmd){
    ostringstream os;
    os << "p" <<  ++contProcessadores;
    id = os.str();
}

Processador::Processador(const Processador & outro){
    *this = outro;
}

Processador & Processador::operator=(const Processador & outro){
    if (this != &outro) {
        for (Regra *r: regras)
            delete r;
        regras.clear();

        for (Regra *r: outro.regras)
            regras.emplace_back(r->duplica());

        for (Aparelho *a: outro.aparelhos)
            aparelhos.emplace_back(a->duplica());

        id = outro.id;
        idZona = outro.idZona;
        comando = outro.comando;

    }
    return *this;
}



int Processador::getAparelhoByID(const std::string& id_code) const{
    for(int i = 0; i < aparelhos.size(); i++){
        if ( aparelhos.at(i)->getId() == id_code){
            return i;
        }
    }
    return -1;
}


const std::string &Processador::getId() const {
    return id;
}

bool Processador::adicionaRegra(const std::string &tipo, const std::vector<int> &parametros, Sensor *sensor) {

    if(tipo == "entre") {
        if( parametros.size() == 2) {
            Regra * r = new Entre(parametros.at(0), parametros.at(1));
            this->regras.emplace_back(r);
            r->associaSensor(sensor);
            return true;
        }
    }else if(tipo == "fora"){
        if( parametros.size() == 2){
            Regra * r = new Fora(parametros.at(0), parametros.at(1));
            this->regras.emplace_back(r);
            r->associaSensor(sensor);
            return true;
        }
    }else if(tipo == "igual"){
        if( parametros.size() == 1){
            Regra * r = new Igual(parametros.at(0));
            this->regras.emplace_back(r);
            r->associaSensor(sensor);
            return true;
        }
    } else if(tipo == "maior"){
        if( parametros.size() == 1){
            Regra * r = new Maior(parametros.at(0));
            this->regras.emplace_back(r);
            r->associaSensor(sensor);
            return true;
        }
    }
    else if(tipo == "menor"){
        if( parametros.size() == 1){
            Regra * r = new Menor(parametros.at(0));
            this->regras.emplace_back(r);
            r->associaSensor(sensor);
            return true;
        }
    }
    return false;
}


bool Processador::removeRegra(const std::string & id_code){
    for (auto it = regras.begin(); it != regras.end(); ++it) {
        if ((*it)->getId() == id_code) {

            delete *it;
            regras.erase(it);
            return true;
        }
    }
    return false;
}


size_t Processador::getNumRegras() const {
    return regras.size();
}

void Processador::setComando(const string &comandoN) {
    Processador::comando = comandoN;
}

const vector<Regra *> &Processador::getRegras() const {
    return regras;
}

Processador::~Processador(){
    for(auto & regra : regras)
        delete regra;
}

bool Processador::associaAparelho (Aparelho* a){
    if(getAparelhoByID(a->getId()) == -1) {  //se o aparelho nao existir adiciono
        aparelhos.emplace_back(a);
        return true;
    }
    return false;
}

void Processador::desassociaAparelho(Aparelho* a){
    if(a != nullptr) {
        for (int i = 0; i < aparelhos.size(); i++)
            if (a->getId() == aparelhos[i]->getId()) {
                delete aparelhos[i];
                aparelhos.erase(aparelhos.begin() + i);
                break;
            }
    }
}

const string &Processador::getIdZona() const {
    return idZona;
}

void Processador::setIdZona(const string &idZonaN) {
    Processador::idZona = idZonaN;
}

bool Processador::validaRegra() {
    int contador = 0;
    for (auto *regra : regras) {
        Sensor *sensor = regra->getSensor();
        double valorPropriedade = sensor->getPropriedade()->getValor();
        if (regra->verificaRegra(valorPropriedade)) {
            contador++;
        }
    }
    if(contador == regras.size()){
       for(auto * a: aparelhos)
            if(a != nullptr){
                a->setEstado(comando);
        }
        return true;
    }
    return false;
}
