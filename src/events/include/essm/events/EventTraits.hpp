#pragma once

#include <essm/types/Traits.hpp>

namespace essm
{
template<typename>
struct EventTraits
{
    constexpr static types::EventId id{};
    constexpr static types::EventName name{""};
};
} // namespace essm
