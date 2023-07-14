#pragma once

#include <essm/types/Traits.hpp>

namespace essm
{
    template<typename> struct StateTraits
    {
        static constexpr types::StateId id{};
        static constexpr types::StateName name{""};
    };
}
