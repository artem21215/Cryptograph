//
// Created by artem on 18.11.2022.
//

#include "gtest/gtest.h"
#include "modulArithmetics.h"
#include "LongArithmetic.h"

TEST(ModulArithmeticTests, testFastPow){
    LongArithmetic number("99999999999999999999");
    LongArithmetic step("9999");
    LongArithmetic mod("9999999999999999999");
    //cout << fastPow(5,2,50) << endl;

    EXPECT_EQ(fastPow(number, step, mod), LongArithmetic("4473330189108740091"));
    EXPECT_EQ(fastPow(LongArithmetic("0"), step, mod), LongArithmetic("0"));
    EXPECT_EQ(fastPow(LongArithmetic("0"), LongArithmetic("0"), mod), LongArithmetic("1"));
}

TEST(ModulArithmeticTests, testGCD){
    auto firstExample = make_pair(LongArithmetic("36"), LongArithmetic("42"));
    auto expectedFirst = LongArithmetic("6");

    auto bigFirst = LongArithmetic("6623647676256734276");
    auto bigSecond = LongArithmetic("3495689234682388");

    auto secondExample = make_pair(bigFirst, bigSecond);
    auto expectedSecond = LongArithmetic("4");

    auto resultGcdFirst = gcd(firstExample.first, firstExample.second);
    auto resultGcdSecond = gcd(secondExample.first, secondExample.second);

    EXPECT_EQ(resultGcdFirst.g, expectedFirst);
    EXPECT_EQ(resultGcdFirst.x * 36 + resultGcdFirst.y * 42, resultGcdFirst.g);

    EXPECT_EQ(resultGcdSecond.g, expectedSecond);
    EXPECT_EQ(resultGcdSecond.x * bigFirst + resultGcdSecond.y * bigSecond, resultGcdSecond.g);
    //EXPECT_EQ(fastPow(LongArithmetic("0"), step, mod), LongArithmetic("0"));
    //EXPECT_EQ(fastPow(LongArithmetic("0"), LongArithmetic("0"), mod), LongArithmetic("1"));
}

