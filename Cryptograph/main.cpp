#include "Crypt.h"
#include "Signs.h"
#include "LongArithmetic.h"
#include <random>
#include <iostream>
#include <openssl/md5.h>
#include <openssl/evp.h>
#include <cstdio>
#include <openssl/rsa.h>


using namespace std;
using ll = long long;

namespace {
    static void runCryptExample() {
        //int q = chooseRandomQ();
        int q = 70340351;
        int mod = 2 * q + 1;
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
        std::uniform_int_distribution<std::mt19937::result_type> randInt(1, 255);
        unsigned char commonKey = randInt(rng);
        alice.setVernam(commonKey);
        bob.setVernam(commonKey);
        CryptoGraph_NS::Vernam vernam;
        vernam.coding(inputFile, codedFileVerrnam, alice, bob);
        vernam.decoding(codedFileVerrnam, decodedFileVerrnam, alice, bob);
    }

    static void runSignExample() {
        //int q = chooseRandomQ();
        int q = 70340351;
        int mod = 2 * q + 1;
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

        Sign_NS::RSA rsa;
        rsa.signing(R"(C:\Users\artem\Desktop\Crypt\IP.Pirogova.s04e02.2021.WEB-DL.(1080p).mkv)", codedFileRSA, alice, bob);
    }
}

int main() {
    //runCryptExample();
    //runSignExample();

    LongArithmetic first("-2");
    LongArithmetic second("3");
    //cout << 6%3 << endl;

    cout << (first / second).getString() << endl << (first%second).getString() << endl;


    /*string example = "-234";
    LongArithmetic first("-12344543");
    LongArithmetic second("-325235");
    std::cout << (first * second).getString() << endl;*/


    return 0;
}
