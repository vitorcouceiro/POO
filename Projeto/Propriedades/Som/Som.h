//
// Created by nunes on 02/12/2023.
//

#ifndef TP_POO_2023_SOM_H
#define TP_POO_2023_SOM_H
#include "../Propriedade.h"

class Som : public Propriedade{
public:
    explicit Som(double valor): Propriedade("som", valor, "Decibeis", "s", 0){}
};

#endif //TP_POO_2023_SOM_H
