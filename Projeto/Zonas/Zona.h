#ifndef TP_POO_2023_ZONA_H
#define TP_POO_2023_ZONA_H
#include <iostream>
#include <map>
#include <vector>
#include "../Library/Terminal.h"
#include "../Sensores/Sensor.h"
#include "../Processadores/Processador.h"
#include "../Aparelhos/Aparelho.h"
#include "../Propriedades/Propriedade.h"

class Zona {
    int x, y;           //local na habitacao
    std::string id;
    static int contadorZonas;
    std::vector<Sensor*> listaSensores;
    std::vector<Aparelho*> listaAparelhos;
    std::vector<Processador*> listaProcessadores;
    std::vector<Propriedade*> listaPropriedades;

    [[nodiscard]] int getAparelhoByID(const std::string& id_code) const;
    [[nodiscard]] int getSensorByID(const std::string& id_code) const;
    [[nodiscard]] int getProcessadorByID(const std::string& id_code) const;
    [[nodiscard]] int getPropriedadeByName (const std::string& nome) const;

public:
    Zona();
    //Zona(const Zona &outro);    //operador por copia (copia identica do original)
    Zona(int linha, int coluna);
    ~Zona();

    bool avaliaProcessador();

    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] std::string getId() const;

    [[nodiscard]] size_t getNumSensores() const;
    [[nodiscard]] size_t getNumProcessadores() const;
    [[nodiscard]] size_t getNumAparelhos() const;
    [[nodiscard]] const std::vector<Propriedade*>& getListaPropriedades() const;

    //adicionar propriedades
    void addPropriedades();
    bool alteraPropriedade(const std::string& nome, double valor);

    //adicionar componentes
    std::string addSensor(const std::string& tipo);
    std::string addProcessador(std::string &comando);
    std::string addAparelho(const std::string& tipo);

    //eliminar componentes
    bool removeAparelho(const std::string& idAparelho);
    bool removeSensor(const std::string& idSensor);
    bool removeProcessador(const std::string& idSensor);

    [[nodiscard]] const std::vector<Sensor *> &getListaSensores() const;
    [[nodiscard]] const std::vector<Aparelho *> &getListaAparelhos() const;
    [[nodiscard]] const std::vector<Processador *> &getListaProcessadores() const;

    //gerir processadores e regras
    bool addRegraProc(const std::string& idProc, const std::string &nomeRegra, const std::vector<int> &parametros, const std::string& idSensor);
    bool removeRegraProc(const std::string& idProc, const std::string& idRegra);
    bool mudaComandoProc(const std::string& idProc,const std::string& comando);
    bool associaAparelhoProc(const std::string& idProc,const std::string& idAparelho);
    bool desassociaAparelhoProc(const std::string& idProc, const std::string& idAparelho);
    bool mudaComando(const std::string& idAparelho,const std::string& comando);
    Processador * fazCopiaProcessador(const std::string& idProc);
    bool repoeCopiaProcessador(Processador* procCopia);

};
#endif //TP_POO_2023_ZONA_H