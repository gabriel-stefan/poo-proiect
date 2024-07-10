#ifndef OOP_COMPARARE_H
#define OOP_COMPARARE_H

#include "balanta.h"

template <typename T>
bool comparaBalante(const T& b1, const T& b2) {
    return b1.getSuma() == b2.getSuma();
}

#endif // OOP_COMPARARE_H
