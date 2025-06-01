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