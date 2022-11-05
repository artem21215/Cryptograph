//
// Created by artem on 06.10.2022.
//

#ifndef THEORYPROGRAMMINGLANGUAGE_SPEAKERS_H
#define THEORYPROGRAMMINGLANGUAGE_SPEAKERS_H

#include <functional>
#include <string>

using namespace std;

using ll = long long;

namespace Users_NS {
    class User {
        int koeffCode{};
        int koeffDecode{};
        int mod{};
        int privateKey{};
        int cRSA{};
        int cVernam{};

    public:
        int nRSA{};
        int dRSA{};
        int nRSAOther{};
        int dRSAOther{};
        int publicKey{};
        int g{};
        int publicKeyOther{};
        enum class KeyIndex {
            KOEFF_FOR_CODE = 0,
            KOEFF_FOR_DECODE
        };

        explicit User(int mod);

        //ll calcMessage(ll partMessage, KeyIndex keyIndex);
        ll
        calcMessage(ll partMessage, const function<int(int, int, int)> &calcLocalMessage, const string &paramForLambda);

        void setup();

        [[nodiscard]] int getMod() const;

        void setVernam(unsigned char commonKey);
    };
}

#endif //THEORYPROGRAMMINGLANGUAGE_SPEAKERS_H
