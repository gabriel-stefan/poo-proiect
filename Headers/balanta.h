#ifndef OOP_BALANTA_H
#define OOP_BALANTA_H

#include <vector>
#include <memory>

class PaymentMethod;

class Balanta {
private:
    int suma;
    std::vector<int> transactionHistory;
    std::unique_ptr<PaymentMethod> paymentMethod;

public:
    Balanta();
    explicit Balanta(int _suma);
    Balanta& operator=(const Balanta& other);
    Balanta(const Balanta& other);
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
