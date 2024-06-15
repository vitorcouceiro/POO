#include <sstream>
#include "Zona.h"
#include "../Propriedades/Fumo/Fumo.h"
#include "../Propriedades/Humidade/Humidade.h"
#include "../Propriedades/Luz/Luz.h"
#include "../Propriedades/Radiacao/Radiacao.h"
#include "../Propriedades/Temperatura/Temperatura.h"
#include "../Propriedades/Som/Som.h"
#include "../Propriedades/Vibracao/Vibracao.h"
#include "../Aparelhos/Aquecedor/Aquecedor.h"
#include "../Aparelhos/Aspersor/Aspersor.h"
#include "../Aparelhos/Lampada/Lampada.h"
#include "../Aparelhos/Refrigerador/Refrigerador.h"

class Habitacao;

using namespace term;
using namespace std;

int Zona::contadorZonas = 0;

Zona::Zona():id(" "), x(-1), y(-1){}

/*Zona::Zona(const Zona &outro){
    id = contadorZonas++;
    for(Sensor *s: outro.listaSensores){
        listaSensores.emplace_back(new Sensor(*s));
    }

    for(Aparelho *a: outro.listaAparelhos){
        listaAparelhos.emplace_back(new Aparelho(*a));
    }

    for(Processador *p: outro.listaProcessadores){
        listaProcessadores.emplace_back(new Processador(*p));
    }

    for(Propriedade *prop: outro.listaPropriedades){
        listaPropriedades.emplace_back(new Propriedade(*prop));
    }
}   //nao sei se vou utilizar este construtor*/

Zona::Zona(int linha, int coluna): x(linha), y(coluna){
    ostringstream os;
    os << "z" << ++contadorZonas;
    id = os.str();
    addPropriedades();
}

bool Zona::avaliaProcessador(){
    for(auto &processador : listaProcessadores){
        if(processador != nullptr){
            processador->validaRegra();
        }
    }
    return true;
}

const vector<Propriedade*>& Zona::getListaPropriedades() const {
    return listaPropriedades;
}


void Zona::addPropriedades(){
    listaPropriedades.emplace_back(new Fumo(0));
    listaPropriedades.emplace_back(new Humidade(0));
    listaPropriedades.emplace_back(new Luz(0));
    listaPropriedades.emplace_back(new Som(0));
    listaPropriedades.emplace_back(new Vibracao(0));
    listaPropriedades.emplace_back(new Radiacao(0));
    listaPropriedades.emplace_back(new Temperatura(0));
}

bool Zona::alteraPropriedade(const string& nome, double valor) {
    //verifica se a prop com esse nome existe
    for(auto & listaPropriedade : listaPropriedades){
        if(listaPropriedade->getNome() == nome){
            listaPropriedade->setValor(valor);
            return true;
        }
    }
    return false;
}

int Zona::getAparelhoByID(const std::string& id_code) const{
    for(int i = 0; i < listaAparelhos.size(); i++){
        if ( listaAparelhos.at(i)->getId() == id_code){
            return i;
        }
    }
    return -1;
}

int Zona::getSensorByID(const std::string& id_code) const{
    for(int i = 0; i < listaSensores.size(); i++){
        if ( listaSensores.at(i)->getId() == id_code){
            return i;
        }
    }
    return -1;
}

int Zona::getProcessadorByID(const std::string& id_code) const{
    for(int i = 0; i < listaProcessadores.size(); i++){
        if ( listaProcessadores.at(i)->getId() == id_code){
            return i;
        }
    }
    return -1;
}

