# Example 4: A state machine

In this example, we will create a very simple `Counter` state machine, which only has two states:

* _Initial state_: the state machine does nothing, only waits for the `Activate` signal.
* _Counting state_: the state machine receives `Number` events and sums the values of all `amount` fields
  received during this counting cycle. The event `Report` finishes the cycle and triggers a log message
  with the counting result.

```c++

#include <cassert>

#include <essm/events/Event.hpp>
#include <essm/state_machine/StateMachine.hpp>
#include <essm/state_machine/State.hpp>

```

We define our events as usual:

```c++

essm_event(Activate) {};
essm_event(Number) { int amount; };
essm_event(Report) {};

```

Then create the state machine:

```c++

essm_state(Idle);
essm_state(Counting);

class Counter : public essm::StateMachine
{
    using Status = essm::ProcessingStatus;

public:

```

We pass the initial state to the `StateMachine`'s construction:

```c++

    Counter() : StateMachine(Idle{})
    {
```

In the constructor, we create the transition table, describing all the possible states and
events which trigger transitions between them, and optional actions.

```c++

        addTransition<Activate, Idle,     Counting>();
        addTransition<Number,   Counting, Counting>(&Counter::count);
        addTransition<Report,   Counting, Idle    >(&Counter::report);

```

Note: while the transitions with actions provided could determine the event types based on the
action handler parameter type, it is suggested to provide it explicitly for increased readability
anyway.

```c++
    }

    Status count(const Number& event)
    {
        counter += event.amount;
        return Status::Success;
    }

    Status report(const Report&)
    {
        essm_info("Result: {}", counter);
        counter = 0;
        return Status::Success;
    }

private:

    int counter{};
};

int main()
{
    Counter counter{};

```

The `StateMachine` is a special case of `EventService` and can handle messages just as the services
we created in previous examples:

```c++

    counter.handle(Activate{}); // We switch to the counting state
    counter.handle(Number{10});
    counter.handle(Number{15});
    counter.handle(Report{});   // We switch to the idling state

```

The difference is that when we are in the wrong state, the action handlers will not be invoked:

```c++

    assert(counter.handle(Number{2}) == essm::ProcessingStatus::Failure);
    assert(counter.handle(Report{}) == essm::ProcessingStatus::Failure);

    assert(counter.handle(Activate{}) == essm::ProcessingStatus::Success);
    assert(counter.handle(Number{12}) == essm::ProcessingStatus::Success);
    assert(counter.handle(Activate{}) == essm::ProcessingStatus::Failure);
    assert(counter.handle(Report{}) == essm::ProcessingStatus::Success);

```

That's all!

```c++

    return 0;
}
```

