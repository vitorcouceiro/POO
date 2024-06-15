#ifndef TP_POO_2023_APARELHO_H
#define TP_POO_2023_APARELHO_H
#include <iostream>
#include <vector>
#include <string>

class Processador;
class Propriedade;

class Aparelho{
    static int contadorAparelhos;
    std::string id;
    std::string nome;
protected:
    std::vector<Propriedade*> props;
    bool on;
public:
    Aparelho (std::string tipo, const std::string& letra);
    [[nodiscard]] const std::string &getId() const;
    [[nodiscard]] const std::string &getNome() const;

    [[nodiscard]] virtual Aparelho* duplica() const {return nullptr;};
    virtual std::string getComando();
    virtual bool setEstado(const std::string& comandoUt);

    virtual void liga();
    virtual void desliga();


    void associaProp(Propriedade * p);
};

#endif //TP_POO_2023_APARELHO_H
