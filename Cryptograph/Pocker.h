//
// Created by artem on 25.11.2022.
//

#ifndef CRYPTOGRAPHGLOBAL_POCKER_H
#define CRYPTOGRAPHGLOBAL_POCKER_H
#include <string>
#include <vector>
#include "Speakers.h"
using namespace std;
using ll = long long;

vector<string> allDesk();

vector<ll> fullCryptedDesk(const vector<string>& fullDesk, vector<Users_NS::User<LongArithmetic>>& players);

ll decrypteCard(const ll card, vector<Users_NS::User<LongArithmetic>>& players, ll idTargetUser);


#endif //CRYPTOGRAPHGLOBAL_POCKER_H
