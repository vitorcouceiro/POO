#include "Lampada.h"
#include "../../Propriedades/Propriedade.h"

Lampada::Lampada():Aparelho("lampada", "l"){}

Lampada* Lampada::duplica() const{
    return new Lampada(*this);
}

void Lampada::liga() {
    if(!on){
        on = true;
        addLumes();
    }
}

void Lampada::desliga(){
    if(on){
        on = false;
        props.at(0)->setValor(props.at(0)->getValor()-900);
    }
}

void Lampada::addLumes(){
    props.at(0)->setValor(props.at(0)->getValor()+900);
}