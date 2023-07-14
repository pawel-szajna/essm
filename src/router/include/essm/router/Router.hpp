#pragma once

#include <essm/types/ProcessingStatus.hpp>
#include <essm/events/EventTraits.hpp>
#include <essm/service/EventService.hpp>
#include <essm/logger/Logger.hpp>

#include <unordered_map>

namespace essm
{
class Router
{

public:

    /**
     * @brief Registers a service to handle a message.
     *
     * @tparam Event Event type
     * @param service Service instance
     *
     * The user of this method has to take care that the service lives at least as long as the router
     * (or, in the worst case, that the router receives no requests to process this type of events after
     * the service is no longer alive).
     */
    template<typename Event>
    void registerService(EventService& service)
    {
        __essm_logger_debug("ESSMrouter",
                            "Registered service for {} ({:#x})",
                            EventTraits<Event>::name,
                            EventTraits<Event>::id);
        services[EventTraits<Event>::id] = &service;
    }

    /**
     * @brief Processes the event.
     *
     * @param event Event to process
     * @return Processing status of the event
     *
     * The processing will fail (with a Failure status) if there is no handler registered for the passed event.
     * The processing will result in a segmentation fault if the registered handler had been destructed.
     */
    template<typename Event>
    ProcessingStatus process(const Event& event) const
    {
        __essm_logger_debug("ESSMrouter",
                            "Received event {} ({:#x})",
                            EventTraits<Event>::name,
                            EventTraits<Event>::id);

        if (not services.contains(EventTraits<Event>::id))
        {
            __essm_logger_error("ESSMrouter",
                                "Routing failed: no service registered for {} ({:#x})",
                                EventTraits<Event>::name,
                                EventTraits<Event>::id);
            return ProcessingStatus::Failure;
        }

        return services.at(EventTraits<Event>::id)->handle(event);
    }

private:

    std::unordered_map<unsigned int, EventService*> services{};

};
}
