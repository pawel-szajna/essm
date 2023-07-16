#pragma once

#include <essm/events/EventTraits.hpp>
#include <essm/helpers/Hash.hpp>

#include <cstdint>

namespace essm
{
#if defined(__GNUC__)
    #define __essm_event_traits_type(name_) essm::EventTraits<name_>
#else
    #define __essm_event_traits_type(name_) ::essm::EventTraits<name_>
#endif

#define __essm_event_create_traits(id_, name_)                                                                         \
    template<>                                                                                                         \
    struct __essm_event_traits_type(name_)                                                                             \
    {                                                                                                                  \
        static constexpr essm::types::EventId id     = id_;                                                            \
        static constexpr essm::types::EventName name = #name_;                                                         \
    }

/**
 * @brief Generate event traits
 *
 * Auto-generates event traits, with the event ID being created by hashing the event name. This macro must be called
 * from the global namespace.
 *
 * @param name_ Event type
 *
 * Example:
 *
 * @code
 * namespace Events
 * {
 * struct Order
 * {
 *     int id;
 *     int amount;
 * }
 * }
 *
 * essm_event_traits(Events::Order);
 * @endcode
 */
#define essm_event_traits(name_) __essm_event_create_traits(::essm::helpers::hash(#name_), name_)

/**
 * @brief Define an event type
 *
 * This macro actually auto-generates the corresponding EventTraits type, with the event identifier created by hashing
 * the event type name. For event types contained within namespaces, essm_event_traits() should be used in the global
 * namespace instead to generate the traits.
 *
 * @param name_ Name of the struct to be created
 *
 * Example:
 *
 * @code
 * essm_event(Request)
 * {
 *     int owner;
 *     std::string query;
 *     bool& anotherField;
 * };
 * @endcode
 */
#define essm_event(name_)                                                                                              \
    struct name_;                                                                                                      \
    essm_event_traits(name_);                                                                                          \
    struct name_

} // namespace essm
