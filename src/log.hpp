#ifndef OO_LOG_HPP
#define OO_LOG_HPP

#include <deque>
#include <string>
#include <string_view>

namespace oo
{
struct Message
{
    std::string text;

    // The number of times this message has been repeated.
    int count {1};
};

class Log
{
public:
    void add(std::string_view message);

    [[nodiscard]] inline auto messages() const noexcept { return m_messages; }

private:
    std::deque<Message> m_messages;
};
} // namespace oo

#endif // OO_LOG_HPP
