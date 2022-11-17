#include <random>
#include <string>
#include "modulArithmetics.h"
#include "Speakers.h"
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
            if (auto number = gcd(i,mod).g; number==1){
                return i;
            }
        }
        return 1;
    }

    int User::getMod() const {
        return mod;
    }
    User::User(int mod) : mod(mod){
        auto tempMod = mod-1;
        koeffCode = chooseRandKoeff(tempMod);
        koeffDecode = fastPow(koeffCode,tempMod-3, tempMod);
        privateKey = koeffCode;
        g = chooseRandomG(mod, (mod-1)/2);
        int pRSA = 7351;
        int qRSA = 6733;
        nRSA = pRSA*qRSA;
        ll phi = (pRSA-1)*(qRSA-1);
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randInt(phi/4,phi);
        ll startNumber = randInt(rng);
        dRSA = 1;
        for (int i=startNumber;i<phi;++i){
            if (gcd(phi, i).g==1) {
                dRSA = i;
                break;
            }
        }
        cRSA = gcd(phi,dRSA).y+phi;

    }

    void User::setVernam(unsigned char commonKey){
        cVernam = commonKey;
    }

    void User::setup(){
        publicKey = fastPow(g,privateKey,mod);
    }

    /*ll User::calcMessage(ll partMessage, KeyIndex keyIndex) {
        return (keyIndex == KeyIndex::KOEFF_FOR_CODE) ? fastPow(partMessage, koeffCode, mod)
                                                      : fastPow(partMessage, koeffDecode, mod);
    }*/

    ll User::calcMessage(ll partMessage, const function<int(int, int, int)>& calcLocalMessage, const string& paramForLambda) {
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
            return calcLocalMessage(partMessage, dRSAOther, nRSAOther);
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
    }
}