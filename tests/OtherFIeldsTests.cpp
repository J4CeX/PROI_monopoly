#include <gtest/gtest.h>
#include "Field/ChanceField.hpp"
#include "Field/CommunityChestField.hpp"
#include "Field/GoToJail.hpp"
#include "Field/IncomeTax.hpp"
#include "Field/Jail.hpp"
#include "Field/LuxuryTax.hpp"
#include "Field/Parking.hpp"
#include "Field/StartField.hpp"
#include <sstream>

using namespace Fields;

TEST(ChanceFieldTests, Constructor) {
    ChanceField chanceField(8);
    ASSERT_EQ(chanceField.getPosition(), 8);
    ASSERT_EQ(chanceField.getInfo(), TYPE::CHANCEFIELD);
}

TEST(ChanceFieldTests, InputConstructor) {
    ChanceField chanceField;
    std::istringstream iss("23");
    iss >> chanceField;
    ASSERT_EQ(chanceField.getPosition(), 23);
    ASSERT_EQ(chanceField.getInfo(), TYPE::CHANCEFIELD);
}

TEST(CommunityFieldTests, Constructor) {
    CommunityChestField communityChestField(4);
    ASSERT_EQ(communityChestField.getPosition(), 4);
    ASSERT_EQ(communityChestField.getInfo(), TYPE::COMMUNITYCHESTFIELD);
}

TEST(CommunityFieldTests, InputConstructor) {
    CommunityChestField communityChestField;
    std::istringstream iss("6");
    iss >> communityChestField;
    ASSERT_EQ(communityChestField.getPosition(), 6);
    ASSERT_EQ(communityChestField.getInfo(), TYPE::COMMUNITYCHESTFIELD);
}

TEST(GoToJailTests, Constructor) {
    GoToJail goToJail(10);
    ASSERT_EQ(goToJail.getPosition(), 10);
    ASSERT_EQ(goToJail.getInfo(), TYPE::GOTOJAIL);
}

TEST(GoToJailTests, InputConstructor) {
    GoToJail goToJail;
    std::istringstream iss("11");
    iss >> goToJail;
    ASSERT_EQ(goToJail.getPosition(), 11);
    ASSERT_EQ(goToJail.getInfo(), TYPE::GOTOJAIL);
}

TEST(IncomeTaxTests, Constructor) {
    IncomeTax incomeTax(35);
    ASSERT_EQ(incomeTax.getPosition(), 35);
    ASSERT_EQ(incomeTax.getInfo(), TYPE::INCOMETAX);
    ASSERT_EQ(incomeTax.getIncome(), 200);
}

TEST(IncomeTaxTests, InputConstructor) {
    IncomeTax incomeTax;
    std::istringstream iss("36");
    iss >> incomeTax;
    ASSERT_EQ(incomeTax.getPosition(), 36);
    ASSERT_EQ(incomeTax.getInfo(), TYPE::INCOMETAX);
    ASSERT_EQ(incomeTax.getIncome(), 200);
}

TEST(JailTests, Constructor) {
    Jail jail(30);
    ASSERT_EQ(jail.getPosition(), 30);
    ASSERT_EQ(jail.getInfo(), TYPE::JAIL);
}

TEST(JailTests, InputConstructor) {
    Jail jail;
    std::istringstream iss("29");
    iss >> jail;
    ASSERT_EQ(jail.getPosition(), 29);
    ASSERT_EQ(jail.getInfo(), TYPE::JAIL);
}