#ifndef TP_POO_2023_FORA_H
#define TP_POO_2023_FORA_H
#include "../Regra.h"

class Fora : public Regra{
    double param2;
public:
    Fora(double x, double y);
    bool verificaRegra(double val) override;    //vai receber o val do sensor

    [[nodiscard]] double getParam2() const;
    [[nodiscard]] Regra* duplica() const override;
};
#endif //TP_POO_2023_FORA_H
