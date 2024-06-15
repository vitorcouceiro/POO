#ifndef TP_POO_2023_ASPERSOR_H
#define TP_POO_2023_ASPERSOR_H
#include "../Aparelho.h"

class Aspersor : public Aparelho{
    int contador,contadorDesliga,flag;
public:
    Aspersor();
    void liga() override;
    void desliga() override;
    void addFumo();
    void addHumidade();
    void addVibracao();
    void atualizaProps();
    [[nodiscard]] Aspersor* duplica() const override;
};
#endif //TP_POO_2023_ASPERSOR_H
