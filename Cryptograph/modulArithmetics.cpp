//
// Created by artem on 06.10.2022.
//

#include <random>
#include "modulArithmetics.h"
#include "LongArithmetic.h"
#include <openssl/bn.h>
#include <openssl/rand.h>
#include <iostream>

using ll = long long;
template<typename Type>
Type fastPow(Type a, Type step, Type mod){
    if (step==0)
        return 1;
    if (step==1)
        return a%mod;
    if (step%2==0){
        auto temp = fastPow(a,step/2, mod)%mod;
        return temp*temp%mod;
    }
    else
        return (fastPow(a,step-1, mod)%mod*(a%mod))%mod;
}
template LongArithmetic fastPow(LongArithmetic, LongArithmetic, LongArithmetic);

template<typename Type>
GcdReturn<Type> gcd (Type a, Type b) {
    Type x;
    Type y;
    if (a == 0) {
        return {0,1,b};
    }
    int x1, y1;
    auto res = gcd (b%a, a);
    x = res.y - (b / a) * res.x;
    y = res.x;
    return {x,y,res.g};
}
template GcdReturn<LongArithmetic> gcd(LongArithmetic, LongArithmetic);

static std::vector<char> eratosfen(){
    int n = 1000000000;
    std::vector<char> prime (n+1, true);
    prime[0] = prime[1] = false;
    for (int i=2; i*i<=n; ++i)
        if (prime[i])
            if (i * 1ll * i <= n)
                for (int j=i*i; j<=n; j+=i)
                    prime[j] = false;
    return prime;
}

int chooseRandomQ(){
    static auto commonNumbers = eratosfen();
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randInt(commonNumbers.size()/15,commonNumbers.size()/10);
    ll startNumber = randInt(rng);
    for (int i=startNumber;i<commonNumbers.size();++i){
        if (commonNumbers[i] && commonNumbers[2*i+1])
            return i;
    }
}

int chooseRandomG(int mod, int q){

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randInt(mod/2, mod-1);
    ll startNumber = randInt(rng);
    for (int i=startNumber;i<mod-1;++i){
        if (fastPow(i,q,mod)!=1)
            return i;
    }
}

template<typename Type>
Type findRandSafePrime(ll bits){
    //srand(time(0));
    BIGNUM *r;
    const unsigned char rnd_seed[] = "string to make the random number generator think it has entropy";

    r = BN_new();
    RAND_seed(rnd_seed, sizeof rnd_seed); // or BN_generate_prime_ex may fail
    //RAND_status();
    //RAND_bytes(const_cast<unsigned char *>(rnd_seed), sizeof(rnd_seed));

    BN_generate_prime_ex(r, bits, true, nullptr, nullptr, nullptr);
    auto mod = LongArithmetic(string(BN_bn2dec(r)));

    BN_free(r);
    return mod;
}
template LongArithmetic findRandSafePrime(ll bits);


