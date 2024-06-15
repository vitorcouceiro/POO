#ifndef TP_POO_2023_MAIOR_H
#define TP_POO_2023_MAIOR_H
#include "../Regra.h"

class Maior : public Regra{
public:
    explicit Maior(double x) : Regra("maior_que", x ){}
    bool verificaRegra(double val) override;
    [[nodiscard]] Regra* duplica() const override;
};
#endif //TP_POO_2023_MAIOR_H
