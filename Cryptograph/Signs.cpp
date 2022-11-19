//
// Created by artem on 12.11.2022.
//

//
// Created by artem on 02.11.2022.
//

#include "Signs.h"
#include "Speakers.h"
#include "modulArithmetics.h"
#include "LongArithmetic.h"
#include <iostream>
#include <fstream>
#include <random>
#include <openssl/md5.h>
#include <openssl/evp.h>
#include <cstdio>

using namespace std;

namespace{
    class CalcHashMD5{
        EVP_MD_CTX*   context;
    public:
        CalcHashMD5(){
            context = EVP_MD_CTX_create();
            const EVP_MD* md = EVP_md5();
            EVP_DigestInit_ex(context, md, NULL);
        }
        void addStringToHash(const string& stringForHash){
            if (stringForHash.empty())
                return;
            EVP_DigestUpdate(context, stringForHash.c_str(), stringForHash.length());
        }
        string getHash(){
            unsigned char md_value[EVP_MAX_MD_SIZE];
            unsigned int  md_len;
            EVP_DigestFinal_ex(context, md_value, &md_len);
            string output;
            output.resize(md_len * 2);
            for (unsigned int i = 0 ; i < md_len ; ++i) {
                std::sprintf(&output[i * 2], "%02x", md_value[i]);
            }
            return output;
        }
        ~CalcHashMD5(){
            EVP_MD_CTX_destroy(context);
        }
    };
    string md5(const string& content)
    {
        EVP_MD_CTX*   context = EVP_MD_CTX_create();
        const EVP_MD* md = EVP_md5();
        unsigned char md_value[EVP_MAX_MD_SIZE];
        unsigned int  md_len;
        string        output;

        EVP_DigestInit_ex(context, md, NULL);
        EVP_DigestUpdate(context, content.c_str(), content.length());
        EVP_DigestFinal_ex(context, md_value, &md_len);
        EVP_MD_CTX_destroy(context);

        output.resize(md_len * 2);
        for (unsigned int i = 0 ; i < md_len ; ++i) {
            std::sprintf(&output[i * 2], "%02x", md_value[i]);
        }
        return output;
    }

    string transformToBin(string& octFormat){
        string temp;
        for (auto& symb:octFormat){
            switch (symb) {
                case '0':
                    temp.push_back('0');
                    temp.push_back('0');
                    temp.push_back('0');
                    temp.push_back('0');
                    break;
                case '1':
                    temp.push_back('0');
                    temp.push_back('0');
                    temp.push_back('0');
                    temp.push_back('1');
                    break;
                case '2':
                    temp.push_back('0');
                    temp.push_back('0');
                    temp.push_back('1');
                    temp.push_back('0');
                    break;
                case '3':
                    temp.push_back('0');
                    temp.push_back('0');
                    temp.push_back('1');
                    temp.push_back('1');
                    break;
                case '4':
                    temp.push_back('0');
                    temp.push_back('1');
                    temp.push_back('0');
                    temp.push_back('0');
                    break;
                case '5':
                    temp.push_back('0');
                    temp.push_back('1');
                    temp.push_back('0');
                    temp.push_back('1');
                    break;
                case '6':
                    temp.push_back('0');
                    temp.push_back('1');
                    temp.push_back('1');
                    temp.push_back('0');
                    break;
                case '7':
                    temp.push_back('0');
                    temp.push_back('1');
                    temp.push_back('1');
                    temp.push_back('1');
                    break;
                case '8':
                    temp.push_back('1');
                    temp.push_back('0');
                    temp.push_back('0');
                    temp.push_back('0');
                    break;
                case '9':
                    temp.push_back('1');
                    temp.push_back('0');
                    temp.push_back('0');
                    temp.push_back('1');
                    break;
                case 'a':
                    temp.push_back('1');
                    temp.push_back('0');
                    temp.push_back('1');
                    temp.push_back('0');
                    break;
                case 'b':
                    temp.push_back('1');
                    temp.push_back('0');
                    temp.push_back('1');
                    temp.push_back('1');
                    break;
                case 'c':
                    temp.push_back('1');
                    temp.push_back('1');
                    temp.push_back('0');
                    temp.push_back('0');
                    break;
                case 'd':
                    temp.push_back('1');
                    temp.push_back('1');
                    temp.push_back('0');
                    temp.push_back('1');
                    break;
                case 'e':
                    temp.push_back('1');
                    temp.push_back('1');
                    temp.push_back('1');
                    temp.push_back('0');
                    break;
                case 'f':
                    temp.push_back('1');
                    temp.push_back('1');
                    temp.push_back('1');
                    temp.push_back('1');
                    break;
            }
        }
        return temp;
    }

