#include <filesystem>
#include <vector>

#include "../src/insertion.hpp"
#include "gtest/gtest.h"

TEST(InsertionTest, ReturnedEvents) {
    std::queue<Event> expectedEvents;
    std::filesystem::path p = std::filesystem::current_path();
    std::string path = p.string() + "/../../tests/examples/success insertion.txt";
    std::string expectedTimeStart = "09:00";
    std::string expectedTimeEnd = "19:00";
    std::ifstream file;
    unsigned int expectedRate = 10;
    unsigned int expectedTables = 3;

    expectedEvents.emplace(1, 0, "client1", "08:48");
    expectedEvents.emplace(1, 0, "client1", "09:41");
    expectedEvents.emplace(1, 0, "client2", "09:48");
    expectedEvents.emplace(3, 0, "client1", "09:52");
    expectedEvents.emplace(2, 1, "client1", "09:54");
    expectedEvents.emplace(2, 2, "client2", "10:25");
    expectedEvents.emplace(1, 0, "client3", "10:58");
    expectedEvents.emplace(2, 3, "client3", "10:59");
    expectedEvents.emplace(1, 0, "client4", "11:30");
    expectedEvents.emplace(2, 2, "client4", "11:35");
    expectedEvents.emplace(3, 0, "client4", "11:45");
    expectedEvents.emplace(4, 0, "client1", "12:33");
    expectedEvents.emplace(4, 0, "client2", "12:43");
    expectedEvents.emplace(4, 0, "client4", "15:52");

    file.open(path);

    unsigned int actualRate, actualTables;
    std::string actualTimeStart, actualTimeEnd;
    std::queue<Event> actualEvents = inputEvents(file, actualTables, actualRate, actualTimeStart, actualTimeEnd);
    file.close();

    EXPECT_EQ(expectedRate, actualRate) << "Problem with rate!";
    EXPECT_EQ(expectedTables, actualTables) << "Problem with tables!";
    EXPECT_EQ(expectedTimeStart, actualTimeStart) << "Problem with start time!";
    EXPECT_EQ(expectedTimeEnd, actualTimeEnd) << "Problem with end time!";

    ASSERT_EQ(expectedEvents.size(), actualEvents.size()) << "Problem with events!";
    while(!expectedEvents.empty()) {
        EXPECT_EQ(expectedEvents.front().lineEvent(), actualEvents.front().lineEvent());
        expectedEvents.pop();
        actualEvents.pop();
    }
}

TEST(InsertionTest, EmptyException) {
    std::filesystem::path p = std::filesystem::current_path();
    std::string path = p.string() + "/../../tests/examples/empty line 1 exception.txt";
    std::ifstream file;
    unsigned int rate, tables;
    std::string timeStart, timeEnd;

    file.open(path);
    EXPECT_THROW(inputEvents(file, tables, rate, timeStart, timeEnd), std::invalid_argument);
    file.close();
}

TEST(InsertionTest, NotNumberException) {
    std::filesystem::path p = std::filesystem::current_path();
    std::vector<std::string> paths;
    paths.emplace_back(p.string() + "/../../tests/examples/not number line 1 exception.txt");
    paths.emplace_back(p.string() + "/../../tests/examples/not number line 3 exception.txt");
    std::ifstream file;

    unsigned int rate, tables;
    std::string timeStart, timeEnd;
    for (const auto& path: paths) {
        file.open(path);
        EXPECT_THROW(inputEvents(file, tables, rate, timeStart, timeEnd), std::invalid_argument);
        file.close();
    }
}

TEST(InsertionTest, WrongTimeException) {
    std::filesystem::path p = std::filesystem::current_path();
    std::vector<std::string> paths;
    paths.emplace_back(p.string() + "/../../tests/examples/wrong time start.txt");
    paths.emplace_back(p.string() + "/../../tests/examples/wrong time end.txt");
    std::ifstream file;

    unsigned int rate, tables;
    std::string timeStart, timeEnd;

    for (const auto& path: paths) {
        file.open(path);
        EXPECT_THROW(inputEvents(file, tables, rate, timeStart, timeEnd), std::invalid_argument);
        file.close();
    }
}

TEST(InsertionTest, NegativeNumberException) {
    std::filesystem::path p = std::filesystem::current_path();
    std::vector<std::string> paths;
    paths.emplace_back(p.string() + "/../../tests/examples/negative number line 1.txt");
    paths.emplace_back(p.string() + "/../../tests/examples/negative number line 3.txt");
    std::ifstream file;

    unsigned int rate, tables;
    std::string timeStart, timeEnd;

    for (const auto& path: paths) {
        file.open(path);
        EXPECT_THROW(inputEvents(file, tables, rate, timeStart, timeEnd), std::invalid_argument);
        file.close();
    }
}

TEST(InsertionTest, WrongEventException) {
    std::filesystem::path p = std::filesystem::current_path();
    std::vector<std::string> paths;
    paths.emplace_back(p.string() + "/../../tests/examples/wrong time event.txt");
    paths.emplace_back(p.string() + "/../../tests/examples/lesser time event.txt");
    paths.emplace_back(p.string() + "/../../tests/examples/wrong id event.txt");
    paths.emplace_back(p.string() + "/../../tests/examples/wrong client name.txt");
    paths.emplace_back(p.string() + "/../../tests/examples/empty number table.txt");
    paths.emplace_back(p.string() + "/../../tests/examples/excess number table.txt");
    std::ifstream file;

    unsigned int rate, tables;
    std::string timeStart, timeEnd;
    for (const auto& path: paths) {
        file.open(path);
        EXPECT_THROW(inputEvents(file, tables, rate, timeStart, timeEnd), std::invalid_argument);
        file.close();
    }
}