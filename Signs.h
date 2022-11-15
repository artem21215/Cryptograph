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
    class IFileSign {
    public:
        virtual void signing(const string &inputFileName, const string &outputFileName,
                            Users_NS::User &alice, Users_NS::User &bob) = 0;

        virtual void checkSign(const string &inputFileName, const string &outputFileName,
                              Users_NS::User &alice, Users_NS::User &bob) = 0;
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

    class RSA : public IFileSign {
    public:
        void signing(const string &inputFileName, const string &outputFileName,
                    Users_NS::User &alice, Users_NS::User &bob) override;

        void checkSign(const string &inputFileName, const string &outputFileName,
                      Users_NS::User &alice, Users_NS::User &bob) override;
    };

    /*class Vernam : public IFileSign {
    public:
        void signing(const string &inputFileName, const string &outputFileName,
                    Users_NS::User &alice, Users_NS::User &bob) override;

        void checkSign(const string &inputFileName, const string &outputFileName,
                      Users_NS::User &alice, Users_NS::User &bob) override;
    };*/
}


#endif //THEORYPROGRAMMINGLANGUAGE_SIGNS_H
