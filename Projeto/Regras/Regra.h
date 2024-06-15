#ifndef TP_POO_2023_REGRA_H
#define TP_POO_2023_REGRA_H
#include <vector>
#include <string>

//agregacao
class Sensor;

class Regra{
    static int contRegras;
    std::string tipo;
    double param;
    std::string id;
    Sensor *sensor;
public:

    Regra(std::string regra, double x);

    virtual bool verificaRegra(double val) {return false;};

    [[nodiscard]] const std::string &getTipo() const;

    [[nodiscard]] double getParam() const;

    [[nodiscard]] const std::string &getId() const;

    bool associaSensor(Sensor *sen);

    [[nodiscard]] Sensor *getSensor() const;

    [[nodiscard]] virtual Regra* duplica() const {return nullptr;};

    //virtual ~Regra()=default;
};
#endif //TP_POO_2023_REGRA_H