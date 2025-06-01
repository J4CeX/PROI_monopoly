#include <gtest/gtest.h>
#include <Field/IncomeTax.hpp>
#include <Field/LuxuryTax.hpp>
#include <sstream>

using namespace Fields;

TEST(IncomeTaxTests, Constructor) {
    IncomeTax incomeTax(10);
    ASSERT_EQ(incomeTax.getInfo(), TYPE::INCOMETAX);
    ASSERT_EQ(incomeTax.getPosition(), 10);
    ASSERT_EQ(incomeTax.getIncome(), 200);
}

TEST(IncomeTaxTests, InputOperatorConstructor) {
    IncomeTax incomeTax;
    std::istringstream iss("38");
    iss >> incomeTax;
    ASSERT_EQ(incomeTax.getInfo(), TYPE::INCOMETAX);
    ASSERT_EQ(incomeTax.getPosition(), 38);
    ASSERT_EQ(incomeTax.getIncome(), 200);
}

TEST(LuxuryTaxTests, Constructor) {
    LuxuryTax luxuryTax(20);
    ASSERT_EQ(luxuryTax.getInfo(), TYPE::LUXURYTAX);
    ASSERT_EQ(luxuryTax.getPosition(), 20);
    ASSERT_EQ(luxuryTax.getIncome(), 100);
}

TEST(LuxuryTaxTests, InputOperatorConstructor) {
    LuxuryTax luxuryTax;
    std::istringstream iss("28");
    iss >> luxuryTax;
    ASSERT_EQ(luxuryTax.getInfo(), TYPE::LUXURYTAX);
    ASSERT_EQ(luxuryTax.getPosition(), 28);
    ASSERT_EQ(luxuryTax.getIncome(), 100);
}