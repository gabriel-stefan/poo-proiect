//
// Created by Gabriel on 7/7/2024.
//

#ifndef OOP_PAYMENTMETHOD_H
#define OOP_PAYMENTMETHOD_H

#include <iostream>
#include <memory>

class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual void pay(int suma) const = 0;
    virtual std::unique_ptr<PaymentMethod> clone() const = 0;

    PaymentMethod() = default;
    PaymentMethod(const PaymentMethod&) = default;
    PaymentMethod(PaymentMethod&&) = default;
    PaymentMethod& operator=(const PaymentMethod&) = default;
    PaymentMethod& operator=(PaymentMethod&&) = default;
};

#endif //OOP_PAYMENTMETHOD_H
