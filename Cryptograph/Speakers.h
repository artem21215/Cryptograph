//
// Created by artem on 06.10.2022.
//

#ifndef THEORYPROGRAMMINGLANGUAGE_SPEAKERS_H
#define THEORYPROGRAMMINGLANGUAGE_SPEAKERS_H

#include <functional>
#include <string>
#include "LongArithmetic.h"

using namespace std;

using ll = long long;

namespace Users_NS {
    template<typename Type>
    class User {
        Type koeffCode{};
        Type koeffDecode{};
        Type mod{};
        Type privateKey{};
        Type cRSA{};
        Type cVernam{};
        Type elGamalX{};

    public:
        Type elGamalY{};
        Type nRSA{};
        Type dRSA{};
        Type nRSAOther{};
        Type dRSAOther{};
        Type publicKey{};
        Type g{};
        Type publicKeyOther{};
        enum class KeyIndex {
            KOEFF_FOR_CODE = 0,
            KOEFF_FOR_DECODE
        };

        explicit User(Type mod);

        //ll calcMessage(ll partMessage, KeyIndex keyIndex);
        Type calcMessage(Type partMessage,
                       const function<Type(Type, Type, Type)> &calcLocalMessage,
                       const string &paramForLambda);

        void setup();

        [[nodiscard]] Type getMod() const;

        void setVernam(unsigned char commonKey);
    };
}

#endif //THEORYPROGRAMMINGLANGUAGE_SPEAKERS_H
