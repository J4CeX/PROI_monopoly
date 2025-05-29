#include <gtest/gtest.h>
#include "EventCard.hpp"
#include "EventCardContainer.hpp"

using namespace Events;

TEST(EventCardTests, Constructor) {
    EventCard eventCard(MovementType::absolute, 10, 0, CardType::chance,
        "test", 50, 10, 20, 30, true, false);
    ASSERT_EQ(eventCard.getMovementType(), MovementType::absolute);
    ASSERT_EQ(eventCard.getCardId(), 0);
    ASSERT_EQ(eventCard.getLocation(), 10);
    ASSERT_EQ(eventCard.getCardType(), CardType::chance);
    ASSERT_EQ(eventCard.getText(), "test");
    ASSERT_EQ(eventCard.getBankBalance(), 50);
    ASSERT_EQ(eventCard.getEachPlayerBalance(), 10);
    ASSERT_EQ(eventCard.getPerHouseBalance(), 20);
    ASSERT_EQ(eventCard.getPerHotelBalance(), 30);
    ASSERT_TRUE(eventCard.isGoFieldCollectable());
    ASSERT_FALSE(eventCard.isGetOutOfJailFree());
    ASSERT_TRUE(eventCard.isFilled());
}

TEST(EventCardTests, DefaultConstructor) {
    EventCard eventCard;
    ASSERT_EQ(eventCard.getMovementType(), MovementType::relativeForward);
    ASSERT_EQ(eventCard.getCardId(), 0);
    ASSERT_EQ(eventCard.getLocation(), 0);
    ASSERT_EQ(eventCard.getCardType(), CardType::chance);
    ASSERT_EQ(eventCard.getText(), "");
    ASSERT_EQ(eventCard.getBankBalance(), 0);
    ASSERT_EQ(eventCard.getEachPlayerBalance(), 0);
    ASSERT_EQ(eventCard.getPerHouseBalance(), 0);
    ASSERT_EQ(eventCard.getPerHotelBalance(), 0);
    ASSERT_TRUE(eventCard.isGoFieldCollectable());
    ASSERT_FALSE(eventCard.isGetOutOfJailFree());
    ASSERT_FALSE(eventCard.isFilled());
}

TEST(EventCardTests, movementTarget) {
    EventCard firstEventCard;
    ASSERT_EQ(firstEventCard.movementTarget(10, 20), 10);
    EventCard secEventCard(MovementType::absolute, 10, 0, CardType::chance,
        "test", 50, 10, 20, 30, true, false);
    ASSERT_EQ(secEventCard.movementTarget(50, 40), 10);
    EventCard thEventCard(MovementType::relativeBackward, 10, 0, CardType::chance,
        "test", 50, 10, 20, 30, true, false);
    ASSERT_EQ(thEventCard.movementTarget(50, 40), 0);
}

TEST(EventCardContainerTests, ConstructorAndAddCard) {
    EventCardContainer eventCardContainer;
    EventCard firstEventCard;
    EventCard secEventCard(MovementType::absolute, 10, 1, CardType::chance,
        "test", 50, 10, 20, 30, true, false);
    EventCard thEventCard(MovementType::relativeBackward, 10, 2, CardType::chance,
        "test", 50, 10, 20, 30, true, false);
    eventCardContainer.addCard(firstEventCard);
    eventCardContainer.addCard(secEventCard);
    eventCardContainer.addCard(thEventCard);
    ASSERT_EQ(eventCardContainer.length(), 3);
    ASSERT_EQ(eventCardContainer[0].getMovementType(), MovementType::relativeForward);
    ASSERT_EQ(eventCardContainer[1].getMovementType(), MovementType::absolute);
    ASSERT_EQ(eventCardContainer[2].getMovementType(), MovementType::relativeBackward);
}