    LongArithmetic transformToDec(string& octFormat){
        auto binFormat = transformToBin(octFormat);
        LongArithmetic step("1");
        LongArithmetic ans("0");
        for (auto it=binFormat.rbegin(); it!=binFormat.rend(); ++it){
            if (*it == '1') {
                ans = ans + step;
            }
            step = step*LongArithmetic("2");
        }
        return ans;
    }
}

namespace Sign_NS{
    template<typename Type>
    void RSA<Type>::signing(const string& inputFileName,
                     Users_NS::User<Type>& user) {
        std::ifstream input( inputFileName, std::ifstream::binary );
        char message;
        string fullFile;
        CalcHashMD5 hashHolder;
        constexpr int maxBufSize = 10000;
        ll cntTemp = 0;
        while (input.get(message)) {
            ++cntTemp;
            fullFile+=message;
            if (fullFile.size()>maxBufSize) {
                hashHolder.addStringToHash(fullFile);
                fullFile.clear();
            }
        }
        cout << cntTemp << endl;
        input.close();
        hashHolder.addStringToHash(fullFile);
        auto fileHashOct = hashHolder.getHash();
        auto fileHash = transformToDec(fileHashOct);
        cout << fileHashOct << endl;
        cout << fileHash.getString() << endl;

        auto calculatorMessage = [](LongArithmetic message, LongArithmetic key, LongArithmetic mod){return fastPow(message, key, mod);};
        auto sign = user.calcMessage(fileHash, calculatorMessage,"RC");

        ll cntOfExtraZero = (user.nRSA).getString().size() - sign.getString().size();
        string strSignToFile;
        for (int i=0;i<cntOfExtraZero;++i)
            strSignToFile+='0';
        strSignToFile +=sign.getString();

        std::ofstream output;
        output.open(inputFileName, std::ios_base::app);
        cout << strSignToFile << endl;
        cout << endl;
        cout << "###############" << endl;
        for (auto v:strSignToFile)
            output << v;
        output.close();
    }
    template class IFileSign<LongArithmetic>;

    template<typename Type>
    bool RSA<Type>::checkSign(const string& inputFileName,
                       Users_NS::User<Type>& user) {
        LongArithmetic fileSize;
        std::ifstream input( inputFileName, std::ifstream::binary );
        char message;
        while (input.get(message)) {
            fileSize = fileSize+1;
        }
        input.close();

        input.open( inputFileName, std::ifstream::binary );
        CalcHashMD5 hashHolder;
        constexpr int maxBufSize = 10000;
        string fullFile;
        for (LongArithmetic i(0); i < fileSize - user.nRSA.getString().size(); i = i+1) {
            input.get(message);
            fullFile+=message;
            if (fullFile.size()>maxBufSize) {
                hashHolder.addStringToHash(fullFile);
                fullFile.clear();
            }
        }
        hashHolder.addStringToHash(fullFile);
        auto fileHashOct = hashHolder.getHash();
        auto fileHash = transformToDec(fileHashOct);
        cout << fileHashOct << endl;
        cout << fileHash.getString() << endl;
        string mayBeStrSign;
        while (input.get(message)) {
            mayBeStrSign+=message;
        }

        input.close();

        cout << mayBeStrSign << endl;
        return fileHash == fastPow(LongArithmetic(mayBeStrSign), user.dRSA, user.nRSA);
    }
    template class RSA<LongArithmetic>;

