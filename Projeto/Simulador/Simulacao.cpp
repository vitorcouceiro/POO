#include <sstream>
#include <fstream>
#include "Simulacao.h"

using namespace std;
using namespace term;


const map<string, int> Simulacao::comandos{
        {"sair", 0},
        {"prox", 1},
        {"avanca", 2},
        {"hnova", 3},
        {"hrem", 4},
        {"znova", 5},
        {"zrem",6},
        {"zlista", 7},
        {"zcomp", 8},
        {"zprops", 9},
        {"pmod", 10},
        {"cnovo", 11},
        {"crem", 12},
        {"rnova", 13},
        {"pmuda", 14},
        {"rlista", 15},
        {"rrem", 16},
        {"asoc", 17},
        {"ades", 18},
        {"acom", 19},
        {"psalva", 20},
        {"prepoe", 21},
        {"prem", 22},
        {"plista", 23},
        {"exec", 24},
        {"clear", 25}
};

Simulacao::Simulacao(Habitacao *h): habitacao(h), x(-1), y(-1){}

void Simulacao::validaComando(const string& linha,term::Window& w2_output){
    string comando, restoLinha;

    istringstream iss(linha);
    iss >> comando;
    getline(iss, restoLinha);

    istringstream is(restoLinha);

    auto opcao = comandos.find(comando);

    if (opcao != comandos.end()) {
        switch (opcao->second) {
            case 0:
                exit(1);
            case 1:  // prox
                if(!executaProx(w2_output) && restoLinha.empty())
                    w2_output << "Erro! Argumentos a mais.\n";
                break;
            case 2:  // avanca <n>
                if(!executaAvanca(is,w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 3: // hnova <nlinhas> <ncolunas>
                if(!executaHNova(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 4:// hrem
                if(restoLinha.empty())
                    executaHrem(w2_output);
                else
                    w2_output << "Erro! Argumentos a mais.\n";
                break;
            case 5: // znova <linha> <coluna>
                if(!executaZNova(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 6: // zrem <ID zona>
                if(!executaZRem(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 7:// zlista
                if(restoLinha.empty())
                    executaZlista(w2_output);
                else
                    w2_output << "Erro! Argumentos a mais.\n";
                break;
            case 8:// zcomp <ID zona>
                if(!executaZcomp(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 9:// zprops <ID zona>
                if(!executaZprops(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 10: // pmod <ID zona> <nome> <valor>
                if(!executaPMod(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 11: // cnovo <ID zona> <s | p | a> <tipo | comando>
                if(!executaCNovo(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 12: // ccrem  <ID zona> <s | p | a> <tipo | comando>
                if(!executaCrem(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 13: // rnova <ID zona> <ID proc. regras> <regra> <ID sensor> [param1] [param2] [...]
                if(!executaRnova(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 14: // pmuda <ID zona> <ID proc. regras> <novo comando>
                if(!executaPmuda(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 15: // rlista <ID zona> <ID proc. regras>
                if(!executaRlista(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 16: // rrem <ID zona> <ID proc. regras> <ID regra>
                if(!executaRrem(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 17: // asoc <ID zona> <ID proc. regras> <ID aparelho>
                if(!executaAsoc(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 18: // ades <ID zona> <ID proc. regras> <ID aparelho>
                if(!executaAdes(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 19: // acom <ID zona> <ID aparelho> <comando>
                if(!executaAcom(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 20: // psalva <ID zona> <ID proc. regras> <nome>
                if(!executaPsalva(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 21: // prepoe <nome>
                if(!executaPrepoe(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 22: // prem <nome>
                if(!executaPrem (is,w2_output)){
                    w2_output << "Comando invalido.\n";
                }
                break;
            case 23: // plista
                if(restoLinha.empty())
                    executaPlista(w2_output);
                else
                    w2_output << "Erro! Argumentos a mais.\n";
                break;
            case 24: // exec <nome de ficheiro>
                if(!leFicheiro(is, w2_output))
                    w2_output << "Comando invalido.\n";
                break;
            case 25: //clear
                if(restoLinha.empty())
                    executaClear(w2_output);
                else
                    w2_output << "Erro! Argumentos a mais.\n";
                break;
        }
    } else{
        w2_output << "Comando invalido ou nao implementado\n";
    }
}

void Simulacao::executa(){
    int contador = 0;
    int cont_linhas_w2 = 0;
    string linha;
    Terminal &t = Terminal::instance();

    for(int i=1; i<20; i++) {
        t.init_color(i, i, 0);
    }

    t << move_to(3,0) << set_color(13) << "Bem Vindo! Para comecar a simulacao insira o comando 'hnova <linhas> <colunas>' para criar uma habitacao.\n";

    Window w1_cmd = term::Window(1,35,90,5);
    Window w2_output = term::Window(91, 1, 58, 39);

    while(true) {
        if(contador == 3){
            w1_cmd.clear();
            contador = 0;
        }

        w1_cmd << "('sair' para encerrar) Comando> ";
        w1_cmd >> linha;

        validaComando(linha, w2_output);

        cont_linhas_w2 ++;
        if (cont_linhas_w2 == 20) {
            w2_output.clear();
            cont_linhas_w2 = 0;
        }

        contador++;
    }
}

bool Simulacao::executaProx(Window &w2_output){
    if(habitacao != nullptr){
        habitacao->avaliaZona();
        w2_output << "Comando Prox executado com sucesso!!\n";
        return true;
    }else{
        w2_output << "Erro!Nao existe nenhuma habitacao.\n";
    }
    return false;
}

bool Simulacao::executaAvanca(istringstream &restoLinha,Window &w2_output){
    int instante ;
    if(restoLinha >> instante){
        for(int i=0;i<instante;i++){
            if(habitacao != nullptr){
                habitacao->avaliaZona();
            }else{
                w2_output << "Erro!Nao existe nenhuma habitacao.\n";
                return false;
            }
        }
        w2_output << "Comando Avanca executado com sucesso!!\n";
        return true;
    }else{
        w2_output << "Erro!Argumentos invalidos.\n";
    }
    return false;
}

bool Simulacao::executaHNova(istringstream &restoLinha,Window &w2_output) {
    int nLinhas, nColunas ;
    if(restoLinha >> nLinhas && restoLinha >> nColunas) {
        x = nLinhas; y = nColunas;
        if(habitacao == nullptr){
            if(nLinhas >= 2 && nLinhas <= 4 && nColunas  >= 2 && nColunas  <= 4){
                pjanelas = criaJanelasHab(nLinhas, nColunas);
                habitacao = new Habitacao(nLinhas, nColunas);
                w2_output << "Habitacao criada com sucesso!\n";
                return true;
            }else{
                w2_output << "Erro! Verifique as dimensoes da habitacao.\n";
            }
        }else{
            w2_output << "Habitacao ja existe!\n";
        }
    }else{
        w2_output << "Erro!Argumentos invalidos.\n";
    }
    return false;
}

Window*** Simulacao::criaJanelasHab (int nlinhas, int ncolunas){
    if(pjanelas == nullptr) {
        pjanelas = new Window ** [nlinhas];
        for(int linha = 0, yAux = 2; linha < nlinhas; linha++, yAux += 8)
        {
            pjanelas[linha] = new Window* [ncolunas];
            for(int coluna = 0, xAux = 7; coluna < ncolunas; coluna++, xAux += 20)
            {
                pjanelas[linha][coluna] = new Window (xAux, yAux, 17, 8);
                *pjanelas[linha][coluna] << move_to(0, 0) << "__";
            }
        }
    }
    return pjanelas;
}

bool Simulacao::executaHrem(Window &w2_output){
    if (pjanelas != nullptr) {

        int nLinhas = habitacao->getNumLinhas();
        int nColunas = habitacao->getNumColunas();

        for (int linha = 0; linha < nLinhas; linha++) {
            for (int coluna = 0; coluna < nColunas; coluna++) {
                delete pjanelas[linha][coluna];
            }
            delete[] pjanelas[linha];
        }

        delete[] pjanelas;
        pjanelas = nullptr;

        delete habitacao;
        habitacao = nullptr;

        x = -1; y= -1;
        w2_output << "Habitacao apagada com sucesso!\n";
        return true;
    }
    w2_output << "Erro! Certefique-se que a habitacao foi inicializada corretamente.\n";
    return false;
}

bool Simulacao::executaZNova(istringstream &restoLinha,Window& w2_output){
    int nlinhas, ncolunas;
    if(restoLinha >> nlinhas && restoLinha >> ncolunas) {

        if(habitacao != nullptr){
            if(habitacao->verificaDimensoes(nlinhas-1, ncolunas - 1) && habitacao->verificaZonaLivre(nlinhas - 1, ncolunas - 1)){
                if(habitacao->addZona(new Zona(nlinhas-1, ncolunas - 1), pjanelas)) {
                    w2_output << "Nova zona criada com sucesso!\n";
                    return true;
                }
            }else{
                w2_output << "Erro! Verifique as dimensoes e a disponibilidade da habitacao.\n";
            }
        }else{
            w2_output << "Erro! A habitacao nao foi inicializada.\n";
        }
    }else{
        w2_output << "Erro!Argumentos invalidos.\n";
    }
    return false;
}

bool Simulacao::executaZRem(istringstream &restoLinha,Window& w2_output) {
    string idZona;
    if(restoLinha >> idZona){
        if (habitacao != nullptr) {
            if (habitacao->removeZona(idZona,pjanelas)) {
                w2_output << "Zona removida com sucesso\n";
                return true;
            }else{
                w2_output << "Erro!Verifique se o id esta correto\n";
            }
        }else{
            w2_output << "Erro!Nao existe nenhuma habitacao.\n";
        }
    }else{
        w2_output << "Erro!Argumentos invalidos.\n";
    }
    return false;
}

bool Simulacao::executaZlista(Window& w2_output) {
    if (habitacao == nullptr) {
        w2_output << "Erro!Nao existe uma habitacao.\n";
        return false;
    }

    for (int i = 0; i < habitacao->getNumLinhas(); ++i) {
        for (int j = 0; j < habitacao->getNumColunas(); ++j) {
            Zona* zona = habitacao->getZona(i, j);


            if (zona != nullptr) {
                w2_output << "------Zona " << zona->getId() << "------" << "\n";

                w2_output << "  Sensores: " << static_cast<int>(zona->getNumSensores()) << "\n";

                w2_output << "  Processadores: " << static_cast<int>(zona->getNumProcessadores()) << "\n";

                w2_output << "  Aparelhos: " << static_cast<int>(zona->getNumAparelhos()) << "\n";

            }
        }
    }

    return true;
}

bool Simulacao::executaZcomp(istringstream &restoLinha,Window& w2_output){
    string idZona;
    if(restoLinha >> idZona){
        if(habitacao != nullptr){
            Zona* zona = habitacao->getZonaByID(idZona);
            if (zona != nullptr) {

                const vector<Sensor*>& sens = zona->getListaSensores();
                for (const auto &sen : sens) {
                    Propriedade* prop = sen->getPropriedade();
                    w2_output << "Tipo: s, ID: " << sen->getId() << ", Nome: " << sen->getNome() << ", Valor:" << prop->getValor() << "\n";
                }

                const vector<Aparelho*>& apars = zona->getListaAparelhos();
                for (const auto &apar : apars) {
                    w2_output << "Tipo: a, ID: " << apar->getId() << ", Nome: " << apar->getNome() << ", Ultimo Estado:"<< apar->getComando() <<"\n";
                }

                const vector<Processador*>& procs = zona->getListaProcessadores();
                for (const auto &proc : procs) {
                    w2_output << "Tipo: p, ID: " << proc->getId() << ", Nome: processador, Numero de Regras: " <<  static_cast<int>(proc->getNumRegras()) << "\n";
                }
                return true;
            }else{
                w2_output << "Erro!Verifique o id da Zona.\n";
            }
        }else{
            w2_output << "Erro!Nao existe uma habitacao.\n";
        }
    }else{
        w2_output << "Erro!Argumentos invalidos.\n";
    }
    return false;
}

bool Simulacao::executaZprops(istringstream &restoLinha, Window& w2_output) {
    string idZona;
    if (restoLinha >> idZona) {
        if (habitacao != nullptr) {
            Zona* zona = habitacao->getZonaByID(idZona);
            if (zona != nullptr) {
                //w2_output << "entrou\n";
                const vector<Propriedade *> &props = zona->getListaPropriedades();
                for (const auto &prop : props) {
                    w2_output << "Propriedade -> " << prop->getNome() << "\n";
                    w2_output << "Valor: " << prop->getValor() << "\n";
                }
                return true;
            }else{
                w2_output << "Erro!Verifique o id da Zona.\n";
            }
        }else{
            w2_output << "Erro!Nao existe uma habitacao.\n";
        }
    }else{
        w2_output << "Erro!Argumentos invalidos.\n";
    }
    return false;
}

bool Simulacao::executaPMod (istringstream  &restoLinha, Window& w2_output){
    string id, nome;
    double valor;
    if(restoLinha >> id && restoLinha >> nome && restoLinha >> valor){
        if(habitacao->alteraPropriedade(id, nome, valor, w2_output)){
            return true;
        }else{
            w2_output << "Nao foi possivel alterar prop.\n";
            return false;
        }
    }else{
        w2_output << "Erro!Argumentos invalidos.\n";
    }
    return false;
}

bool Simulacao::executaCNovo(istringstream  &restoLinha,Window& w2_output){
    string idZona,letra, tipo;
    if(restoLinha >> idZona && restoLinha >> letra && restoLinha >> tipo){
        if(habitacao != nullptr){

            Zona* zona = habitacao->getZonaByID(idZona);
            if (zona != nullptr) {
                int linha = zona->getY();
                int coluna = zona->getX();

                string str = habitacao->adicionaComponente(zona, tipo, letra);
                if (!str.empty()) {
                    displayComponentes(letra, linha, coluna, str, zona);
                    w2_output << "Componente adicionado com sucesso!\n";
                    return true;
                }else{
                    w2_output << "Nao foi possivel adicionar componente.\n";
                }
            }else{
                w2_output << "Erro!Verifique o id da Zona.\n";
            }
        }else{
            w2_output << "Erro!Nao existe uma habitacao.\n";
        }
    }else{
        w2_output << "Erro!Argumentos invalidos.\n";
    }
    return false;
}

void Simulacao::displayComponentes(const std::string &letra, int corx, int cory, const std::string &str, Zona *zona) {
    int numAparelhos = static_cast<int>(zona->getNumAparelhos());
    int numSensores = static_cast<int>(zona->getNumSensores()) ;
    int numProcessadores = static_cast<int>(zona->getNumProcessadores());

    if(letra == "a" && numAparelhos <= 5){
        *pjanelas[corx][cory] << move_to(numAparelhos * 2,1) << str;
    } else if (letra == "p" && numProcessadores <= 5) {
        *pjanelas[corx][cory] << move_to(numProcessadores * 2, 3) << str;
    } else if (letra == "s" && numSensores <= 5) {
        *pjanelas[corx][cory] << move_to(0 + numSensores * 2,4) << str;
    }
}

bool Simulacao::executaCrem(istringstream &restoLinha, Window &w2_output) {
    string idZona, letra, idComponente;
    if (restoLinha >> idZona && restoLinha >> letra && restoLinha >> idComponente) {
        if (habitacao != nullptr) {
            Zona *zona = habitacao->getZonaByID(idZona);
            if (zona != nullptr) {
                if (habitacao->removeComponte(zona, letra, idComponente)) {
                    w2_output << "Componente removido.\n";
                    atualizarDisplay(zona);
                    return true;
                } else {
                    w2_output << "Nao foi possivel remover componente.\n";
                }
            } else {
                w2_output << "Erro!Verifique o id da Zona.\n";
            }
        } else {
            w2_output << "Erro!Nao existe uma habitacao.\n";
        }
    } else {
        w2_output << "Erro!Argumentos invalidos.\n";
    }
    return false;
}

void Simulacao::atualizarDisplay(Zona *zona){
    int localx = zona->getX();
    int localy = zona->getY();
    int numAparelhos = 2;
    int numSensores = 2;
    int numProcessadores = 2;

    for(int i=0;i<18;i++){
        for(int j=0;j<4;j++){
            *pjanelas[localx][localy] << move_to(i, j) << " ";
        }
    }

    *pjanelas[localx][localy] << move_to(0, 0) << zona->getId();

    const vector<Sensor *> &sensores = zona->getListaSensores();
    for (const auto &sensor : sensores) {
        if(numSensores<=11){
            *pjanelas[localx][localy] << move_to( numSensores ,4) << sensor->getId();
        }
        numSensores+=2;
    }

    const vector<Aparelho *> &aparelhos = zona->getListaAparelhos();
    for (const auto &aparelho : aparelhos) {
        if(numAparelhos<=11) {
                *pjanelas[localx][localy] << move_to(numAparelhos, 1) << aparelho->getId();
        }
        numAparelhos+=2;
    }

    const vector<Processador *> &processadores = zona->getListaProcessadores();
    for (const auto &processador : processadores) {
        if(numProcessadores<=11) {
            *pjanelas[localx][localy] << move_to(numProcessadores, 3) << processador->getId();
        }
        numProcessadores+=2;
    }

}

bool Simulacao::executaRnova(std::istringstream  &restoLinha,term::Window& w2_output){
    string idZona, idProc, regra, idSensor;
    vector <int> parametros;
    int token;
    if(restoLinha >> idZona && restoLinha >> idProc && restoLinha >> regra && restoLinha >> idSensor) {
        while (restoLinha >> token) {
            parametros.emplace_back(token);
        }

        if (habitacao != nullptr) {
            Zona *zona = habitacao->getZonaByID(idZona);
            if (zona != nullptr) {
                if(habitacao->addRegraProc(regra, zona,idProc, parametros, idSensor)){
                    atualizaDisplayRegra(zona,idProc);
                    w2_output << "Regra adicionada com sucesso ao processador " << idProc << "!\n";
                    return true;
                }else
                    w2_output << "Nao foi possivel adicionar a regra ao processador " << idProc << "!\n";
            }else {
                w2_output << "Erro!Verifique o id da Zona.\n";
            }
        }else {
            w2_output << "Erro!Nao existe uma habitacao.\n";
        }
    }
    return false;
}  //--> nao sei se esta efetivamente a adicionar


bool Simulacao::executaPmuda(istringstream  &restoLinha,Window& w2_output){
    string idZona, idProc, comando;
    if(restoLinha >> idZona && restoLinha >> idProc && restoLinha >> comando){
        if (habitacao != nullptr) {
            Zona *zona = habitacao->getZonaByID(idZona);
            if (zona != nullptr) {
                habitacao->mudaComando(zona,idProc,comando);
                w2_output << "Comando alterado com sucesso!\n";
                return true;
            }else {
                w2_output << "Erro!Verifique o id da Zona.\n";
            }
        }else {
            w2_output << "Erro!Nao existe uma habitacao.\n";
        }
    }else{
        w2_output << "Argumentos inexistentes ou invalidos!\n";
    }
    return false;
}


bool Simulacao::executaRlista(istringstream &restoLinha, Window& w2_output) {
    string idZona, idProc;
    if (!(restoLinha >> idZona && restoLinha >> idProc)) {
        w2_output << "Argumentos inexistentes ou invalidos!\n";
        return false;
    }

    if (habitacao == nullptr) {
        w2_output << "Erro!Nao existe uma habitacao.\n";
        return false;
    }

    for (int i = 0; i < habitacao->getNumLinhas(); ++i) {
        for (int j = 0; j < habitacao->getNumColunas(); ++j) {
            Zona *zona = habitacao->getZona(i, j);

            if (zona != nullptr && zona->getId() == idZona) {
                const vector<Processador*>& lista = zona->getListaProcessadores();
                for (const auto& proc : lista) {
                    if(proc->getId() == idProc){
                        const vector<Regra*>& regras = proc->getRegras();
                        if (regras.empty()) {
                            w2_output << "Nao existem regras no proc: " << proc->getId() << "\n";
                        } else {
                            w2_output << "(Zona " << idZona << ") Regras no proc: " << proc->getId() << "\n";
                            for (const auto& regra : regras) {
                                Sensor* sensor = regra->getSensor();
                                w2_output << "Regra:" << regra->getTipo() << ",ID:" << regra->getId() << ",Sensor:" << sensor->getNome() << ",ID:" << sensor->getId() << "\n";
                            }
                        }
                    }
                }
                return true;
            }
        }
    }

    w2_output << "Erro!Verifique o id da Zona.\n";
    return false;
}


bool Simulacao::executaRrem (istringstream  &restoLinha, Window& w2_output){
    string idZona, idProc, idRegra;

    if(restoLinha >> idZona && restoLinha >> idProc && restoLinha >> idRegra) {
        if (habitacao != nullptr) {
            Zona *zona = habitacao->getZonaByID(idZona);

            if (zona != nullptr) {
                habitacao->removeRegraProc(zona, idProc, idRegra);
                atualizaDisplayRegra(zona,idProc);
                w2_output << "Regra eliminada com sucesso, do processador " << idProc << "!\n";
                return true;
            }else {
                w2_output << "Erro!Verifique o id da Zona.\n";
            }
        }else {
            w2_output << "Erro!Nao existe uma habitacao.\n";
        }
    }else{
        w2_output << "Argumentos inexistentes ou invalidos!\n";
    }
    return false;
}

void Simulacao::atualizaDisplayRegra(Zona* zona,const string& idProc){
    const vector<Processador*>& procs = zona->getListaProcessadores();
    int corx  = zona->getX();
    int cory  = zona->getY();

    for(int i=0;i<17;i++){
        *pjanelas[corx][cory] << move_to(i, 5) << " ";
    }

    for (const auto &proc : procs) {
        if(proc->getId() == idProc){
            const vector<Regra *> &regras = proc->getRegras();
            int index = 1;
            for (const auto &regra: regras) {
                *pjanelas[corx][cory] << move_to(index * 2, 5) << regra->getId();
                index++;
            }
        }
    }

}

bool Simulacao::executaAsoc (std::istringstream  &restoLinha, term::Window& w2_output){
    string idZona, idProc, idAparelho;

    if(restoLinha >> idZona && restoLinha >> idProc && restoLinha >> idAparelho) {
        if (habitacao != nullptr) {
            Zona *zona = habitacao->getZonaByID(idZona);
            if (zona != nullptr) {
                if(habitacao->associaAparelhoProc(idProc, idAparelho, zona))
                {
                    w2_output << "Aparelho associado com sucesso ao processador: " << idProc <<"!\n";
                    return true;
                } else
                    w2_output << "Nao foi possivel associar aparelho ao processador: " << idProc <<"!\n";
            }else {
                w2_output << "Erro!Verifique o id da Zona.\n";
            }
        }else {
            w2_output << "Erro!Nao existe uma habitacao.\n";
        }
    }else{
        w2_output << "Argumentos inexistentes ou invalidos!\n";
    }
    return false;
}

bool Simulacao::executaAdes (std::istringstream  &restoLinha, term::Window& w2_output){
    string idZona, idProc, idAparelho;

    if(restoLinha >> idZona && restoLinha >> idProc && restoLinha >> idAparelho) {
        if (habitacao != nullptr) {
            Zona *zona = habitacao->getZonaByID(idZona);
            if (zona != nullptr) {
                if(habitacao->desassociaAparelhoProc(idProc, idAparelho, zona))
                {
                    w2_output << "Aparelho desassociado com sucesso ao processador: " << idProc <<"!\n";
                    return true;
                } else
                    w2_output << "Nao foi possivel associar aparelho ao processador: " << idProc <<"!\n";
            }else {
                w2_output << "Erro!Verifique o id da Zona.\n";
            }
        }else {
            w2_output << "Erro!Nao existe uma habitacao.\n";
        }
    }else{
        w2_output << "Argumentos inexistentes ou invalidos!\n";
    }
    return false;
}

bool Simulacao::executaAcom(istringstream  &restoLinha, Window& w2_output){
    string idZona, idAparelho, comando;
    if(restoLinha >> idZona && restoLinha >> idAparelho && restoLinha >> comando) {
        if (habitacao != nullptr) {
            Zona *zona = habitacao->getZonaByID(idZona);
            if (zona != nullptr) {
                if(zona->mudaComando(idAparelho,comando)) {
                    w2_output << "Enviou o comando com sucesso!\n";
                    return true;
                } else{
                    w2_output << "Nao foi possivel mudar o comando!\n";
                }
            }else {
                w2_output << "Erro! Verifique o id da Zona.\n";
            }
        }else {
            w2_output << "Erro! Nao existe uma habitacao.\n";
        }
    }else{
        w2_output << "Argumentos inexistentes ou invalidos!\n";
    }
    return false;
}

bool Simulacao::executaPsalva (istringstream  &restoLinha, Window& w2_output){
    string idZona, idProc, nome;

    if(restoLinha >> idZona && restoLinha >> idProc && restoLinha >> nome) {
        if (habitacao != nullptr) {
            Zona *zona = habitacao->getZonaByID(idZona);
            if (zona != nullptr) {
                if(habitacao->salvaProcessador(idProc, nome, zona)) {
                    w2_output << "Processador " << idProc << " salvo com sucesso!\n";
                    return true;
                } else
                    w2_output << "Nao foi possivel salvar o processador!\n";
            }else {
                w2_output << "Erro! Verifique o id da Zona.\n";
            }
        }else {
            w2_output << "Erro! Nao existe uma habitacao.\n";
        }
    }else{
        w2_output << "Argumentos inexistentes ou invalidos!\n";
    }
    return false;
}

bool Simulacao::executaPrepoe (istringstream  &restoLinha, Window& w2_output){
    string nome;

    if(restoLinha >> nome) {
        if (habitacao != nullptr) {
            if(habitacao->repoeProcessador(nome)) {
                w2_output << "Processador reposto com sucesso!\n";
                return true;
            } else {
                w2_output << "Nao foi possivel repor o processador existente na copia com o nome: " << nome << "!\n";
                return true;
            }
        } else {
            w2_output << "Erro! Nao existe uma habitacao.\n";
            return true;
        }
    }else{
        w2_output << "Argumentos inexistentes ou invalidos!\n";
    }
    return false;
}

bool Simulacao::executaPrem (std::istringstream  &restoLinha, term::Window& w2_output){
    string nome;

    if(restoLinha >> nome) {
        if (habitacao != nullptr) {
            if(habitacao->removeCopiaProc(nome)) {
                w2_output << "Copia eliminada com sucesso!\n";
                return true;
            } else {
                w2_output << "Nao foi possivel eliminar a copia do processador com o nome: " << nome << "!\n";
                return true;
            }
        } else {
            w2_output << "Erro! Nao existe uma habitacao.\n";
            return true;
        }
    }else{
        w2_output << "Argumentos inexistentes ou invalidos!\n";
    }
    return false;

}

bool Simulacao::executaPlista(Window &w2_output) {
    if (habitacao == nullptr) {
        w2_output << "Erro!Nao existe uma habitacao.\n";
        return false;
    }

    map<string, Processador *> copias = habitacao->getCopiasProcs();
    if(!copias.empty()) {
        for (auto &copia: copias) {
            string nomeCopia = copia.first;
            Processador *proc = copia.second;
            string idProc = proc->getId();
            string idZona = proc->getIdZona();
            w2_output << "Nome: " << nomeCopia << ", ID Proc: " << idProc << ", ID Zona: " << idZona << "\n";
        }
    } else {
        w2_output << "Nao existem copias de processadores\n";
    }



    return true;
}

bool Simulacao::leFicheiro(istringstream& is, Window& w2_output) {
    int cont_linhas_w2 = 0;
    string nomeFicheiro;
    is >> nomeFicheiro;  // Extrai o nome do arquivo do istringstream

    ifstream arquivo(nomeFicheiro);  // Abre o arquivo usando o nome extraído

    if (!arquivo.is_open()) {
        w2_output << "Erro ao abrir o arquivo";
        return false;
    }

    std::string linha;
    while (getline(arquivo, linha)) {
        validaComando(linha, w2_output);
        cont_linhas_w2 ++;
        if (cont_linhas_w2 == 20) {
            w2_output.clear();
            cont_linhas_w2 = 0;
        }

    }

    arquivo.close();
    w2_output << "Leitura do arquivo concluida.\n";
    return true;
}

void Simulacao::executaClear(term::Window &w2_output) {
    w2_output.clear();
}

Simulacao::~Simulacao() {
    for(int i=0; i < x; i++){
        for (int j = 0; j < y; j++)
            delete pjanelas[i][j];   //como incializei a nullptr, não gera excecções
        delete [] pjanelas[i];
    }
    delete[] pjanelas;
    pjanelas = nullptr;
}