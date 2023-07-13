//~ # Example 1: A simple service
//~
//~ This is just a very minimal service that can handle two types of events.
//~ One of the messages causes the accumulator to increase by a given amount,
//~ while the other reports the currently stored value.
//~
//~ ## Implementation

#include <cassert>
#include <iostream>

//~ The type `MessageService` is the basic service which is capable of just
//~ handling some messages.

#include <essm/service/MessageService.hpp>

//~ While any type can act as an event, as long as it has the required traits,
//~ there are macros to generate those traits automatically.

#include <essm/events/Event.hpp>

//~ We'll also make use of the included logger interface. It can be configured
//~ in various ways, but the default configuration should be enough to begin with.

#include <essm/logger/Logger.hpp>

//~ First of all, we need to define our events. Those can be, in fact, almost
//~ anything, as long as the proper event traits are defined. The most important
//~ event trait is its identifier, which has to be unique. The macro `essm_event`
//~ can be used to simplify the generation as follows:

essm_event(1, Increment)
{
    int amount;
};

essm_event(2, Report)
{};

//~ Let us also define an event which will not be supported by the service
//~ to demonstrate that the program can handle this gracefully.

essm_event(3, Invalid)
{};

//~ It is now time to define our service. It implements the previously included
//~ `MessageService`:

class AccumulateService : public essm::MessageService<AccumulateService>
{
    using ProcessingStatus = essm::ProcessingStatus;

public:

    //~ In the constructor, we call the base class, which takes care of message
    //~ routing, and ask it to register the handlers for events which we want to
    //~ support:

    AccumulateService()
    {
        registerHandler(&AccumulateService::handleIncrement);
        registerHandler(&AccumulateService::handleReport);
    }

    //~ The router then takes care of passing the events to the proper handler
    //~ method, based on the event type.
    //~
    //~ If one would like (for example, to increase readability) to make the event
    // ~type more verbose, the template parameter for event type can be passed,
    //~ like `registerHandler<Increment>(&AccumulateService::handleIncrement)`.
    //~ However, as the handler method name makes it quite obvious, it can be
    //~ skipped.
    //~
    //~ Next, we want to implement the handlers. They just receive the event
    //~ (as a const reference, as we aren't supposed to modify them) and take
    //~ some actions:

    ProcessingStatus handleIncrement(const Increment& increment)
    {
        amount += increment.amount;
        return ProcessingStatus::Success;
    }

    ProcessingStatus handleReport(const Report&)
    {
        essm_info("Current value: {}", amount);
        return ProcessingStatus::Success;
    }

    //~ The handlers have to return a `ProcessingStatus`. As there isn't much
    //~ potential for failure in our service, we just return the `Success` value
    //~ every time.
    //~
    //~ The last thing to do in our service is to declare the private counter:

private:

    int amount{0};

};

//~ Our service is done. Now, let's write a simple `main` function for our program.

int main()
{
    //~ We'll just create the service. No magic needed here for such a simple
    //~ use case:

    auto service = AccumulateService{};

    //~ Now it is time to create and send some events and send them to our service.
    //~ We'll use the `handle` method, supplied by the `MessageService`:

    service.handle(Increment{2});
    service.handle(Report{});

    //~ The handler functions, of course, inform us about the processing result.
    //~ Our handlers, of course, return a success value:

    assert(service.handle(Increment{3}) == essm::ProcessingStatus::Success);

    //~ We can try to pass an event which has not been registered, like the
    //~ type `Invalid`. This, of course, results in a processing failure:

    assert(service.handle(Invalid{}) == essm::ProcessingStatus::Failure);

    //~ Processing failure does not make our service unusable. As soon as we
    //~ provide it with another valid event, it happily processes it for us:

    service.handle(Report{});

    return 0;
}

//~ ## Results
//~
//~ This simple program just writes a simple output when the `Report` event is
//~ processed and an error message from `MessageService`, when it cannot find
//~ a handler for some event:
//~
//~ ```
//~ Current value: 2
//~ Service does not offer a handler for message #3: Invalid
//~ Current value: 5
//~ ```
