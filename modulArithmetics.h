//
// Created by artem on 06.10.2022.
//

#ifndef THEORYPROGRAMMINGLANGUAGE_MODULARITHMETICS_H
#define THEORYPROGRAMMINGLANGUAGE_MODULARITHMETICS_H
#include <vector>
#include "LongArithmetic.h"

using ll = long long;
struct GcdReturn{
    ll x{};
    ll y{};
    ll g{};
};

ll fastPow(ll a, ll step, ll mod);

GcdReturn gcd(ll a, ll b);

int chooseRandomQ();

int chooseRandomG(int mod, int q);

#endif //THEORYPROGRAMMINGLANGUAGE_MODULARITHMETICS_H
