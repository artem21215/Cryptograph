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
    template<typename Type>
    class IFileCrypto {
    public:
        virtual void coding(const string &inputFileName, const string &outputFileName,
                            Users_NS::User<Type> &alice, Users_NS::User<Type> &bob) = 0;

        virtual void decoding(const string &inputFileName, const string &outputFileName,
                              Users_NS::User<Type> &alice, Users_NS::User<Type> &bob) = 0;
    };

    template<typename Type>
    class Shamir : public IFileCrypto<Type> {
    public:
        void coding(const string &inputFileName, const string &outputFileName,
                    Users_NS::User<Type> &alice, Users_NS::User<Type> &bob) override;

        void decoding(const string &inputFileName, const string &outputFileName,
                      Users_NS::User<Type> &alice, Users_NS::User<Type> &bob) override;
    };

    template<typename Type>
    class ElGamal : public IFileCrypto<Type> {
    public:
        void coding(const string &inputFileName, const string &outputFileName,
                    Users_NS::User<Type> &alice, Users_NS::User<Type> &bob) override;

        void decoding(const string &inputFileName, const string &outputFileName,
                      Users_NS::User<Type> &alice, Users_NS::User<Type> &bob) override;
    };

    template<typename Type>
    class RSA : public IFileCrypto<Type> {
    public:
        void coding(const string &inputFileName, const string &outputFileName,
                    Users_NS::User<Type> &alice, Users_NS::User<Type> &bob) override;

        void decoding(const string &inputFileName, const string &outputFileName,
                      Users_NS::User<Type> &alice, Users_NS::User<Type> &bob) override;
    };

    template<typename Type>
    class Vernam : public IFileCrypto<Type> {
    public:
        void coding(const string &inputFileName, const string &outputFileName,
                    Users_NS::User<Type> &alice, Users_NS::User<Type> &bob) override;

        void decoding(const string &inputFileName, const string &outputFileName,
                      Users_NS::User<Type> &alice, Users_NS::User<Type> &bob) override;
    };
}


#endif //THEORYPROGRAMMINGLANGUAGE_CRYPT_H
