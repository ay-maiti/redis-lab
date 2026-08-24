#include <gtest/gtest.h>

#include "protocol/command_parser.h"

using namespace redis_lab;

TEST(CommandParserTest, ParsesPing)
{
    CommandParser parser;

    auto command = parser.Parse("PING");

    ASSERT_TRUE(command.has_value());
    EXPECT_EQ(command->type, CommandType::PING);
    EXPECT_TRUE(command->args.empty());
}

TEST(CommandParserTest, ParsesGet)
{
    CommandParser parser;

    auto command = parser.Parse("GET key");

    ASSERT_TRUE(command.has_value());
    EXPECT_EQ(command->type, CommandType::GET);

    ASSERT_EQ(command->args.size(), 1);
    EXPECT_EQ(command->args[0], "key");
}

TEST(CommandParserTest, ParsesSet)
{
    CommandParser parser;

    auto command = parser.Parse("SET key value");

    ASSERT_TRUE(command.has_value());
    EXPECT_EQ(command->type, CommandType::SET);

    ASSERT_EQ(command->args.size(), 2);
    EXPECT_EQ(command->args[0], "key");
    EXPECT_EQ(command->args[1], "value");
}

TEST(CommandParserTest, ParsesDelete)
{
    CommandParser parser;

    auto command = parser.Parse("DEL key");

    ASSERT_TRUE(command.has_value());
    EXPECT_EQ(command->type, CommandType::DEL);
}

TEST(CommandParserTest, ParsesExists)
{
    CommandParser parser;

    auto command = parser.Parse("EXISTS key");

    ASSERT_TRUE(command.has_value());
    EXPECT_EQ(command->type, CommandType::EXISTS);
}

TEST(CommandParserTest, RejectsEmptyInput)
{
    CommandParser parser;

    EXPECT_FALSE(parser.Parse("").has_value());
}

TEST(CommandParserTest, RejectsUnknownCommand)
{
    CommandParser parser;

    EXPECT_FALSE(parser.Parse("HELLO key").has_value());
}

TEST(CommandParserTest, RejectsGetWithoutKey)
{
    CommandParser parser;

    EXPECT_FALSE(parser.Parse("GET").has_value());
}

TEST(CommandParserTest, RejectsSetWithoutValue)
{
    CommandParser parser;

    EXPECT_FALSE(parser.Parse("SET key").has_value());
}

TEST(CommandParserTest, RejectsExtraArguments)
{
    CommandParser parser;

    EXPECT_FALSE(parser.Parse("SET key value extra").has_value());
}

TEST(CommandParserTest, HandlesMultipleSpaces)
{
    CommandParser parser;

    auto command = parser.Parse("SET   key   value");

    ASSERT_TRUE(command.has_value());
    EXPECT_EQ(command->type, CommandType::SET);

    ASSERT_EQ(command->args.size(), 2);
    EXPECT_EQ(command->args[0], "key");
    EXPECT_EQ(command->args[1], "value");
}   