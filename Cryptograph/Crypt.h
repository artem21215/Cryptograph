//
// Created by artem on 02.11.2022.
//

#ifndef THEORYPROGRAMMINGLANGUAGE_CRYPT_H
#define THEORYPROGRAMMINGLANGUAGE_CRYPT_H

#include "modulArithmetics.h"
#include "Speakers.h"
#include <fstream>
#include <random>
#include <string>

using namespace std;

namespace CryptoGraph_NS {
    class IFileCrypto {
    public:
        virtual void coding(const string &inputFileName, const string &outputFileName,
                            Users_NS::User &alice, Users_NS::User &bob) = 0;

        virtual void decoding(const string &inputFileName, const string &outputFileName,
                              Users_NS::User &alice, Users_NS::User &bob) = 0;
    };

    class Shamir : public IFileCrypto {
    public:
        void coding(const string &inputFileName, const string &outputFileName,
                    Users_NS::User &alice, Users_NS::User &bob) override;

        void decoding(const string &inputFileName, const string &outputFileName,
                      Users_NS::User &alice, Users_NS::User &bob) override;
    };

    class ElGamal : public IFileCrypto {
    public:
        void coding(const string &inputFileName, const string &outputFileName,
                    Users_NS::User &alice, Users_NS::User &bob) override;

        void decoding(const string &inputFileName, const string &outputFileName,
                      Users_NS::User &alice, Users_NS::User &bob) override;
    };

    class RSA : public IFileCrypto {
    public:
        void coding(const string &inputFileName, const string &outputFileName,
                    Users_NS::User &alice, Users_NS::User &bob) override;

        void decoding(const string &inputFileName, const string &outputFileName,
                      Users_NS::User &alice, Users_NS::User &bob) override;
    };

    class Vernam : public IFileCrypto {
    public:
        void coding(const string &inputFileName, const string &outputFileName,
                    Users_NS::User &alice, Users_NS::User &bob) override;

        void decoding(const string &inputFileName, const string &outputFileName,
                      Users_NS::User &alice, Users_NS::User &bob) override;
    };
}


#endif //THEORYPROGRAMMINGLANGUAGE_CRYPT_H
