#ifndef TP_POO_2023_LUZ_H
#define TP_POO_2023_LUZ_H
#include "../Propriedade.h"

class Luz : public Propriedade{
public:
    explicit Luz(double valor): Propriedade("luz", valor, "Lumens", "l",0) {}
};

#endif //TP_POO_2023_LUZ_H
