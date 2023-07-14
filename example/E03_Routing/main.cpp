//~ # Example 3: A simple router
//~
//~ This example shows how message handling can be done automatically using a simple event router
//~ to distribute events to services based on their type.

#include <cassert>

#include <essm/logger/Logger.hpp>
#include <essm/router/Router.hpp>
#include <essm/events/Event.hpp>
#include <essm/service/EventService.hpp>

//~ We define several event types:

essm_event(EventA) {};
essm_event(EventB) {};
essm_event(EventC) {};
essm_event(EventD) {};

//~ We define two services, `ServiceA` which can handle `EventA`, and `ServiceB` which can handle `EventB`:

class ServiceA : public essm::EventService
{
public:
    ServiceA()
    {
        registerHandler(&ServiceA::handleA);
    }
private:
    essm::ProcessingStatus handleA(const EventA&)
    {
        essm_info("Received event A in service A");
        return essm::ProcessingStatus::Success;
    }
};

class ServiceB : public essm::EventService
{
public:
    ServiceB()
    {
        registerHandler(&ServiceB::handleB);
    }
private:
    essm::ProcessingStatus handleB(const EventB&)
    {
        essm_info("Received event B in service B");
        return essm::ProcessingStatus::Success;
    }
};

//~ Then we proceed with a few experiments:

int main()
{
    essm_info("Starting routing demo");

    //~ We set up the router and services:

    essm::Router router;
    ServiceA serviceA{};
    ServiceB serviceB{};

    //~ We register our instance of `ServiceA` to handle `EventA`, and `ServiceB` to handle `EventB`:

    router.registerService<EventA>(serviceA);
    router.registerService<EventB>(serviceB);

    //~ When we push the events `A` and `B` to the router, they are distributed to the registered services:

    assert(router.process(EventA{}) == essm::ProcessingStatus::Success);
    assert(router.process(EventB{}) == essm::ProcessingStatus::Success);

    //~ This is reflected in the log:
    //~
    //~ ```
    //~ DBG/ESSMrouter/Router.hpp#49 Received event EventA (0x9cfc03fc)
    //~ DBG/ESSMservice/EventService.hpp#20 Received event EventA (0x9cfc03fc)
    //~ INF/Application/main.cpp#32 Received event A in service A
    //~ DBG/ESSMrouter/Router.hpp#49 Received event EventB (0x5f55246)
    //~ DBG/ESSMservice/EventService.hpp#20 Received event EventB (0x5f55246)
    //~ INF/Application/main.cpp#47 Received event B in service B
    //~ ```
    //~
    //~ `EventC`, however, has no registered service to handle it, and its processing fails:

    assert(router.process(EventC{}) == essm::ProcessingStatus::Failure);

    //~ ```
    //~ DBG/ESSMrouter/Router.hpp#49 Received event EventC (0x72f262d0)
    //~ ERR/ESSMrouter/Router.hpp#56 Routing failed: no service registered for EventC (0x72f262d0)
    //~ ```
    //~
    //~ If we register `ServiceA` as a handler for `EventD`, the router will send events of this type to this
    //~ service, but the processing fails, as `ServiceA` has no handler for this event type:

    router.registerService<EventD>(serviceA);
    assert(router.process(EventD{}) == essm::ProcessingStatus::Failure);

    //~ ```
    //~ DBG/ESSMrouter/Router.hpp#49 Received event EventD (0xec96f773)
    //~ DBG/ESSMservice/EventService.hpp#20 Received event EventD (0xec96f773)
    //~ ERR/ESSMservice/EventService.hpp#28 Service does not offer a handler for event EventD (0xec96f773)
    //~ ```

    return 0;
}
