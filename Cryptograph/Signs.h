//
// Created by artem on 12.11.2022.
//

#ifndef THEORYPROGRAMMINGLANGUAGE_SIGNS_H
#define THEORYPROGRAMMINGLANGUAGE_SIGNS_H

#include "modulArithmetics.h"
#include "Speakers.h"
#include <fstream>
#include <random>
#include <string>

using namespace std;

namespace Sign_NS {
    template<typename Type>
    class IFileSign {
    public:
        virtual void signing(const string &inputFileName,
                            Users_NS::User<Type> &alice) = 0;

        virtual bool checkSign(const string &inputFileName,
                              Users_NS::User<Type> &alice) = 0;
    };

   /* class Shamir : public IFileSign {
    public:
        void signing(const string &inputFileName, const string &outputFileName,
                    Users_NS::User &alice, Users_NS::User &bob) override;

        void checkSign(const string &inputFileName, const string &outputFileName,
                      Users_NS::User &alice, Users_NS::User &bob) override;
    };

    class ElGamal : public IFileSign {
    public:
        void signing(const string &inputFileName, const string &outputFileName,
                    Users_NS::User &alice, Users_NS::User &bob) override;

        void checkSign(const string &inputFileName, const string &outputFileName,
                      Users_NS::User &alice, Users_NS::User &bob) override;
    };*/

   template<typename Type>
    class RSA : public IFileSign<Type> {
    public:
        void signing(const string &inputFileName,
                    Users_NS::User<Type> &alice) override;

        bool checkSign(const string &inputFileName,
                      Users_NS::User<Type> &alice) override;
    };

    template<typename Type>
    class ElGamal : public IFileSign<Type> {
    public:
        void signing(const string &inputFileName,
                     Users_NS::User<Type> &alice) override;

        bool checkSign(const string &inputFileName,
                       Users_NS::User<Type> &alice) override;
    };
}


#endif //THEORYPROGRAMMINGLANGUAGE_SIGNS_H
