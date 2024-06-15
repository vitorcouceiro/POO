#ifndef TP_POO_2023_TEMPERATURA_H
#define TP_POO_2023_TEMPERATURA_H

#include "../Propriedade.h"

class Temperatura : public Propriedade{
public:
    explicit Temperatura(double valor): Propriedade("temperatura", valor, "graus Celsius", "t", -273){}
};



#endif //TP_POO_2023_TEMPERATURA_H
