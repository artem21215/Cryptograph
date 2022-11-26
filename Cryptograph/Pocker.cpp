//
// Created by artem on 25.11.2022.
//

#include "Pocker.h"
#include "Speakers.h"
#include "modulArithmetics.h"
#include <random>
#include <vector>
#include <string>
using namespace std;
vector<string> cartNames{"six", "seven", "eight", "nine", "ten", "jack", "queen", "king", "ace"};
vector<string> suitNames{"heart", "diamond", "club", "spade"};

vector<string> allDesk(){
    vector<string> full;
    for (const auto& curCart:cartNames){
        for (const auto& curSuit:suitNames)
            full.push_back(curCart + ' ' +curSuit);
    }
    return full;
}

vector<ll> cryptedByUser(const vector<ll>& cryptedDesk, Users_NS::User<LongArithmetic>& player){
    vector<ll> cryptedDeskCurrent;
    for (auto curMean:cryptedDesk){
        auto calculatorMessage = [](LongArithmetic message, LongArithmetic key, LongArithmetic mod){return fastPow(message, key, mod);};
        cryptedDeskCurrent.push_back(convertLongArithmToInt(player.calcMessage(curMean, calculatorMessage, "SC")));
    }

    return cryptedDeskCurrent;
}

vector<ll> stirDeskByUser(const vector<ll>& cryptedDesk, Users_NS::User<LongArithmetic>& player){
    vector<ll> cryptedDeskCurrent(cryptedDesk);
    vector<ll> randomedDesk;

    std::random_device dev;
    std::mt19937 rng(dev());
    while (!cryptedDeskCurrent.empty()) {
        std::uniform_int_distribution<std::mt19937::result_type> randInt(0, cryptedDeskCurrent.size() - 1);
        ll randNumber = randInt(rng);
        randomedDesk.push_back(cryptedDeskCurrent[randNumber]);
        cryptedDeskCurrent.erase(cryptedDeskCurrent.begin()+randNumber);
    }
    return randomedDesk;
}

vector<ll> fullCryptedDesk(const vector<string>& fullDesk, vector<Users_NS::User<LongArithmetic>>& players){
    vector<ll> cryptedDesk(fullDesk.size());
    for (int i=0;i<fullDesk.size();++i)
        cryptedDesk[i] = i;

    for (int i=0;i<players.size();++i){
        cryptedDesk = cryptedByUser(cryptedDesk, players[i]);
        cryptedDesk = stirDeskByUser(cryptedDesk, players[i]);
    }
    return cryptedDesk;
}

ll decrypteCard(const ll card, vector<Users_NS::User<LongArithmetic>>& players, ll idTargetUser){
    ll decryptedCard = card;
    for (int i=0;i<players.size();++i){
        if (i==idTargetUser)
            continue;
        auto calculatorMessage = [](LongArithmetic message, LongArithmetic key, LongArithmetic mod){return fastPow(message, key, mod);};
        decryptedCard = convertLongArithmToInt(players[i].calcMessage(decryptedCard, calculatorMessage, "SD"));
    }

    if (idTargetUser!=-1) {
        auto calculatorMessage = [](LongArithmetic message, LongArithmetic key, LongArithmetic mod) {return fastPow(message, key, mod);};
        decryptedCard = convertLongArithmToInt(players[idTargetUser].calcMessage(decryptedCard, calculatorMessage, "SD"));
    }
    return decryptedCard;
}
