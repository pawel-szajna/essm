#pragma once

namespace essm
{
template<typename> struct EventTraits{};

// TODO: Implement consteval hashing of event name for automated ID generation

#define essm_event(id, name)                    \
struct name;                                    \
template<> struct ::essm::EventTraits<name>     \
{                                               \
    static constexpr unsigned int eventId = id; \
    static constexpr auto eventName = #name;    \
};                                              \
struct name

}
