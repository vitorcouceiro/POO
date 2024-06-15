#ifndef TP_POO_2023_LAMPADA_H
#define TP_POO_2023_LAMPADA_H
#include "../Aparelho.h"

class Lampada : public Aparelho{
public:
    Lampada();
    [[nodiscard]] Lampada* duplica() const override;
    void liga() override;
    void desliga() override;
    void addLumes();
};

#endif //TP_POO_2023_LAMPADA_H
