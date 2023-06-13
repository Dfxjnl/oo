#include "log.hpp"

#include <string>
#include <string_view>

namespace oo
{
void Log::add(const std::string_view message)
{
    // Check if it's a repeat of the last message.
    if (!m_messages.empty()) {
        auto& last {m_messages.back()};

        if (last.text == message) {
            // It is, so just increase the count.
            ++last.count;
            return;
        }
    }

    // It's a new message.
    m_messages.push_back({std::string {message}});

    constexpr auto max_messages {8};

    if (m_messages.size() > max_messages) {
        m_messages.pop_front();
    }
}
} // namespace oo
