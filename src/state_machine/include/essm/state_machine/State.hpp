#pragma once

// TODO: Extract the hashing functions to a common place

#include <essm/events/Event.hpp>
#include <essm/events/EventTraits.hpp>

#define essm_state(name_)                                                  \
    struct name_ {};                                                       \
    template<> struct essm::StateTraits<name_>                             \
    {                                                                      \
        constexpr static types::StateId id = ::essm::detail::hash(#name_); \
        constexpr static types::StateName name = #name_;                   \
    }
