#ifndef TP_POO_2023_SENSOR_H
#define TP_POO_2023_SENSOR_H
#include <string>
#include <vector>
#include "../Propriedades/Propriedade.h"


class Sensor{
    static int contSensores;
    std::string id;
    std::string nome;
    std::string letra;
    Propriedade *prop;
    //std::vector<Regra*> listaRegras;   --> duvidas se o sensor precisa de conhecer as regras
public:
    Sensor(std::string tipo, const std::string &letra);
    //~Sensor();
    void lePropriedade();
    const std::string &getId() const;
    const std::string &getNome() const;
    bool associaPropriedade (Propriedade * propNova);

    int getValor();//valor da propriedade

    Propriedade* getPropriedade()const;
};



#endif //TP_POO_2023_SENSOR_H