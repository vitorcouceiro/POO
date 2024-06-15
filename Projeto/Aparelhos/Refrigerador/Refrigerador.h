#ifndef TP_POO_2023_REFRIGERADOR_H
#define TP_POO_2023_REFRIGERADOR_H
#include "../Aparelho.h"

class Refrigerador : public Aparelho{
    int contador;
public:
    Refrigerador();
    [[nodiscard]] Refrigerador* duplica() const override;

    void liga() override;
    void desliga() override;
    void addRuido();
    void removeGrau();
};


#endif //TP_POO_2023_REFRIGERADOR_H
