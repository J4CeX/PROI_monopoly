#include <gtest/gtest.h>
#include "Field/Street.hpp"
#include "Field/Station.hpp"
#include "Field/Utility.hpp"

using namespace Fields;

TEST(StreetTests, Constructor) {
    Street street(10, 200, 24, 50, 100, 200, 300, 400, "test street", Color::Lightblue);
    ASSERT_EQ(street.getPosition(), 10);
    ASSERT_EQ(street.getPurchasePrice(), 200);
    ASSERT_EQ(street.getRent(), 24);
    ASSERT_EQ(street.getName(), "test street");
    ASSERT_EQ(street.getInfo(), TYPE::STREET);
    ASSERT_THROW(street.getOwner(), std::runtime_error);
    ASSERT_FALSE(street.isMortgaged());
    ASSERT_FALSE(street.isOwned());
    ASSERT_EQ(street.getHouseCount(), 0);
    ASSERT_EQ(street.getHousePrice(), 50);
}