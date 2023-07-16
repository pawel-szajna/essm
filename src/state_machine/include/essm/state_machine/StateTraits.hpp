#pragma once

#include <essm/types/Traits.hpp>

namespace essm
{
template<typename>
struct StateTraits
{
    constexpr static types::StateId id{};
    constexpr static types::StateName name{""};
};
} // namespace essm
