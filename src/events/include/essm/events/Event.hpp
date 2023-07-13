#pragma once

namespace essm
{
template<typename> struct EventTraits{};

#define essm_event(id, name)                    \
struct name;                                    \
template<> struct ::essm::EventTraits<name>     \
{                                               \
    static constexpr unsigned int eventId = id; \
    static constexpr auto eventName = #name;    \
};                                              \
struct name

}
