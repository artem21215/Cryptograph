#include <random>
#include <string>
#include "modulArithmetics.h"
#include "Speakers.h"
#include <iostream>
#include "LongArithmetic.h"

using ll = long long;
using namespace std;

namespace Users_NS{
    static ll chooseRandKoeff(ll mod){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randInt(1,mod/2);
        ll startNumber = randInt(rng);
        for (auto i=startNumber;i<mod;++i){
            auto number = gcd(i,mod).g;
            if (number==1){
                return i;
            }
        }
        return 1;
    }

    template<typename Type>
    Type User<Type>::getMod() const {
        return mod;
    }

    template<typename Type>
    User<Type>::User(Type mod) : mod(mod){
        koeffCode = mod-1;
        while (gcd<LongArithmetic>(mod-1, koeffCode).g != 1)
            koeffCode = findRandSafePrime<LongArithmetic>(20);
        koeffDecode = gcd<LongArithmetic>(mod-1,koeffCode).y + mod-1;

        cout << koeffCode.getString() << endl;
        cout << koeffDecode.getString() << endl;
        auto res = koeffCode * koeffDecode % (mod-1);
        cout << res.getString() << endl << endl;
        //g = chooseRandomG(mod, (mod-1)/2);
        /*auto lenGOST = 50;
        bigModP = LongArithmetic("10");
        string bigTempMod;
        for (int i=0;i<100;++i)
            bigTempMod+='9';
        LongArithmetic b;
        while (!isPrimeBig(bigModP.getString())){
            bigQ = findRandSafePrime<LongArithmetic>(lenGOST);
            b = fastPow(LongArithmetic("2"), LongArithmetic(100 - 50), LongArithmetic(bigTempMod));
            b = b + LongArithmetic("2");
            b = b + LongArithmetic(4);
            b = b + LongArithmetic("8");

            bigModP = bigQ * b + 1;
        }
        aGost = 1;
        while (aGost <= 1){
            auto gTemp = findRandSafePrime<LongArithmetic>(10)% (bigModP - 2) + 1;
            aGost = fastPow(gTemp, b , bigModP);
        }
        xGOST = findRandSafePrime<LongArithmetic>(100);
        yGOST = fastPow(aGost, xGOST, bigModP);


        constexpr int lenElGamalG = 90;
        g = findRandSafePrime<LongArithmetic>(lenElGamalG);
        while (fastPow(g, (mod-1)/2, mod) == 1)
            g = findRandSafePrime<LongArithmetic>(lenElGamalG);
        elGamalX = findRandSafePrime<LongArithmetic>(lenElGamalG) % (mod-1);
        elGamalY = fastPow(g,elGamalX, mod);

        constexpr int lenRSABits = 100;
        Type pRSA = findRandSafePrime<LongArithmetic>(lenRSABits);
        Type qRSA = findRandSafePrime<LongArithmetic>(lenRSABits);
        nRSA = pRSA*qRSA;
        LongArithmetic phi = (pRSA-1)*(qRSA-1);


        while (dRSA == 0){
            auto curNumb = findRandSafePrime<LongArithmetic>(lenRSABits - 10);
            if (gcd(phi, curNumb).g == 1)
                dRSA = curNumb;
        }*/
//        cRSA = gcd<LongArithmetic>(phi,dRSA).y + phi;
    }

    template<typename Type>
    void User<Type>::setVernam(unsigned char commonKey){
        cVernam = commonKey;
    }

    template<typename Type>
    void User<Type>::setup(){
        publicKey = fastPow(g,privateKey,mod);
    }

    /*ll User::calcMessage(ll partMessage, KeyIndex keyIndex) {
        return (keyIndex == KeyIndex::KOEFF_FOR_CODE) ? fastPow(partMessage, koeffCode, mod)
                                                      : fastPow(partMessage, koeffDecode, mod);
    }*/

    template<typename Type>
    Type User<Type>::calcMessage(Type partMessage, const function<Type(Type, Type, Type)>& calcLocalMessage, const string& paramForLambda) {
        if (paramForLambda == "SC"){
            return calcLocalMessage(partMessage, koeffCode, mod);
        }
        else if (paramForLambda == "SD"){
            return calcLocalMessage(partMessage, koeffDecode, mod);
        }
        else if (paramForLambda == "ED"){
            return calcLocalMessage(partMessage, privateKey, mod);
        }
        else if (paramForLambda == "RC"){
            return calcLocalMessage(partMessage, cRSA, nRSA);
        }
        else if (paramForLambda == "RD"){
            return calcLocalMessage(partMessage, cRSA, nRSA);
        }
        else if (paramForLambda == "VC"){
            return calcLocalMessage(partMessage, cVernam, 0);
        }
        else if (paramForLambda == "VD"){
            return calcLocalMessage(partMessage, cVernam, 0);
        }
        return 0;
    }

    template class User<LongArithmetic>;
}