    template<typename Type>
    void ElGamal<Type>::signing(const string& inputFileName,
                            Users_NS::User<Type>& user) {
        std::ifstream input( inputFileName, std::ifstream::binary );
        char message;
        string fullFile;
        CalcHashMD5 hashHolder;
        constexpr int maxBufSize = 10000;
        ll cntTemp = 0;
        while (input.get(message)) {
            ++cntTemp;
            fullFile+=message;
            if (fullFile.size()>maxBufSize) {
                hashHolder.addStringToHash(fullFile);
                fullFile.clear();
            }
        }
        cout << cntTemp << endl;
        input.close();
        hashHolder.addStringToHash(fullFile);
        auto fileHashOct = hashHolder.getHash();
        auto fileHash = transformToDec(fileHashOct);
        cout << fileHashOct << endl;
        cout << fileHash.getString() << endl;

        constexpr int lenElGamalG = 90;
        auto k = findRandSafePrime<LongArithmetic>(lenElGamalG) % (user.getMod()-2) + 1;
        while (gcd(k,user.getMod()-1).g != 1)
            k = findRandSafePrime<LongArithmetic>(lenElGamalG) % (user.getMod()-2) + 1;
        auto r = fastPow(user.g,k,user.getMod());
        //auto u = (fileHash - x * r) % (user.getMod()-1);
        auto calculatorMessage = [r](LongArithmetic message, LongArithmetic key, LongArithmetic mod){return (message - key * r) % (mod-1);};
        auto u = user.calcMessage(fileHash, calculatorMessage,"EC");
        auto kInverted = gcd<LongArithmetic>(user.getMod()-1,k).y + (user.getMod()-1);
        auto s = kInverted * u % (user.getMod()-1);


        ll cntOfExtraZeroR = user.getMod().getString().size() - r.getString().size();
        ll cntOfExtraZeroS = user.getMod().getString().size() - s.getString().size();

        string strSignToFile;
        for (int i=0;i<cntOfExtraZeroR;++i)
            strSignToFile+='0';
        strSignToFile +=r.getString();

        for (int i=0;i<cntOfExtraZeroS;++i)
            strSignToFile+='0';
        strSignToFile +=s.getString();

        std::ofstream output;
        output.open(inputFileName, std::ios_base::app);
        cout << strSignToFile << endl;
        cout << endl;
        cout << "###############" << endl;
        for (auto v:strSignToFile)
            output << v;
        output.close();
    }

    template<typename Type>
    bool ElGamal<Type>::checkSign(const string& inputFileName,
                              Users_NS::User<Type>& targetUser) {
        LongArithmetic fileSize;
        std::ifstream input( inputFileName, std::ifstream::binary );
        char message;
        while (input.get(message)) {
            fileSize = fileSize+1;
        }
        input.close();

        input.open( inputFileName, std::ifstream::binary );
        CalcHashMD5 hashHolder;
        constexpr int maxBufSize = 10000;
        string fullFile;
        for (LongArithmetic i(0); i < fileSize - targetUser.getMod().getString().size() * 2; i = i+1) {
            input.get(message);
            fullFile+=message;
            if (fullFile.size()>maxBufSize) {
                hashHolder.addStringToHash(fullFile);
                fullFile.clear();
            }
        }
        hashHolder.addStringToHash(fullFile);
        auto fileHashOct = hashHolder.getHash();
        auto fileHash = transformToDec(fileHashOct);
        cout << fileHashOct << endl;
        cout << fileHash.getString() << endl;
        string mayBeStrSign;
        while (input.get(message)) {
            mayBeStrSign+=message;
        }

        input.close();

        cout << mayBeStrSign << endl;
        string r,s;
        auto lenMod = targetUser.getMod().getString().size();
        for (int i=0;i<lenMod; ++i){
            r+=mayBeStrSign[i];
            s+=mayBeStrSign[lenMod + i];
        }
        return fastPow(targetUser.g, fileHash, targetUser.getMod()) == (fastPow(targetUser.g, fileHash, targetUser.getMod()) *
                                                                       fastPow(targetUser.g, fileHash, targetUser.getMod()))%targetUser.getMod();
    }
    template class ElGamal<LongArithmetic>;
}