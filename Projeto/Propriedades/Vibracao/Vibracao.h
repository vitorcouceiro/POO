#ifndef TP_POO_2023_VIBRACAO_H
#define TP_POO_2023_VIBRACAO_H
#include "../Propriedade.h"


class Vibracao : public Propriedade{
public:
    explicit Vibracao(double valor): Propriedade("vibracao", valor,"Hertz", "v", 0){}
};

#endif //TP_POO_2023_VIBRACAO_H
