#include <iostream>
#include "modulArithmetics.h"
#include <fstream>
#include <map>
#include <functional>
#include <random>
using namespace std;
using ll = long long;

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

    class User{
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
        enum class KeyIndex{
            KOEFF_FOR_CODE = 0,
            KOEFF_FOR_DECODE
        };
        explicit User(int mod);
        //ll calcMessage(ll partMessage, KeyIndex keyIndex);
        ll calcMessage(ll partMessage, const function<int(int, int, int)>& calcLocalMessage, const string& paramForLambda);
        void setup();
        [[nodiscard]] int getMod() const;
        void setVernam(unsigned char commonKey);
    };

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

namespace CryptoGraph_NS{
    //auto mod = 1000000007ll;
    class IFileCrypto{
    public:
        virtual void coding(const string& inputFileName, const string& outputFileName,
                            Users_NS::User& alice, Users_NS::User& bob) = 0;
        virtual void decoding(const string& inputFileName, const string& outputFileName,
                              Users_NS::User& alice, Users_NS::User& bob) = 0;
    };

    class Shamir : public IFileCrypto{
    public:
        void coding(const string& inputFileName, const string& outputFileName,
                    Users_NS::User& alice, Users_NS::User& bob) override;
        void decoding(const string& inputFileName, const string& outputFileName,
                      Users_NS::User& alice, Users_NS::User& bob) override;
    };

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

    class ElGamal : public IFileCrypto{
    public:
        void coding(const string& inputFileName, const string& outputFileName,
                    Users_NS::User& alice, Users_NS::User& bob) override;
        void decoding(const string& inputFileName, const string& outputFileName,
                      Users_NS::User& alice, Users_NS::User& bob) override;
    };

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

    class RSA : public IFileCrypto{
    public:
        void coding(const string& inputFileName, const string& outputFileName,
                    Users_NS::User& alice, Users_NS::User& bob) override;
        void decoding(const string& inputFileName, const string& outputFileName,
                      Users_NS::User& alice, Users_NS::User& bob) override;
    };

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

    class Vernam : public IFileCrypto{
    public:
        void coding(const string& inputFileName, const string& outputFileName,
                    Users_NS::User& alice, Users_NS::User& bob) override;
        void decoding(const string& inputFileName, const string& outputFileName,
                      Users_NS::User& alice, Users_NS::User& bob) override;
    };

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

int main() {

    //int q = chooseRandomQ();
    int q = 70340351;
    int mod = 2*q+1;
    Users_NS::User alice(mod);
    Users_NS::User bob(mod);
    bob.g = alice.g;
    alice.setup();
    bob.setup();
    bob.publicKeyOther = alice.publicKey;
    alice.publicKeyOther = bob.publicKey;
    alice.nRSAOther = bob.nRSA;
    bob.nRSAOther = alice.nRSA;
    alice.dRSAOther = bob.dRSA;
    bob.dRSAOther = alice.dRSA;


    const string inputFile = R"(C:\Users\artem\Desktop\Crypt\picture.png)";
    const string codedFileShamir = R"(C:\Users\artem\Desktop\Crypt\pictureCodedShamir.png)";
    const string decodedFileShamir = R"(C:\Users\artem\Desktop\Crypt\pictureDecodedShamir.png)";
    const string codedFileElGamal = R"(C:\Users\artem\Desktop\Crypt\pictureCodedElGamal.png)";
    const string decodedFileElGamal = R"(C:\Users\artem\Desktop\Crypt\pictureDecodedElGamal.png)";
    const string codedFileRSA = R"(C:\Users\artem\Desktop\Crypt\pictureCodedRSA.png)";
    const string decodedFileRSA = R"(C:\Users\artem\Desktop\Crypt\pictureDecodedRSA.png)";
    const string codedFileVerrnam = R"(C:\Users\artem\Desktop\Crypt\pictureCodedVernan.png)";
    const string decodedFileVerrnam = R"(C:\Users\artem\Desktop\Crypt\pictureDecodedVernan.png)";

    CryptoGraph_NS::Shamir shamir;
    shamir.coding(inputFile, codedFileShamir, alice, bob);
    shamir.decoding(codedFileShamir, decodedFileShamir, alice, bob);

    CryptoGraph_NS::ElGamal elGamal;
    elGamal.coding(inputFile, codedFileElGamal, alice, bob);
    elGamal.decoding(codedFileElGamal, decodedFileElGamal, alice, bob);

    CryptoGraph_NS::RSA rsa;
    rsa.coding(inputFile, codedFileRSA, alice, bob);
    rsa.decoding(codedFileRSA, decodedFileRSA, alice, bob);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randInt(1,255);
    unsigned char commonKey = randInt(rng);
    alice.setVernam(commonKey);
    bob.setVernam(commonKey);
    CryptoGraph_NS::Vernam vernam;
    vernam.coding(inputFile, codedFileVerrnam, alice, bob);
    vernam.decoding(codedFileVerrnam, decodedFileVerrnam, alice, bob);



    return 0;
}
