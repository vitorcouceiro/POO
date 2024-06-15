#ifndef TP_POO_2023_PROCESSADOR_H
#define TP_POO_2023_PROCESSADOR_H
#include <iostream>
#include <vector>
#include "../Regras/Regra.h"
#include "../Library/Terminal.h"

//agregacao
class Aparelho;

class Processador{
    static int contProcessadores;
    std::string id;
    std::string comando;   //output do processador a enviar ao aparelho
    std::vector <Regra*> regras;  //composicao
    std::vector <Aparelho*> aparelhos;    //associacao
    std::string idZona;

public:
    explicit Processador(std::string &cmd);

    Processador(const Processador & outro);                   //construtor por copia

    Processador & operator=(const Processador & outro);        //redefinicao do operator=

    ~Processador();

    [[nodiscard]] int getAparelhoByID(const std::string& id_code) const;

    [[nodiscard]] const std::vector<Regra *> &getRegras() const;

    bool adicionaRegra(const std::string &tipo, const std::vector<int> &parametros, Sensor *sensor);

    bool removeRegra(const std::string & id_code);

    bool associaAparelho (Aparelho* a);

    void desassociaAparelho(Aparelho* a);

    [[nodiscard]] const std::string &getId() const;

    [[nodiscard]] size_t getNumRegras() const;

    void setComando(const std::string &comando);

    void setIdZona(const std::string &idZona);

    [[nodiscard]] const std::string &getIdZona() const;

    bool validaRegra();

};
#endif //TP_POO_2023_PROCESSADOR_H