int Zona::getPropriedadeByName (const std::string& nome) const{
    for(int i = 0; i < listaPropriedades.size(); i++){
        if ( listaPropriedades.at(i)->getNome() == nome){
            return i;
        }
    }
    return -1;
}
std::string Zona::addAparelho(const std::string& tipo){
    if(tipo == "aquecedor"){
        auto* aquecedor = new Aquecedor();
        if (getAparelhoByID(aquecedor->getId()) == -1) {  //verificar se este aparelho n existe

            int indexTemperatura = getPropriedadeByName("temperatura");         //associar respetivas propriedades
            int indexSom = getPropriedadeByName("som");
            aquecedor->associaProp(listaPropriedades.at(indexTemperatura));
            aquecedor->associaProp(listaPropriedades.at(indexSom));

            listaAparelhos.emplace_back(aquecedor);
            return aquecedor->getId();
        }
    } else if (tipo == "aspersor"){
        auto* aspersor = new Aspersor();
        if (getAparelhoByID(aspersor->getId()) == -1) {  //verificar se este aparelho n existe


            int indexHumidade= getPropriedadeByName("humidade");         //associar respetivas propriedades
            int indexVibracao = getPropriedadeByName("vibracao");
            int indexFumo = getPropriedadeByName("fumo");
            aspersor->associaProp(listaPropriedades.at(indexHumidade));
            aspersor->associaProp(listaPropriedades.at(indexVibracao));
            aspersor->associaProp(listaPropriedades.at(indexFumo));

            listaAparelhos.emplace_back(aspersor);
            return aspersor->getId();
        }
    }else if (tipo == "lampada") {

        auto *lampada = new Lampada();
        if (getAparelhoByID(lampada->getId()) == -1) {  //verificar se este aparelho n existe

            int indexLuz = getPropriedadeByName("luz");         //associar respetivas propriedades
            lampada->associaProp(listaPropriedades.at(indexLuz));

            listaAparelhos.emplace_back(lampada);
            return lampada->getId();
        }
    }else if (tipo == "refrigerador"){
        auto* refrigerador = new Refrigerador();
       if (getAparelhoByID(refrigerador->getId()) == -1) {  //verificar se este aparelho n existe

            int indexTemperatura = getPropriedadeByName("temperatura");         //associar respetivas propriedades
            int indexRuido = getPropriedadeByName("som");
            refrigerador->associaProp(listaPropriedades.at(indexTemperatura));
            refrigerador->associaProp(listaPropriedades.at(indexRuido));

           listaAparelhos.emplace_back(refrigerador);
           return refrigerador->getId();
       }
    }
    return "";
}
string Zona::addProcessador(string &comando){
    auto* proc = new Processador(comando);
    if (getProcessadorByID(proc->getId()) == -1){
        proc->setComando(comando);
        proc->setIdZona(this->id);   //adicionei o preenchimento do idZona no proc
        listaProcessadores.emplace_back(proc);
        return proc->getId();
    }
    return "";
}
string Zona::addSensor(const std::string& tipo){


        //so adiciona sensor se a propriedade existir
        if (tipo == "temperatura"){
            int indice = getPropriedadeByName(tipo);
            if(indice != -1){
                auto *senTemperatura = new Sensor(tipo, "t");
                if (getSensorByID(senTemperatura->getId()) == -1) {
                    senTemperatura->associaPropriedade(listaPropriedades.at(indice));  //associa a propriedade
                    listaSensores.emplace_back(senTemperatura);                        //adiciona o sensor a zona
                    return senTemperatura->getId();
                }
            }
        }else if (tipo == "movimento"){
            int indexVibra = getPropriedadeByName("vibracao");
            if(indexVibra != -1){
                auto *senMovimento = new Sensor(tipo, "v");
                if (getSensorByID(senMovimento->getId()) == -1) {  //verificar se este aparelho n existe
                    senMovimento->associaPropriedade(listaPropriedades.at(indexVibra));
                    listaSensores.emplace_back(senMovimento);
                    return senMovimento->getId();
                }
            }
        }else if (tipo == "luminosidade"){
            int indexLuz = getPropriedadeByName("luz");
            if(indexLuz != -1){
                auto *senLuz = new Sensor(tipo, "m");
                if (getSensorByID(senLuz->getId()) == -1) {  //verificar se este aparelho n existe
                    senLuz->associaPropriedade(listaPropriedades.at(indexLuz));
                    listaSensores.emplace_back(senLuz);
                    return senLuz->getId();
                }
            }
        }else if (tipo == "radiacao"){
            int indice = getPropriedadeByName(tipo);
            if(indice != -1){
                auto *senRadiacao = new Sensor(tipo, "d");
                if (getSensorByID(senRadiacao->getId()) == -1) {  //verificar se este aparelho n existe
                    senRadiacao->associaPropriedade(listaPropriedades.at(indice));
                    listaSensores.emplace_back(senRadiacao);
                    return senRadiacao->getId();
                }
            }
        }else if (tipo == "humidade") {
            int indice = getPropriedadeByName(tipo);
            if(indice != -1){
                auto *senHumidade = new Sensor(tipo, "h");
                if (getSensorByID(senHumidade->getId()) == -1) {  //verificar se este aparelho n existe
                    senHumidade->associaPropriedade(listaPropriedades.at(indice));
                    listaSensores.emplace_back(senHumidade);
                    return senHumidade->getId();
                }
            }
        } else if (tipo == "som") {
            int indice = getPropriedadeByName(tipo);
            if(indice != -1){
                auto *senSom = new Sensor(tipo, "o");
                if (getSensorByID(senSom->getId()) == -1) {  //verificar se este aparelho n existe
                    senSom->associaPropriedade(listaPropriedades.at(indice));
                    listaSensores.emplace_back(senSom);
                    return senSom->getId();
                }
            }
        } else if (tipo == "fumo") {
            int indice = getPropriedadeByName(tipo);
            if(indice != -1){
                auto *senFumo = new Sensor(tipo, "f");
                if (getSensorByID(senFumo->getId()) == -1) {  //verificar se este aparelho n existe
                    senFumo->associaPropriedade(listaPropriedades.at(indice));
                    listaSensores.emplace_back(senFumo);
                    return senFumo->getId();
                }
            }
        }

    return "";
}

