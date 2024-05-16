#include <filesystem>
#include <vector>

#include "../src/insertion.h"
#include "gtest/gtest.h"

TEST(InsertionTest, ReturnedEvents) {
    std::queue<Event> expectedEvents;
    std::filesystem::path p = std::filesystem::current_path();
    std::string path = p.string() + "/../../examples/success insertion.txt";
    std::string expectedTimeStart = "09:00";
    std::string expectedTimeEnd = "19:00";
    std::ifstream file;
    unsigned int expectedRate = 10;
    unsigned int expectedTables = 4;

    expectedEvents.emplace(1, 0, "client1", "08:48");
    expectedEvents.emplace(1, 0, "client2", "09:41");
    expectedEvents.emplace(1, 0, "client1", "09:48");

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
    std::string path = p.string() + "/../../examples/empty line 1 exception.txt";
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
    paths.emplace_back(p.string() + "/../../examples/not number line 1 exception.txt");
    paths.emplace_back(p.string() + "/../../examples/not number line 3 exception.txt");
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
    paths.emplace_back(p.string() + "/../../examples/wrong time start.txt");
    paths.emplace_back(p.string() + "/../../examples/wrong time end.txt");
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
    paths.emplace_back(p.string() + "/../../examples/negative number line 1.txt");
    paths.emplace_back(p.string() + "/../../examples/negative number line 3.txt");
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
    paths.emplace_back(p.string() + "/../../examples/wrong time event.txt");
    paths.emplace_back(p.string() + "/../../examples/wrong id event.txt");
    paths.emplace_back(p.string() + "/../../examples/wrong client name.txt");
    paths.emplace_back(p.string() + "/../../examples/empty number table.txt");
    paths.emplace_back(p.string() + "/../../examples/excess number table.txt");
    std::ifstream file;

    unsigned int rate, tables;
    std::string timeStart, timeEnd;
    for (const auto& path: paths) {
        file.open(path);
        EXPECT_THROW(inputEvents(file, tables, rate, timeStart, timeEnd), std::invalid_argument);
        file.close();
    }
}