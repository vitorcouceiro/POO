#include "Habitacao.h"
#include <sstream>
using namespace term;
using namespace std;

bool Habitacao::verificaDimensoes(int x, int y) const{
    return (x >= 0 && x < getNumLinhas() && y >= 0 && y < getNumColunas());
}

bool Habitacao::verificaZonaLivre(int x, int y) const{
    return (matriz_zonas[x][y] == nullptr);
}

/*string Habitacao::verificaID(std::string id) const {
    int indice=-1;
    for(int i = 0; i < num_linhas ; i++)
        for(int j = 0; j <num_colunas; j++)
            return indice = matriz_zonas[i][j]->getId();
}*/

bool Habitacao::avaliaZona(){
    for (int i = 0; i < num_linhas; ++i) {
        for (int j = 0; j < num_colunas; ++j) {
            Zona* zona = matriz_zonas[i][j];
            if (zona != nullptr) {
                zona->avaliaProcessador();
            }
        }
    }
    return true;
}

Habitacao::Habitacao() : Habitacao(2,2) {}


Habitacao::Habitacao(int nlinhas,int ncolunas):num_linhas(nlinhas),num_colunas(ncolunas){
    matriz_zonas = new Zona ** [num_linhas];
    for( int i= 0 ; i < nlinhas; i++)
        matriz_zonas[i] = new Zona * [num_colunas];

    for (int i=0; i < num_linhas;i++)             //preparo o array para receber as zonas (no inicio nao tem zonas  associadas)
        for(int j=0;j<num_colunas;j++)
            matriz_zonas[i][j]= nullptr;
}


Habitacao::~Habitacao()
{
    for(int i=0;i<num_linhas;i++) {
        for (int j = 0; j < num_colunas; j++)
            delete matriz_zonas[i][j];   //como incializei a nullptr, não gera excecções
        delete [] matriz_zonas[i];
    }
    delete[] matriz_zonas;

    for (auto & copiasProc : copiasProcs) {
        delete copiasProc.second;
    }
    copiasProcs.clear();
}

int Habitacao::getNumLinhas() const {
    return num_linhas;
}

int Habitacao::getNumColunas() const {
    return num_colunas;
}


bool Habitacao::addZona( Zona* a , Window*** pjanelas ){
    matriz_zonas[a->getX()][a->getY()] = a;
    *pjanelas[a->getX()][a->getY()] << move_to(0, 0) << a->getId();
    return true;
}

bool Habitacao::removeZona(const std::string& id, Window*** pjanelas) {
    Zona* zona = getZonaByID(id);

    if (zona != nullptr) {
        int x = zona->getX();
        int y = zona->getY();

        pjanelas[x][y]->clear();
        *pjanelas[x][y] << move_to(0, 0) << "--";

        matriz_zonas[x][y] = nullptr;
        delete zona;

        return true;
    }

    return false;
}


Zona* Habitacao::getZona(int x, int y) const {
    return matriz_zonas[x][y];
}

Zona* Habitacao::getZonaByID(const string& idZona) const {
    for (int i = 0; i < num_linhas; ++i) {
        for (int j = 0; j < num_colunas; ++j) {
            if (matriz_zonas[i][j] != nullptr && matriz_zonas[i][j]->getId() == idZona) {
                return matriz_zonas[i][j];
            }
        }
    }
    return nullptr;
}

bool Habitacao::alteraPropriedade(const std::string& id, const std::string& nomeProp, double valor, Window& w2_output){
    for(int i = 0; i < num_linhas; i++){
        for(int j = 0; j < num_colunas; j++){
            if(matriz_zonas[i][j]->getId() == id) {
                if (matriz_zonas[i][j]->alteraPropriedade(nomeProp, valor)) {   //altera prop
                    w2_output << "Propriedade alterada com sucesso!\n";
                    return true;
                } else {
                    w2_output << "Propriedade nao encontrada!\n";
                    return false;
                }
            }
        }
    }

    w2_output << "Erro!Verifica o Id.\n";  // Moved outside the loops
    return false;
}

std::string Habitacao::adicionaComponente(Zona* zona, std::string tipo, const std::string& letra){
    string idComponente;
    if( letra == "a"){
        idComponente = zona->addAparelho(tipo);
        return idComponente;
    }
    else if (letra == "s"){
        idComponente = zona->addSensor(tipo);
        return idComponente;
    }
    else if(letra == "p"){
        idComponente = zona->addProcessador(tipo);
        return idComponente;
    }
    return "";
}

bool Habitacao::removeComponte(Zona *zona, const string& letra, const string& idComponente){
    if(letra == "s"){
        return zona->removeSensor(idComponente);
    }else if(letra == "p"){
        return zona->removeProcessador(idComponente);
    }else if(letra == "a"){
        return zona->removeAparelho(idComponente);
    }
    return false;
}

bool Habitacao::addRegraProc(const std::string &regra, Zona *a, const std::string& idProc, const std::vector<int> &parametros, std::string& idSensor) {
    if(a->addRegraProc(idProc, regra, parametros, idSensor)){
        return true;
    }
    return false;
}

bool Habitacao::removeRegraProc(Zona *a, const std::string& idProc, const std::string& idRegra){
    if(a->removeRegraProc(idProc,idRegra)){
        return true;
    }
    return false;
}

bool Habitacao::mudaComando( Zona *a,const string& idProc,const string& comando){
    if(a->mudaComandoProc(idProc,comando))
        return true;
    return false;
}
bool Habitacao::associaAparelhoProc(const std::string& idProc, const std::string& idAparelho, Zona *a) {
    if(a->associaAparelhoProc(idProc,idAparelho))
        return true;
    return false;
}

bool Habitacao::desassociaAparelhoProc(const std::string& idProc, const std::string& idAparelho, Zona* a){
    if(a->desassociaAparelhoProc(idProc, idAparelho))
        return true;
    return false;
}

bool Habitacao::salvaProcessador(const std::string& idProc, const std::string& nomeCopia, Zona* a){
    Processador* proc = a->fazCopiaProcessador(idProc);
    if( proc != nullptr){
        copiasProcs.insert({nomeCopia, proc});
        return true;
    }

    return false;
}

bool Habitacao::repoeProcessador(const std::string& nomeCopia){
    auto it = copiasProcs.find(nomeCopia);
    if(it != copiasProcs.end()) {     //se existir uma copia com o nome inserido..
        Processador *proc = it->second;
        string idZona = proc->getIdZona();
        Zona * a = getZonaByID(idZona);
        if(a != nullptr ) {
            if (a->repoeCopiaProcessador(proc))
                return true;
        }
    }
    return false;
}


const map<std::string, Processador *> &Habitacao::getCopiasProcs() const {
    return copiasProcs;
}

bool Habitacao::removeCopiaProc(const std::string& nomeCopia){
    auto it = copiasProcs.find(nomeCopia);
    if (it != copiasProcs.end()) {  // Se existir uma cópia com o nome inserido...
        copiasProcs.erase(it);
        return true;
    }
    return false;
}