#include <queue>

#include "../src/event.hpp"
#include "gtest/gtest.h"

struct EventFixture: public testing::Test {
    std::vector<Computer> computers;
    static void SetUpTestSuite() {
        Event::timeStartEnd("09:00", "10:00");
    }
};

TEST_F(EventFixture, RightInputEvents) {
    computers.emplace_back(1, 10);
    std::queue<std::string> expectedEvents;
    expectedEvents.emplace("09:00 1 client\n");
    expectedEvents.emplace("09:00 2 client 1\n");
    expectedEvents.emplace("09:00 3 client\n");
    expectedEvents.emplace("09:00 4 client\n");

    std::queue<Event> actualEvents;
    actualEvents.emplace(1, 0, "client", "09:00");
    actualEvents.emplace(2, 1, "client", "09:00");
    actualEvents.emplace(3, 0, "client", "09:00");
    actualEvents.emplace(4, 0, "client", "09:00");

    while(!expectedEvents.empty()) {
        EXPECT_EQ(expectedEvents.front(), actualEvents.front().lineEvent());
        expectedEvents.pop();
        actualEvents.pop();
    }
}

TEST_F(EventFixture, RightLogEventsForId1) {
    std::queue<std::string> expectedEvents;
    expectedEvents.emplace("08:00 13 NotOpenYet\n");
    expectedEvents.emplace("");
    expectedEvents.emplace("09:30 13 YouShallNotPass\n");

    std::queue<Event> actualEvents;
    actualEvents.emplace(1, 0, "client", "08:00");
    actualEvents.emplace(1, 0, "client", "09:00");
    actualEvents.emplace(1, 0, "client", "09:30");

    while(!expectedEvents.empty()) {
        EXPECT_EQ(expectedEvents.front(), actualEvents.front().runEvent(computers));
        expectedEvents.pop();
        actualEvents.pop();
    }
}

TEST_F(EventFixture, RightLogEventsForId2) {
    computers.emplace_back(1, 10);
    std::queue<std::string> expectedEvents;
    expectedEvents.emplace("09:00 13 ClientUnknown\n");
    expectedEvents.emplace("");
    expectedEvents.emplace("09:30 13 PlaceIsBusy\n");

    Event clientEnter(1, 0, "client", "09:00");
    clientEnter.runEvent(computers);
    std::queue<Event> actualEvents;
    actualEvents.emplace(2, 1, "unknown", "09:00");
    actualEvents.emplace(2, 1, "client", "09:00");
    actualEvents.emplace(2, 1, "client", "09:30");

    while(!expectedEvents.empty()) {
        EXPECT_EQ(expectedEvents.front(), actualEvents.front().runEvent(computers));
        expectedEvents.pop();
        actualEvents.pop();
    }
    Event clientExit(4, 0, "client", "09:00");
    clientExit.runEvent(computers);
}

TEST_F(EventFixture, RightLogEventsForId3) {
    computers.emplace_back(1, 10);
    std::queue<std::string> expectedEvents;
    expectedEvents.emplace("09:00 13 ICanWaitNoLonger!\n");
    expectedEvents.emplace("");
    expectedEvents.emplace("");
    expectedEvents.emplace("");
    expectedEvents.emplace("09:30 11 waiter\n");

    std::queue<Event> actualEvents;
    actualEvents.emplace(3, 0, "client1", "09:00");
    actualEvents.emplace(2, 1, "client1", "09:00");
    actualEvents.emplace(3, 0, "client2", "09:00");
    actualEvents.emplace(3, 0, "client3", "09:00");
    actualEvents.emplace(3, 0, "waiter", "09:30");

    while(!expectedEvents.empty()) {
        EXPECT_EQ(expectedEvents.front(), actualEvents.front().runEvent(computers));
        expectedEvents.pop();
        actualEvents.pop();
    }
    Event client1Exit(4, 0, "client1", "09:00");
    Event client2Exit(4, 0, "client2", "09:00");
    Event client3Exit(4, 0, "client3", "09:00");
    client1Exit.runEvent(computers);
    client2Exit.runEvent(computers);
    client3Exit.runEvent(computers);
}

TEST_F(EventFixture, RightLogEventsForId4) {
    computers.emplace_back(1, 10);
    std::queue<std::string> expectedEvents;
    expectedEvents.emplace("09:00 13 ClientUnknown\n");
    expectedEvents.emplace("09:00 12 client2 1\n");
    expectedEvents.emplace("");
    expectedEvents.emplace("");

    Event client1Enter(1, 0, "client1", "09:00");
    Event client1Sit(2, 1, "client1", "09:00");
    Event client2Wait(3, 0, "client2", "09:00");
    Event client3Wait(3, 0, "client3", "09:00");
    client1Enter.runEvent(computers);
    client1Sit.runEvent(computers);
    client2Wait.runEvent(computers);
    client3Wait.runEvent(computers);

    std::queue<Event> actualEvents;
    actualEvents.emplace(4, 0, "unknown", "09:00");
    actualEvents.emplace(4, 0, "client1", "09:00");
    actualEvents.emplace(4, 0, "client3", "09:00");
    actualEvents.emplace(4, 0, "client2", "09:00");

    while(!expectedEvents.empty()) {
        EXPECT_EQ(expectedEvents.front(), actualEvents.front().runEvent(computers));
        expectedEvents.pop();
        actualEvents.pop();
    }
}