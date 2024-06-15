#ifndef TP_POO_2023_HABITACAO_H
#define TP_POO_2023_HABITACAO_H
#include <vector>
#include "../Zonas/Zona.h"
#include "../Library/Terminal.h"

class Habitacao {
    Zona *** matriz_zonas;
    int num_linhas, num_colunas;
    //const int verificaID(std::string id)const;
    std::map<std::string, Processador*> copiasProcs;
public:
    Habitacao();
    Habitacao(int nlinhas,int ncolunas);
    ~Habitacao();

    bool avaliaZona();

    [[nodiscard]] int getNumLinhas() const;
    [[nodiscard]] int getNumColunas() const;


    [[nodiscard]] Zona* getZona(int x, int y) const;
    [[nodiscard]] Zona* getZonaByID(const std::string& idZona) const;

    [[nodiscard]] const std::map<std::string, Processador *> &getCopiasProcs() const;


    //bool criaHabitacao(int nLinhas, int nColunas);  //duvidas se
    bool addZona(Zona *a, term::Window ***pjanelas);
    bool removeZona(const std::string& id, term::Window*** pjanelas);


    [[nodiscard]] bool verificaDimensoes(int x, int y) const;
    [[nodiscard]] bool verificaZonaLivre(int x, int y) const;

    bool alteraPropriedade(const std::string& id, const std::string& nomeProp, double valor, term::Window& w2_output);

    std::string adicionaComponente(Zona* zona, std::string tipo, const std::string& letra);
    bool removeComponte(Zona *zona,const std::string& letra,const std::string& idComponente);

    bool addRegraProc(const std::string &regra, Zona *a, const std::string& idProc, const std::vector<int> &parametros, std::string& idSensor);
    bool removeRegraProc(Zona *a, const std::string& idProc, const std::string& idRegra);
    bool mudaComando( Zona *a, const std::string& idProc, const std::string& comando);
    bool associaAparelhoProc(const std::string& idProc, const std::string& idAparelho, Zona *a);
    bool desassociaAparelhoProc(const std::string& idProc, const std::string& idAparelho, Zona* a);
    bool salvaProcessador(const std::string& idProc, const std::string& nomeCopia, Zona* a);
    bool repoeProcessador(const std::string& nomeCopia);
    bool removeCopiaProc(const std::string& nomeCopia);

};

#endif //TP_POO_2023_HABITACAO_H