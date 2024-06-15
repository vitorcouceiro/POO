#include "Aquecedor.h"
#include "../../Propriedades/Propriedade.h"

Aquecedor::Aquecedor(): Aparelho("aquecedor", "a"), contador(0) {}

Aquecedor* Aquecedor::duplica() const{
    return new Aquecedor(*this);
}

void Aquecedor::liga(){
    if(!on){
        on = true;
        addSom();
    }else{
        contador ++;
    }
    if(contador == 3){
        addTemperatura();//isto so acontece a cada 3 instantes
        contador = 0;
    }
}

void Aquecedor::desliga(){
    if(on){
        on = false;
        props.at(1)->setValor(props.at(1)->getValor() - 5);
        contador = 0;
    }
}

void Aquecedor::addSom(){
    props.at(1)->setValor(props.at(1)->getValor() + 5);
}
//aumenta sempre um grau celsius (até um max de 50 graus)
void Aquecedor::addTemperatura(){
    if( props.at(0)->getValor() < 50)
        props.at(0)->setValor(props.at(0)->getValor() +1);
}

