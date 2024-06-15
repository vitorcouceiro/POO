#ifndef TP_POO_2023_AQUECEDOR_H
#define TP_POO_2023_AQUECEDOR_H
#include "../Aparelho.h"

class Aquecedor : public Aparelho{
    int contador;
public:
    Aquecedor();
    void liga() override;
    void desliga() override;
    void addSom();
    void addTemperatura();
    [[nodiscard]] Aquecedor* duplica() const override;
};
#endif //TP_POO_2023_AQUECEDOR_H
