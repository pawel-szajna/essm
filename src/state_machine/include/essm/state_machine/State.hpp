#pragma once

#include <essm/events/EventTraits.hpp>
#include <essm/helpers/Hash.hpp>

#define essm_state(name_)                                                                                              \
    struct name_                                                                                                       \
    {                                                                                                                  \
    };                                                                                                                 \
    template<>                                                                                                         \
    struct essm::StateTraits<name_>                                                                                    \
    {                                                                                                                  \
        constexpr static types::StateId id     = ::essm::helpers::hash(#name_);                                        \
        constexpr static types::StateName name = #name_;                                                               \
    }
