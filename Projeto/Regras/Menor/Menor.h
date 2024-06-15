#ifndef TP_POO_2023_MENOR_H
#define TP_POO_2023_MENOR_H
#include "../Regra.h"
class Menor : public Regra{
public:
    explicit Menor(double x) : Regra("menor_que", x ){}
    bool verificaRegra(double val) override;
    [[nodiscard]] Regra* duplica() const override;
};
#endif //TP_POO_2023_MENOR_H
