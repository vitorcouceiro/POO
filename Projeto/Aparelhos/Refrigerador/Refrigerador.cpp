#include "Refrigerador.h"
#include "../../Propriedades/Propriedade.h"

Refrigerador::Refrigerador():Aparelho("refrigerador", "r"),contador(0){}

Refrigerador* Refrigerador::duplica() const{
    return new Refrigerador(*this);
}

void Refrigerador::liga(){
    if(!on){
        on = true;
        addRuido();
    }else{
        contador ++;
    }
    if(contador == 3){
        removeGrau();//isto so acontece a cada 3 instantes ligado
        contador = 0;
    }
}

void Refrigerador::desliga(){
    if(on){
        on = false;
        props.at(1)->setValor(props.at(1)->getValor() - 20);
        contador = 0;
    }
}
void Refrigerador::removeGrau(){//Remove um grau celsius à temperatura da zona a cada 3 instantes ligado
    props.at(0)->setValor(props.at(0)->getValor()-1);
}

void Refrigerador::addRuido(){
    props.at(1)->setValor(props.at(1)->getValor()+20);
}