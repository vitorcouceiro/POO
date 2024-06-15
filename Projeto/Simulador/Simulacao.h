#ifndef TP_POO_2324_SIMULACAO_H
#define TP_POO_2324_SIMULACAO_H

#include "../Habitacao/Habitacao.h"
#include "../Zonas/Zona.h"
#include "../Library/Terminal.h"


class Simulacao {
    Habitacao *habitacao = nullptr;
    static const std::map <std::string, int> comandos;
    term::Window *** pjanelas = nullptr;
    int x,y;

public:
    explicit Simulacao(Habitacao *h);

    [[noreturn]] void executa();
    void validaComando(const std::string& linha,term::Window& w2_output);

    bool leFicheiro(std::istringstream& is, term::Window& w2_output);

    bool executaProx(term::Window &w2_output);//verifica regra

    bool executaAvanca(std::istringstream &restoLinha,term::Window &w2_output);

    bool executaHNova(std::istringstream &restoLinha, term::Window &w2_output);
    bool executaHrem(term::Window &w2_output);
    bool executaZNova(std::istringstream &restoLinha,term::Window& w2_output);
    bool executaZRem(std::istringstream &restoLinha,term::Window& w2_output);
    bool executaZlista(term::Window& w2_output);
    bool executaZprops(std::istringstream &restoLinha, term::Window& w2_output) ;
    bool executaZcomp(std::istringstream &restoLinha, term::Window& w2_output);
    bool executaPMod (std::istringstream  &restoLinha, term::Window& w2_output);
    bool executaCNovo(std::istringstream  &restoLinha,term::Window& w2_output);
    void displayComponentes(const std::string &letra, int corx, int cory, const std::string &str, Zona *zona);
    bool executaCrem(std::istringstream  &restoLinha,term::Window& w2_output);
    void atualizarDisplay(Zona *zona);
    bool executaRnova(std::istringstream  &restoLinha,term::Window& w2_output);
    bool executaPmuda(std::istringstream  &restoLinha,term::Window& w2_output);
    bool executaRlista(std::istringstream  &restoLinha, term::Window& w2_output);
    bool executaRrem (std::istringstream  &restoLinha, term::Window& w2_output);
    void atualizaDisplayRegra(Zona* zona,const std::string& idProc);
    bool executaAsoc (std::istringstream  &restoLinha, term::Window& w2_output);
    bool executaAdes (std::istringstream  &restoLinha, term::Window& w2_output);
    bool executaAcom(std::istringstream  &restoLinha, term::Window& w2_output);
    bool executaPsalva(std::istringstream  &restoLinha, term::Window& w2_output);
    bool executaPrepoe (std::istringstream  &restoLinha, term::Window& w2_output);
    bool executaPrem (std::istringstream  &restoLinha, term::Window& w2_output);
    bool executaPlista(term::Window &w2_output);
    static void executaClear(term::Window &w2_output);
    term::Window*** criaJanelasHab (int nlinhas, int ncolunas);

    ~Simulacao();
};


#endif //TP_POO_2324_SIMULACAO_H