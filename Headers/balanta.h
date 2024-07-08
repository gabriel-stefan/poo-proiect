#ifndef OOP_BALANTA_H
#define OOP_BALANTA_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "passwordmanager.h"
#include "exceptieCustom.h"
#include "paymentMethod.h"
#include "paypal.h"
#include "card.h"

class Balanta {
private:
    int suma;
    std::vector<int> transactionHistory;
    std::unique_ptr<PaymentMethod> paymentMethod;

public:
    Balanta();
    explicit Balanta(const int _suma);
    Balanta& operator=(const Balanta& other);
    Balanta(const Balanta& other);
    Balanta(Balanta&& other) = default;
    Balanta& operator=(Balanta&& other) = default;
    ~Balanta();

    int getSuma() const;
    void adaugaSuma(int sumaAdaugata);
    void scadeSuma(int sumaScazuta);
    void setPaymentMethod(std::unique_ptr<PaymentMethod> method);
    void pay(int amount) const;
    void afisareIstoricTranzactii() const;

    friend std::ostream& operator<<(std::ostream& os, const Balanta& other);
};

#endif // OOP_BALANTA_H
