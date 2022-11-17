//
// Created by artem on 02.11.2022.
//

#include "LongArithmetic.h"
#include <string>
#include <utility>
#include <vector>
using namespace std;

static void deleteExtraSpaces(string& longString){
    std::reverse(longString.begin(), longString.end());
    while (!longString.empty() && longString.back()=='0')
        longString.pop_back();
    std::reverse(longString.begin(), longString.end());
}
LongArithmetic::LongArithmetic(const string& other) : number(other) {
    if (this->number[0] == '-') {
        isPositive = false;
        number.erase(number.begin());
    }
    deleteExtraSpaces(this->number);
    if (number.empty())
        number+='0';
    if (number == "0")
        isPositive = true;
}

LongArithmetic::LongArithmetic(const LongArithmetic& other):isPositive(other.isPositive), number(other.number){
    deleteExtraSpaces(this->number);
    if (number.empty())
        number+='0';
    if (number == "0")
        isPositive = true;
}

LongArithmetic& LongArithmetic::operator=(const LongArithmetic& other){
    auto otherStr = other.getString();
    this->isPositive = true;
    if (!otherStr.empty() && otherStr.front() == '-') {
        otherStr.erase(otherStr.begin());
        this->isPositive = false;
    }
    this->number = otherStr;
    deleteExtraSpaces(this->number);
    if (number.empty())
        number+='0';
    if (number == "0")
        isPositive = true;
    return *this;
}

LongArithmetic LongArithmetic::operator-() const {
    auto temp = *this;
    temp.isPositive = !isPositive;
    return temp;
}

LongArithmetic LongArithmetic::operator-(const LongArithmetic& other) const {
    if (this->isPositive != other.isPositive){
        auto first = *this;
        auto second = other;
        second = -second;
        return second + first;
    }

    auto [first, second] = std::make_pair(number, other.number);
    if (first.size() < second.size())
        swap(first, second);
    if (first.size() == second.size() && first<second)
        swap(first,second);

    reverse(first.begin(),first.end());
    reverse(second.begin(),second.end());

    for (int i=0;i<min(number.size(), other.number.size());++i){
        int cur = (first[i] - '0') - (second[i] - '0');
        if (cur < 0) {
            --first[i + 1];
            cur+=10;
            first[i] = to_string(cur).front();
        }
        else{
            first[i] = to_string(cur).front();
        }
    }
    std::reverse(first.begin(), first.end());
    auto ans = LongArithmetic(first);
    if (*this < other)
        ans = -ans;
    return ans;
}

LongArithmetic LongArithmetic::operator*(const LongArithmetic& other) const{
    auto first = this->number;
    auto second = other.number;

    if (second.size() > first.size())
        swap(first, second);

    auto copyThis = LongArithmetic(first);
    vector<LongArithmetic> simpleMul;
    auto temp = LongArithmetic("0");
    for (int i = 0; i < 10; ++i){
        simpleMul.push_back(temp);
        temp = temp + copyThis;
    }

    string delt;
    LongArithmetic summ("0");
    std::reverse(second.begin(), second.end());
    for (const auto numb:second){
        auto tempCur = simpleMul[numb - '0'];
        summ = summ + (LongArithmetic(tempCur.getString()+delt));
        delt+='0';
    }
    if (isPositive != other.isPositive)
        summ = -summ;
    return summ;
}

LongArithmetic LongArithmetic::operator+(const LongArithmetic& other) const {
    if (this->isPositive != other.isPositive){
        auto myFirst = *this;
        auto mySecond = other;
        if (!myFirst.isPositive)
            std::swap(myFirst, mySecond);
        mySecond.isPositive = true;
        return myFirst - mySecond;
    }
    auto first = this->number;
    auto second = other.number;
    if (first.size() < second.size())
        std::swap(first,second);
    std::reverse(first.begin(), first.end());
    std::reverse(second.begin(), second.end());
    for (int i=0;second.size() < first.size();++i)
        second+='0';

    bool needUpgrade = false;
    for (int i=0;i<first.size();++i){
        int summ = 0;
        summ = first[i] + second[i] - '0' - '0' + needUpgrade;
        if (summ > 9) {
            needUpgrade = true;
            summ -= 10;
        }
        else
            needUpgrade = false;
        first[i] = summ + '0';
    }
    if (needUpgrade)
        first+='1';
    std::reverse(first.begin(), first.end());
    auto result = LongArithmetic(first);
    if (!this->isPositive)
        result = -result;
    return result;
}

static pair<LongArithmetic, LongArithmetic> calcDivide(const LongArithmetic& dividend,
                                                       const LongArithmetic& divisor){
    auto dividentStr = dividend.getString();
    if (dividentStr[0] == '-')
        dividentStr.erase(dividentStr.begin());
    auto copyDivisor = divisor;
    if (copyDivisor < LongArithmetic("0"))
        copyDivisor = - copyDivisor;
    string divPartStr;
    string modPartStr;

    LongArithmetic curExtra("0");
    auto it = 0;
    auto curSubstring = LongArithmetic("0");
    bool needExit = false;
    while (true) {
        while (curSubstring < copyDivisor) {
            divPartStr.push_back('0');
            if (it >= dividentStr.size()){
                modPartStr = curSubstring.getString();
                needExit = true;
                break;
            }
            curSubstring = curSubstring * LongArithmetic("10");
            curSubstring = curSubstring + LongArithmetic(string(1,dividentStr[it]));
            ++it;
        }
        if (divPartStr.empty())
            break;
        divPartStr.pop_back();
        if (needExit){
            break;
        }

        LongArithmetic curMulMember = LongArithmetic("0");
        int mul = 0;
        while (curMulMember <= curSubstring) {
            ++mul;
            curMulMember = curMulMember + copyDivisor;
        }
        mul--;
        curMulMember = curMulMember - copyDivisor;
        divPartStr += to_string(mul);
        curSubstring = curSubstring - curMulMember;
    }
    bool positive = true;
    return (divisor*dividend < LongArithmetic("0")) ?
           make_pair(-LongArithmetic(divPartStr), (-LongArithmetic(modPartStr) + copyDivisor)%copyDivisor) :
           make_pair(LongArithmetic(divPartStr), LongArithmetic(modPartStr));
}

LongArithmetic LongArithmetic::operator/(const LongArithmetic& other) const{
    return calcDivide(*this, other).first;
}

LongArithmetic LongArithmetic::operator%(const LongArithmetic& other) const{
    return calcDivide(*this, other).second;
}

bool LongArithmetic::operator<(const LongArithmetic &other) const{
    bool result = false;
    if (number.size() < other.number.size())
        result = true;
    if (number.size() == other.number.size() && number < other.number)
        result = true;
    if (isPositive == other.isPositive) {
        if (isPositive)
            return result;
        else
            return !result;
    }
    else{
        if (isPositive)
            return false;
        else
            return true;
    }
}

bool LongArithmetic::operator>(const LongArithmetic &other) const{
    return !(*this < other || *this == other);
}

bool LongArithmetic::operator<=(const LongArithmetic &other) const{
    return *this < other || *this == other;
}

bool LongArithmetic::operator>=(const LongArithmetic &other) const{
    return *this > other || *this == other;
}

bool LongArithmetic::operator==(const LongArithmetic &other) const{
    return (isPositive == other.isPositive && number == other.number);
}

string LongArithmetic::getString() const {
    return (!isPositive) ? "-" + number : number;
}
