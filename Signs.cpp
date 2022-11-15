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
    void RSA::signing(const string& inputFileName, const string& outputFileName,
                     Users_NS::User& alice, Users_NS::User& bob) {
        /*std::ifstream input( inputFileName, std::ifstream::binary );
        std::ofstream output( outputFileName, std::ios::binary );
        char message;
        string fullFile;
        CalcHashMD5 hashHolder;
        constexpr int maxBufSize = 10000;
        while (input.get(message)) {
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

        auto calculatorMessage = [](LongArithmetic message, int key, int mod){return fastPow(message, key, mod);};
        auto sign = alice.calcMessage(fileHash, calculatorMessage,"RC");

        input.close();
        output.close();*/
    }

    void RSA::checkSign(const string& inputFileName, const string& outputFileName,
                       Users_NS::User& alice, Users_NS::User& bob) {

    }
}