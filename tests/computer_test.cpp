#include "../src/computer.hpp"
#include "gtest/gtest.h"

TEST(ComputerTest, RigthNumberPaymentAndClient) {
    unsigned int expectedNumber = 5;
    unsigned int expectedPayment = 0;
    std::string expectedName = "client";

    Computer computer(5, 10);
    computer.busyOn("client", "09:00");

    EXPECT_EQ(computer.computerNumber(), expectedNumber);
    EXPECT_EQ(computer.computerPayment(), expectedPayment);
    EXPECT_EQ(computer.name(), expectedName);
    EXPECT_TRUE(computer.isBusy());
}

TEST(ComputerTest, AfterOneClient) {
    Computer computer(1, 15);
    unsigned int expectedPayment = 150;
    std::string expectedTime = "09:35";

    computer.busyOn("client", "09:25");
    computer.busyOff("19:00");

    EXPECT_EQ(computer.computerPayment(), expectedPayment);
    EXPECT_EQ(computer.time(), expectedTime);
}

TEST(ComputerTest, AfterThreeClients) {
    Computer computer(1, 15);
    unsigned int expectedPayment = 150;
    std::string expectedTime = "08:36";

    computer.busyOn("client1", "09:25");
    computer.busyOff("10:26"); //payment - 30, time - 01:01
    computer.busyOn("client2", "10:28");
    computer.busyOff("13:28"); //payment - 45, time - 03:00
    computer.busyOn("client3", "13:30");
    computer.busyOff("18:05"); //payment - 75, time - 04:35

    EXPECT_EQ(computer.computerPayment(), expectedPayment);
    EXPECT_EQ(computer.time(), expectedTime);
}

TEST(ComputerTest, NoInvasion) {
    std::string expectedName = "client";
    Computer computer(1, 1);

    computer.busyOn(expectedName, "09:00");
    computer.busyOn("invader", "09:01");

    EXPECT_EQ(computer.name(), expectedName);
}