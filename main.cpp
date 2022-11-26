#include "Crypt.h"
#include "Signs.h"
#include "Cryptograph/LongArithmetic.h"
#include "LongArithmetic.h"
#include "Pocker.h"
#include <random>
#include <iostream>
#include <openssl/md5.h>
#include <openssl/evp.h>
#include <cstdio>
#include <openssl/rsa.h>
#include <openssl/bn.h>
//#include <openssl/rand.h>

using namespace std;
using ll = long long;

namespace {
    /*static void runCryptExample() {
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

     */
    static void runSignExample() {
        //const string inputFile = R"(C:\Users\artem\Desktop\Crypt\picture.png)";
        const string inputFile = R"(C:\Users\artem\Desktop\Crypt\pictureCodedShamir.png)";
        const string decodedFileShamir = R"(C:\Users\artem\Desktop\Crypt\pictureDecodedShamir.png)";
        const string codedFileElGamal = R"(C:\Users\artem\Desktop\Crypt\pictureCodedElGamal.png)";
        const string decodedFileElGamal = R"(C:\Users\artem\Desktop\Crypt\pictureDecodedElGamal.png)";
        const string signedFileRSA = R"(C:\Users\artem\Desktop\Crypt\pictureCodedRSA.png)";
        const string decodedFileRSA = R"(C:\Users\artem\Desktop\Crypt\pictureDecodedRSA.png)";
        const string codedFileVerrnam = R"(C:\Users\artem\Desktop\Crypt\pictureCodedVernan.png)";
        const string decodedFileVerrnam = R"(C:\Users\artem\Desktop\Crypt\pictureDecodedVernan.png)";

        auto p = findRandSafePrime<LongArithmetic>(100);

        Users_NS::User<LongArithmetic> alice(p);
        Users_NS::User<LongArithmetic> bob(p);
        Sign_NS::RSA<LongArithmetic> signRSA;
        Sign_NS::RSA<LongArithmetic> signElGamal;
        Sign_NS::RSA<LongArithmetic> signGOST;

        cout << "RSA CHECK:" << endl;
        signRSA.signing(inputFile,alice);
        if (signRSA.checkSign(inputFile, alice)){
            cout << "Sign is belong to Alice!" << endl;
        }
        else
            cout << "Sign is not belong to Alice!" << endl;

        cout << "ElGamal CHECK:" << endl;
        signElGamal.signing(signedFileRSA,alice);
        if (signElGamal.checkSign(signedFileRSA, alice)){
            cout << "Sign is belong to Alice!" << endl;
        }
        else
            cout << "Sign is not belong to Alice!" << endl;

        cout << "GOST CHECK:" << endl;
        signGOST.signing(codedFileVerrnam,alice);
        if (signGOST.checkSign(codedFileVerrnam, alice)){
            cout << "Sign is belong to Alice!" << endl;
        }
        else
            cout << "Sign is not belong to Alice!" << endl;
    }

    void runPocker(const int numberOfPlayers){
        auto p = findRandSafePrime<LongArithmetic>(31);
        cout << p.getString() << endl << endl;

        vector<Users_NS::User<LongArithmetic>> players;
        for (int i=0;i<numberOfPlayers;++i)
            players.emplace_back(p);
        static const auto fullDesk = allDesk();
        auto cryptedDeskWithRandom = fullCryptedDesk(fullDesk, players);
        auto cardLastId = 0;
        for (int i=0;i<players.size();++i){
            players[i].cards.push_back(cryptedDeskWithRandom[cardLastId]);
            players[i].cards.push_back(cryptedDeskWithRandom[cardLastId+1]);
            cardLastId+=2;
        }
        vector<ll> table(5);
        for (auto& v:table){
            v = cryptedDeskWithRandom[cardLastId];
            cardLastId++;
        }
        cout << "Cards from table: " << endl;
        ll curPlId = 0;
        for (auto v:table){
            cout << "open card number " << curPlId << ' ';
            cout << fullDesk[decrypteCard(v, players, -1)] << endl;
            curPlId++;
        }
        cout << endl;


        curPlId = 0;
        for (auto v:players){
            cout << "cards for player " << curPlId << ' ';
            cout << fullDesk[decrypteCard(v.cards.front(), players, curPlId)] << ' ';
            cout << fullDesk[decrypteCard(v.cards.back(), players, curPlId)] << endl;
            curPlId++;
        }

    }


}

int main() {
    //runCryptExample();
    //runSignExample();

    constexpr int numberOfPlayers = 5;
    runPocker(numberOfPlayers);
    return 0;
}
