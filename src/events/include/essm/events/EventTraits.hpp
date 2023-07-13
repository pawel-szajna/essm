#pragma once

namespace essm
{
template<typename> struct EventTraits
{
    static constexpr unsigned int eventId{};
    static constexpr auto eventName{""};
};
}
