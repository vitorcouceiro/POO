//
// Created by nunes on 06/12/2023.
//

#ifndef TP_POO_2023_IGUAL_H
#define TP_POO_2023_IGUAL_H
#include "../Regra.h"

class Igual : public Regra{
public:
    explicit Igual(double x) : Regra("igual_a", x){}
    bool verificaRegra(double val) override;
    [[nodiscard]] Regra* duplica() const override;
};
#endif //TP_POO_2023_IGUAL_H
