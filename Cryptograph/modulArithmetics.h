//
// Created by artem on 06.10.2022.
//

#ifndef THEORYPROGRAMMINGLANGUAGE_MODULARITHMETICS_H
#define THEORYPROGRAMMINGLANGUAGE_MODULARITHMETICS_H
#include <vector>

using ll = long long;
template<typename Type>
struct GcdReturn{
    Type x;
    Type y;
    Type g;
};

template<typename Type>
Type fastPow(Type a, Type step, Type mod);

template<typename Type>
GcdReturn<Type> gcd(Type a, Type b);

template<typename Type>
int chooseRandomQ();

int chooseRandomG(int mod, int q);

template<typename Type>
Type findRandSafePrime(ll bits);

#endif //THEORYPROGRAMMINGLANGUAGE_MODULARITHMETICS_H
