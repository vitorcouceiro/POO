#ifndef TP_POO_2023_PROPRIEDADE_H
#define TP_POO_2023_PROPRIEDADE_H
#include <string>

class Propriedade{
    int static contadorProps;
    std::string nome;
    double valor;
    std::string id;
    std::string unidadeMedida;
    double min;
public:
    Propriedade(std::string  nome, double valor, std::string  unidadeMedida, const std::string& letra, double min);

    virtual ~Propriedade();


    [[nodiscard]] const std::string &getNome() const;

    [[nodiscard]] double getValor() const;

    [[nodiscard]] const std::string &getId() const;

    virtual void setValor(double valor);

};











#endif //TP_POO_2023_PROPRIEDADE_H
