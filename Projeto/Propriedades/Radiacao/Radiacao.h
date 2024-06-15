#ifndef TP_POO_2023_RADIACAO_H
#define TP_POO_2023_RADIACAO_H

#include "../Propriedade.h"

class Radiacao : public Propriedade{
public:
    explicit Radiacao(double valor): Propriedade("radiacao", valor, "Becquerel", "r", 0){}
};

#endif //TP_POO_2023_RADIACAO_H