bool Zona::removeSensor(const string& idSensor) {
    for (auto it = listaSensores.begin(); it != listaSensores.end(); ++it) {
        if ((*it)->getId() == idSensor) {
            delete *it;
            listaSensores.erase(it);
            return true;
        }
    }
    return false;
}

bool Zona::removeProcessador(const string& idProcessador) {
    for (auto it = listaProcessadores.begin(); it != listaProcessadores.end(); ++it) {
        if ((*it)->getId() == idProcessador) {
            delete *it;
            listaProcessadores.erase(it);
            return true;
        }
    }
    return false;
}

bool Zona::removeAparelho(const string& idAparelho) {
    for (auto it = listaAparelhos.begin(); it != listaAparelhos.end(); ++it) {
        if ((*it)->getId() == idAparelho) {
            delete *it;
            listaAparelhos.erase(it);
            return true;
        }
    }
    return false;
}



int Zona::getX() const {
    return x;
}

int Zona::getY() const {
    return y;
}

string Zona::getId() const {
    return id;
}

size_t Zona::getNumSensores() const {
    return listaSensores.size();
}

size_t Zona::getNumProcessadores() const {
    return listaProcessadores.size();
}

size_t Zona::getNumAparelhos() const {
    return listaAparelhos.size();
}

const vector<Sensor *> &Zona::getListaSensores() const {
    return listaSensores;
}

const vector<Aparelho *> &Zona::getListaAparelhos() const {
    return listaAparelhos;
}

const vector<Processador *> &Zona::getListaProcessadores() const {
    return listaProcessadores;
}


bool Zona::addRegraProc(const string& idProc, const string &nomeRegra, const vector<int> &parametros, const string& idSensor) {
    int indiceProc = getProcessadorByID(idProc);
    int indiceSensor = getSensorByID(idSensor);

    if(indiceProc != -1 && indiceSensor != -1 ){  //so adiciona se o processador e o sensor existirem
        Sensor* sen = listaSensores.at(indiceSensor);
        if(listaProcessadores.at(indiceProc)->adicionaRegra(nomeRegra, parametros, sen))
            return true;
        else
            return false;
    }
    return false;
}

bool Zona::removeRegraProc(const std::string& idProc, const std::string& idRegra){
    int indiceP = getProcessadorByID(idProc);

    if(indiceP != -1) {
        listaProcessadores.at(indiceP)->removeRegra(idRegra);
        return true;
    }
    return false;
}


bool Zona::mudaComandoProc(const string& idProc,const string& comando){
    int indiceProc = getProcessadorByID(idProc);
    if (indiceProc != -1) {
        listaProcessadores.at(indiceProc)->setComando(comando);
        return true;
    }
    return false;
}

bool Zona::mudaComando(const string& idAparelho,const string& comando){
    int indiceApa = getAparelhoByID(idAparelho);
    if (indiceApa != -1) {
        listaAparelhos.at(indiceApa)->setEstado(comando);
        return true;
    }
    return false;
}
bool Zona::associaAparelhoProc(const std::string& idProc,const std::string& idAparelho){

    int indiceProc = getProcessadorByID(idProc);
    int indiceAparelho = getAparelhoByID(idAparelho);

    if(indiceProc != -1 && indiceAparelho != -1){
        Aparelho* a = listaAparelhos.at(indiceAparelho);
        if(listaProcessadores.at(indiceProc)->associaAparelho(a))
            return true;
    }
    return false;
}

bool Zona::desassociaAparelhoProc(const std::string& idProc, const std::string& idAparelho) {

    int indiceProc = getProcessadorByID(idProc);
    int indiceAparelho = getAparelhoByID((idAparelho));
    if(indiceProc != -1 ){
        listaProcessadores.at(indiceProc)->desassociaAparelho(listaAparelhos.at(indiceAparelho));
        return true;
    }
    return false;
}

Zona::~Zona(){
    for(auto & listaSensor : listaSensores)
        delete listaSensor;
    for(auto & listaAparelho : listaAparelhos)
        delete listaAparelho;
    for(auto & listaProcessador : listaProcessadores)
        delete listaProcessador;
    for(auto & listaPropriedade : listaPropriedades)
        delete listaPropriedade;
}

Processador * Zona::fazCopiaProcessador(const std::string& idProc) {
    int indiceProc = getProcessadorByID(idProc);
    if(indiceProc != -1){
        auto * a = new Processador(*(listaProcessadores.at(indiceProc)));  //construtor por copia
        return a;
    }
    return nullptr;
}

bool Zona::repoeCopiaProcessador(Processador* procCopia){
    int index = getProcessadorByID(procCopia->getId());
    if( index != -1){
        listaProcessadores.at(index) = procCopia;
        return true;
    }
    return false;
}