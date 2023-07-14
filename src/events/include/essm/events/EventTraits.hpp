#pragma once

#include <essm/types/Traits.hpp>

namespace essm
{
template<typename> struct EventTraits
{
    static constexpr types::EventId id{};
    static constexpr types::EventName name{""};
};
}
