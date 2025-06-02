#include <gtest/gtest.h>
#include "Field/Street.hpp"
#include "Field/Station.hpp"
#include "Field/Utility.hpp"
#include <strstream>

using namespace Fields;

TEST(StreetTests, Constructor) {
    Street street(10, 200, 24, 50, 100, 200, 300, 400, "test street", Color::Lightblue);
    ASSERT_EQ(street.getPosition(), 10);
    ASSERT_EQ(street.getPurchasePrice(), 200);
    ASSERT_EQ(street.getRent(), 24);
    ASSERT_EQ(street.getName(), "test street");
    ASSERT_EQ(street.getInfo(), TYPE::STREET);
    ASSERT_EQ(street.getOwner(), 0);
    ASSERT_FALSE(street.isMortgaged());
    ASSERT_FALSE(street.isOwned());
    ASSERT_EQ(street.getHouseCount(), 0);
    ASSERT_EQ(street.getHousePrice(), 50);
    ASSERT_EQ(street.getColor(), Color::Lightblue);
}

TEST(StreetTests, MortgageAndPurchase) {
    Street street(10, 200, 24, 50, 100, 200, 300, 400, "test street", Color::Lightblue);
    ASSERT_FALSE(street.isOwned());
    ASSERT_FALSE(street.isMortgaged());
    ASSERT_EQ(street.mortgage(), 0);
    ASSERT_EQ(street.unmortgage(), 0);
    ASSERT_EQ(street.removeOwner(), 0);
    street.setOwner(2);
    ASSERT_TRUE(street.isOwned());
    ASSERT_EQ(street.getOwner(), 2);
    ASSERT_EQ(street.mortgage(), 100);
    ASSERT_EQ(street.unmortgage(), 100);
    ASSERT_EQ(street.removeOwner(), 200);
}

TEST(StreetTests, Houses) {
    Street street(10, 200, 24, 50, 100, 200, 300, 400, "test street", Color::Lightblue);
    street.setOwner(3);
    ASSERT_EQ(street.getHouseCount(), 0);
    ASSERT_EQ(street.getRent(), 24);
    ASSERT_EQ(street.purchaseHouse(), 50);
    ASSERT_EQ(street.getHouseCount(), 1);
    ASSERT_EQ(street.getRent(), 50);
    ASSERT_EQ(street.purchaseHouse(), 50);
    ASSERT_EQ(street.getHouseCount(), 2);
    ASSERT_EQ(street.getRent(), 100);
    ASSERT_EQ(street.purchaseHouse(), 50);
    ASSERT_EQ(street.getHouseCount(), 3);
    ASSERT_EQ(street.getRent(), 200);
    ASSERT_EQ(street.purchaseHouse(), 50);
    ASSERT_EQ(street.getHouseCount(), 4);
    ASSERT_EQ(street.getRent(), 300);
    ASSERT_EQ(street.purchaseHouse(), 50);
    ASSERT_EQ(street.getHouseCount(), 5);
    ASSERT_EQ(street.getRent(), 400);
    ASSERT_EQ(street.purchaseHouse(), 0);
    ASSERT_EQ(street.getHouseCount(), 5);
    ASSERT_EQ(street.getRent(), 400);
    ASSERT_EQ(street.sellHouse(), 50);
    ASSERT_EQ(street.getRent(), 300);
    ASSERT_EQ(street.sellHouse(), 50);
    ASSERT_EQ(street.getRent(), 200);
    ASSERT_EQ(street.sellHouse(), 50);
    ASSERT_EQ(street.getRent(), 100);
    ASSERT_EQ(street.sellHouse(), 50);
    ASSERT_EQ(street.getRent(), 50);
    ASSERT_EQ(street.sellHouse(), 50);
    ASSERT_EQ(street.getRent(), 24);
    ASSERT_EQ(street.sellHouse(), 0);
    ASSERT_EQ(street.getRent(), 24);
}

TEST(StreetTests, InputConstructor) {
    Street street;
    std::istringstream iss("9 120 8 40 100 300 450 600 Lightblue Targowa");
    iss >> street;
    ASSERT_EQ(street.getPosition(), 9);
    ASSERT_EQ(street.getPurchasePrice(), 120);
    ASSERT_EQ(street.getRent(), 8);
    ASSERT_EQ(street.getName(), "Targowa");
    ASSERT_EQ(street.getInfo(), TYPE::STREET);
    ASSERT_EQ(street.getOwner(), 0);
    ASSERT_FALSE(street.isMortgaged());
    ASSERT_FALSE(street.isOwned());
    ASSERT_EQ(street.getHouseCount(), 0);
    ASSERT_EQ(street.getHousePrice(), 50);
    ASSERT_EQ(street.getColor(), Color::Lightblue);

    ASSERT_EQ(street.getHouseCount(), 0);
    ASSERT_EQ(street.getRent(), 8);
    ASSERT_EQ(street.purchaseHouse(), 50);
    ASSERT_EQ(street.getHouseCount(), 1);
    ASSERT_EQ(street.getRent(), 40);
    ASSERT_EQ(street.purchaseHouse(), 50);
    ASSERT_EQ(street.getHouseCount(), 2);
    ASSERT_EQ(street.getRent(), 100);
    ASSERT_EQ(street.purchaseHouse(), 50);
    ASSERT_EQ(street.getHouseCount(), 3);
    ASSERT_EQ(street.getRent(), 300);
    ASSERT_EQ(street.purchaseHouse(), 50);
    ASSERT_EQ(street.getHouseCount(), 4);
    ASSERT_EQ(street.getRent(), 450);
    ASSERT_EQ(street.purchaseHouse(), 50);
    ASSERT_EQ(street.getHouseCount(), 5);
    ASSERT_EQ(street.getRent(), 600);
}

TEST(StationTests, Constructor) {
    Station station(5, "station");
    ASSERT_EQ(station.getPosition(), 5);
    ASSERT_EQ(station.getName(), "station");
    ASSERT_EQ(station.getInfo(), TYPE::STATION);
    ASSERT_EQ(station.getPurchasePrice(), 200);
    ASSERT_EQ(station.getRent(), 50);
}

TEST(StationTests, MortgageAndPurchase) {
    Station station(15, "station");
    ASSERT_FALSE(station.isOwned());
    ASSERT_FALSE(station.isMortgaged());
    ASSERT_EQ(station.mortgage(), 0);
    ASSERT_EQ(station.unmortgage(), 0);
    ASSERT_EQ(station.removeOwner(), 0);
    station.setOwner(2);
    ASSERT_TRUE(station.isOwned());
    ASSERT_EQ(station.getOwner(), 2);
    ASSERT_EQ(station.mortgage(), 100);
    ASSERT_EQ(station.unmortgage(), 100);
    ASSERT_EQ(station.removeOwner(), 200);
}