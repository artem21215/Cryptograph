//
// Created by artem on 02.11.2022.
//

#include "Crypt.h"
#include "Speakers.h"
#include "modulArithmetics.h"
#include <fstream>
#include <random>

namespace CryptoGraph_NS{
    void Shamir::coding(const string& inputFileName, const string& outputFileName,
                        Users_NS::User& alice, Users_NS::User& bob) {
        std::ifstream input( inputFileName, std::ifstream::binary );
        std::ofstream output( outputFileName, std::ios::binary );
        char message;

        auto calculatorMessage = [](int message, int key, int mod){return fastPow(message, key, mod);};
        while (input.get(message)) {
            int x1 = alice.calcMessage(message, calculatorMessage,"SC");
            int x2 = bob.calcMessage(x1, calculatorMessage, "SC");
            char* arrayBite = reinterpret_cast<char*>(&x2);
            for (size_t i=0;i<sizeof(x2);++i){
                output << static_cast<char>(arrayBite[i]);
            }
        }
        input.close();
        output.close();
    }

    void Shamir::decoding(const string& inputFileName, const string& outputFileName,
                          Users_NS::User& alice, Users_NS::User& bob) {
        std::ifstream input( inputFileName, std::ifstream::binary );
        std::ofstream output( outputFileName, std::ios::binary );
        int message;

        auto calculatorMessage = [](int message, int key, int mod){return fastPow(message, key, mod);};
        while (input.read(reinterpret_cast<char*>(&message), sizeof(int))) {
            int x3 = alice.calcMessage(message, calculatorMessage, "SD");
            char x4 = bob.calcMessage(x3, calculatorMessage, "SD");
            //auto x3 = alice.calcMessage(message,Users_NS::User::KeyIndex::KOEFF_FOR_DECODE);
            //auto x4 = bob.calcMessage(x3,Users_NS::User::KeyIndex::KOEFF_FOR_DECODE);

            output << static_cast<char>(x4);
        }
        input.close();
        output.close();
    }

    void ElGamal::coding(const string& inputFileName, const string& outputFileName,
                         Users_NS::User& alice, Users_NS::User& bob) {
        //mod = 10000007; g from 2.2 diffi-helmon; For users create secret key and public and send others
        // A -> B : A gen k{1,mod-1}, r = g^k mod p, e = m*publicB^k mod p; B calculate m'=e*r^(p-1-secretB) mod p
        std::ifstream input( inputFileName, std::ifstream::binary );
        std::ofstream output( outputFileName, std::ios::binary );
        char message;

        auto mod = alice.getMod();
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randInt(1,mod-2);
        int k = randInt(rng);
        while (input.get(message)) {
            unsigned char messageTemp = message;
            int r = fastPow(alice.g,k,mod);
            auto deb = fastPow(bob.publicKey,k,mod);
            int e = (messageTemp % mod) * fastPow(bob.publicKey,k,mod) % mod;
            char* arrayBite = reinterpret_cast<char*>(&r);
            for (size_t i=0;i<sizeof(r);++i){
                output << static_cast<char>(arrayBite[i]);
            }
            arrayBite = reinterpret_cast<char*>(&e);
            for (size_t i=0;i<sizeof(e);++i){
                output << static_cast<char>(arrayBite[i]);
            }
        }
        input.close();
        output.close();
    }

    void ElGamal::decoding(const string& inputFileName, const string& outputFileName,
                           Users_NS::User& alice, Users_NS::User& bob) {
        std::ifstream input( inputFileName, std::ifstream::binary );
        std::ofstream output( outputFileName, std::ios::binary );
        int messageR{};
        int messageE{};

        while (input.read(reinterpret_cast<char*>(&messageR), sizeof(int))) {
            input.read(reinterpret_cast<char*>(&messageE), sizeof(int));
            auto calculatorMessage = [messageE, messageR](int message, int key, int mod)
            {return messageE * fastPow(messageR, mod-1-key, mod) % mod;};
            char m = bob.calcMessage(messageE, calculatorMessage, "ED");

            output << m;
        }
        input.close();
        output.close();
    }

    void RSA::coding(const string& inputFileName, const string& outputFileName,
                     Users_NS::User& alice, Users_NS::User& bob) {
        std::ifstream input( inputFileName, std::ifstream::binary );
        std::ofstream output( outputFileName, std::ios::binary );
        char message;

        auto calculatorMessage = [](int message, int key, int mod){return fastPow(message, key, mod);};
        while (input.get(message)) {
            unsigned char messageTemp = message;
            int e = alice.calcMessage(messageTemp, calculatorMessage,"RC");
            char* arrayBite = reinterpret_cast<char*>(&e);
            for (size_t i=0;i<sizeof(e);++i){
                output << static_cast<char>(arrayBite[i]);
            }
        }
        input.close();
        output.close();
    }

    void RSA::decoding(const string& inputFileName, const string& outputFileName,
                       Users_NS::User& alice, Users_NS::User& bob) {
        std::ifstream input( inputFileName, std::ifstream::binary );
        std::ofstream output( outputFileName, std::ios::binary );
        int message{};

        while (input.read(reinterpret_cast<char*>(&message), sizeof(int))) {
            auto calculatorMessage = [](int message, int key, int mod)
            {return fastPow(message, key, mod);};
            char m = bob.calcMessage(message, calculatorMessage, "RD");

            output << m;
        }
        input.close();
        output.close();
    }

    void Vernam::coding(const string& inputFileName, const string& outputFileName,
                        Users_NS::User& alice, Users_NS::User& bob) {
        std::ifstream input( inputFileName, std::ifstream::binary );
        std::ofstream output( outputFileName, std::ios::binary );
        char message;

        auto calculatorMessage = [](int message, int key, int mod){return message^static_cast<unsigned char>(key);};
        while (input.get(message)) {
            char e = alice.calcMessage(message, calculatorMessage,"VC");
            output << e;
        }
        input.close();
        output.close();
    }

    void Vernam::decoding(const string& inputFileName, const string& outputFileName,
                          Users_NS::User& alice, Users_NS::User& bob) {
        std::ifstream input( inputFileName, std::ifstream::binary );
        std::ofstream output( outputFileName, std::ios::binary );
        char message{};

        auto calculatorMessage = [](int message, int key, int mod){return message^static_cast<unsigned char>(key);};
        while (input.get(message)) {
            char m = bob.calcMessage(message, calculatorMessage, "VD");
            output << m;
        }
        input.close();
        output.close();
    }
}