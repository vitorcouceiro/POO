//
// Created by nunes on 06/12/2023.
//

#ifndef TP_POO_2023_ENTRE_H
#define TP_POO_2023_ENTRE_H
#include "../Regra.h"

class Entre : public Regra{
    double param2;
public:
    Entre(double x, double y);
    bool verificaRegra(double val) override;    //vai receber o val do aparelho

    [[nodiscard]] double getParam2() const;
    [[nodiscard]] Regra* duplica() const override;

};
#endif //TP_POO_2023_ENTRE_H
