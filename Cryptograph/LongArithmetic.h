//
// Created by artem on 02.11.2022.
//

#ifndef THEORYPROGRAMMINGLANGUAGE_LONGARITHMETIC_H
#define THEORYPROGRAMMINGLANGUAGE_LONGARITHMETIC_H

#include <string>

using namespace std;

class LongArithmetic {
    string number;
    bool isPositive = true;
public:
    LongArithmetic(const string& other);

    LongArithmetic(int other);

    LongArithmetic();

    LongArithmetic(const LongArithmetic& other);

    LongArithmetic& operator=(const LongArithmetic& other);

    [[nodiscard]] LongArithmetic operator+(const LongArithmetic& other) const;

    [[nodiscard]] LongArithmetic operator-(const LongArithmetic& other) const;

    [[nodiscard]] LongArithmetic operator-() const;

    [[nodiscard]] LongArithmetic operator*(const LongArithmetic& other) const;

    [[nodiscard]] LongArithmetic operator/(const LongArithmetic& other) const;

    [[nodiscard]] LongArithmetic operator%(const LongArithmetic& other) const;

    bool operator<(const LongArithmetic& other) const;

    bool operator>(const LongArithmetic& other)const;

    bool operator<=(const LongArithmetic& other) const;

    bool operator>=(const LongArithmetic& other) const;

    bool operator==(const LongArithmetic& other) const;

    bool operator!=(const LongArithmetic& other) const;

    [[nodiscard]] string getString() const;

};



#endif //THEORYPROGRAMMINGLANGUAGE_LONGARITHMETIC_H
