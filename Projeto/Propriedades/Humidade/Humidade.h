#ifndef TP_POO_2023_HUMIDADE_H
#define TP_POO_2023_HUMIDADE_H
#include "../Propriedade.h"

class Humidade : public Propriedade{
    double max;
public:
    explicit Humidade(double valor);

    void setValor(double valorApa) override;
};

#endif //TP_POO_2023_HUMIDADE_H
