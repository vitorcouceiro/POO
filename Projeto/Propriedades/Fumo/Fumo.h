#ifndef TP_POO_2023_FUMO_H
#define TP_POO_2023_FUMO_H
#include "../Propriedade.h"

class Fumo : public Propriedade{
    double max;
public:
    explicit Fumo(double valor);
    void setValor(double valorApa) override;
};

#endif //TP_POO_2023_FUMO_H
