# Example 1: A simple service

This is just a very minimal service that can handle two types of events.
One of the messages causes the accumulator to increase by a given amount,
while the other reports the currently stored value.

## Implementation

```c++

#include <cassert>

```

The type `EventService` is the basic service which is capable of just
handling incoming events.

```c++

#include <essm/service/EventService.hpp>

```

While any type can act as an event, as long as it has the required traits,
there are macros to generate those traits automatically.

```c++

#include <essm/events/Event.hpp>

```

We'll also make use of the included logger interface. It can be configured
in various ways, but the default configuration should be enough to begin with.

```c++

#include <essm/logger/Logger.hpp>

```

First of all, we need to define our events. Those can be, in fact, almost
anything, as long as the proper event traits are defined. The most important
event trait is its identifier, which has to be unique. The macro `essm_event`
can be used to simplify the generation as follows:

```c++

essm_event(Increment)
{
    int amount;
};

essm_event(Report)
{};

```

Let us also define an event which will not be supported by the service
to demonstrate that the program can handle this gracefully.

```c++

essm_event(Invalid)
{};

```

It is now time to define our service. It implements the previously included
`EventService`:

```c++

class AccumulateService : public essm::EventService
{
    using ProcessingStatus = essm::ProcessingStatus;

public:

```

In the constructor, we call the base class, which takes care of message
routing, and ask it to register the handlers for events which we want to
support:

```c++

    AccumulateService()
    {
        registerHandler(&AccumulateService::handleIncrement);
        registerHandler(&AccumulateService::handleReport);
    }

```

The router then takes care of passing the events to the proper handler
method, based on the event type.

If one would like (for example, to increase readability) to make the event

```c++
    // ~type more verbose, the template parameter for event type can be passed,
```

like `registerHandler<Increment>(&AccumulateService::handleIncrement)`.
However, as the handler method name makes it quite obvious, it can be
skipped.

Next, we want to implement the handlers. They just receive the event
(as a const reference, as we aren't supposed to modify them) and take
some actions:

```c++

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

```

The handlers have to return a `ProcessingStatus`. As there isn't much
potential for failure in our service, we just return the `Success` value
every time.

The last thing to do in our service is to declare the private counter:

```c++

private:

    int amount{0};

};

```

Our service is done. Now, let's write a simple `main` function for our program.

```c++

int main()
{
```

We'll just create the service. No magic needed here for such a simple
use case:

```c++

    auto service = AccumulateService{};

```

Now it is time to create and send some events and send them to our service.
We'll use the `handle` method, supplied by the `EventService`:

```c++

    service.handle(Increment{2});
    service.handle(Report{});

```

The handler functions, of course, inform us about the processing result.
Our handlers, of course, return a success value:

```c++

    assert(service.handle(Increment{3}) == essm::ProcessingStatus::Success);

```

We can try to pass an event which has not been registered, like the
type `Invalid`. This, of course, results in a processing failure:

```c++

    assert(service.handle(Invalid{}) == essm::ProcessingStatus::Failure);

```

Processing failure does not make our service unusable. As soon as we
provide it with another valid event, it happily processes it for us:

```c++

    service.handle(Report{});

    return 0;
}

```

## Results

This simple program just writes a simple output when the `Report` event is
processed and an error message from `EventService`, when it cannot find
a handler for some event:

```
Current value: 2
Service does not offer a handler for message #3: Invalid
Current value: 5
```
