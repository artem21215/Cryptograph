#include "gtest/gtest.h"
#include "LongArithmetic.h"

TEST(LongAtithmeticTests, testConstructorZero){
    LongArithmetic a("0");
    EXPECT_EQ(a.getString(), "0");
}

TEST(LongAtithmeticTests, testConstructorNegative){
    LongArithmetic a("-12428482374868238477328478748378274");
    EXPECT_EQ(a.getString(), "-12428482374868238477328478748378274");
}

TEST(LongAtithmeticTests, testConstructorPositive){
    LongArithmetic a("12428482374868238477328478748378274");
    EXPECT_EQ(a.getString(), "12428482374868238477328478748378274");
}

TEST(LongAtithmeticTests, testCopyConstructor){
    LongArithmetic a("-12428482374868238477328478748378274");
    const auto b(a);
    EXPECT_EQ(b.getString(), "-12428482374868238477328478748378274");
}

TEST(LongAtithmeticTests, testCopyOperator){
    LongArithmetic a("-12428482374868238477328478748378274");
    LongArithmetic b("0");
    b = a;
    EXPECT_EQ(b.getString(), "-12428482374868238477328478748378274");
}

TEST(LongAtithmeticTests, testCompare){
    LongArithmetic bigNegative("-124284823748682384773284787483782742347286283578178234");
    LongArithmetic zero("0");
    LongArithmetic bigPositive("2348728578273489289582394781292859829589234");
    LongArithmetic bigPositiveWithChangeLessInMiddle("2348728578273489289582394781292849829589234");
    LongArithmetic secondZero("0");
    LongArithmetic shortNumber("23432");
    LongArithmetic shortNumberWithChange("23532");
    EXPECT_TRUE(bigNegative < zero);
    EXPECT_TRUE(bigPositive > zero);
    EXPECT_TRUE(bigNegative < bigPositive);
    EXPECT_TRUE(bigPositive > bigPositiveWithChangeLessInMiddle);
    EXPECT_TRUE(zero == secondZero);
    EXPECT_TRUE(shortNumber < shortNumberWithChange);
    EXPECT_TRUE(shortNumber == shortNumberWithChange - LongArithmetic("100"));
}

TEST(LongAtithmeticTests, testOperators){
    LongArithmetic bigNegative("-124284823748682384773284787483782742347286283578178234");
    LongArithmetic zero("0");
    LongArithmetic bigPositive("2348728578273489289582394781292859829589234");
    LongArithmetic bigPositiveWithChangeLessInMiddle("2348728578273489289582394781292849829589234");
    LongArithmetic secondZero("0");
    LongArithmetic shortNumber("23432");
    LongArithmetic shortNumberWithChange("23532");
    EXPECT_EQ((secondZero - zero).getString(), "0");
    EXPECT_EQ((-shortNumber).getString(), "-23432");
    EXPECT_EQ((- -shortNumber).getString(), "23432");
    EXPECT_EQ((shortNumberWithChange - shortNumber).getString(), "100");
    EXPECT_EQ((bigPositive - bigNegative).getString(), "124284823751031113351558276773365137128579143407767468");
    EXPECT_EQ((shortNumber - shortNumberWithChange).getString(), "-100");
    EXPECT_EQ((-shortNumber - shortNumberWithChange).getString(), to_string(-23532 - 23432));
    EXPECT_EQ((-shortNumberWithChange - shortNumber).getString(), to_string(-23532 - 23432));
    EXPECT_EQ((bigNegative - zero).getString(), bigNegative.getString());
    EXPECT_EQ((zero - bigNegative).getString(), (-bigNegative).getString());

    EXPECT_EQ((zero + bigNegative).getString(), bigNegative.getString());
    EXPECT_EQ((bigNegative + zero).getString(), bigNegative.getString());
    EXPECT_EQ((shortNumber + shortNumberWithChange).getString(), to_string(23532 + 23432));
    EXPECT_EQ((shortNumberWithChange + -shortNumber).getString(), "100");
    EXPECT_EQ((shortNumber + -shortNumberWithChange).getString(), "-100");

    EXPECT_EQ((zero * bigNegative).getString(), "0");
    EXPECT_EQ((zero * bigPositive).getString(), "0");
    EXPECT_EQ((bigPositive * bigNegative).getString(),
              "-291911317384213975115106324139422830039899970696505526369850456865949194996408425758666259532756");
    EXPECT_EQ((bigNegative * bigPositive).getString(),
              "-291911317384213975115106324139422830039899970696505526369850456865949194996408425758666259532756");
    EXPECT_EQ((bigPositive * -bigNegative).getString(),
              "291911317384213975115106324139422830039899970696505526369850456865949194996408425758666259532756");
    EXPECT_EQ((-bigPositive * bigNegative).getString(),
             "291911317384213975115106324139422830039899970696505526369850456865949194996408425758666259532756");

    EXPECT_EQ((bigNegative / bigPositive).getString(), "-52915788098");
    EXPECT_EQ((bigPositive / bigNegative).getString(), "0");
    EXPECT_EQ((bigNegative/bigNegative).getString(), "1");
    EXPECT_EQ((zero / bigNegative).getString(), "0");
    //EXPECT_EQ((LongArithmetic("-5") / LongArithmetic("2")).getString(), "-2");
    //EXPECT_EQ((bigNegative % bigPositive).getString(), "1045618834670226325508717124325986852041302");
    //EXPECT_EQ((bigPositive % bigNegative).getString(), "2348728578273489289582394781292859829589234");
    EXPECT_EQ((zero % bigNegative).getString(), "0");




}
