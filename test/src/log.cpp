#include "log.hpp"

#include <doctest/doctest.h>
#include <fmt/core.h>

#include <string>

TEST_CASE("Log")
{
    oo::Log log;

    SUBCASE("Add unique messages")
    {
        const std::string message1 {"Message 1"};
        const std::string message2 {"Message 2"};
        const std::string message3 {"Message 3"};

        log.add(message1);
        log.add(message2);
        log.add(message3);

        const auto& messages {log.messages()};
        REQUIRE(messages.size() == 3);

        CHECK(messages[0].text == message1);
        CHECK(messages[1].text == message2);
        CHECK(messages[2].text == message3);
    }

    SUBCASE("Add repeated messages")
    {
        const std::string message1 {"Message 1"};
        const std::string message2 {"Message 2"};

        log.add(message1);
        log.add(message1);
        log.add(message2);

        const auto& messages {log.messages()};
        REQUIRE(messages.size() == 2);

        CHECK(messages[0].text == message1);
        CHECK(messages[0].count == 2);
        CHECK(messages[1].text == message2);
    }

    SUBCASE("Add more than the maximum number of messages")
    {
        constexpr auto max_messages {8};

        for (int i {1}; i <= max_messages + 2; ++i) {
            const std::string message {fmt::format("Message {}", std::to_string(i))};
            log.add(message);
        }

        const auto& messages {log.messages()};
        REQUIRE(messages.size() == max_messages);
    }
}
