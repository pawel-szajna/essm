//~ # Example 4: A state machine
//~
//~ In this example, we will create a very simple `Counter` state machine, which only has two states:
//~
//~ * _Initial state_: the state machine does nothing, only waits for the `Activate` signal.
//~ * _Counting state_: the state machine receives `Number` events and sums the values of all `amount` fields
//~   received during this counting cycle. The event `Report` finishes the cycle and triggers a log message
//~   with the counting result.

#include <essm/events/Event.hpp>
#include <essm/state_machine/StateMachine.hpp>

//~ We define our events as usual:

essm_event(Activate) {};
essm_event(Number) { int amount; };
essm_event(Report) {};

//~ Then create the state machine:

class Counter : public essm::StateMachine
{
    using Status = essm::ProcessingStatus;

public:

    Counter()
    {
        //~ In the constructor, we create the transition table, describing all the possible states and
        //~ events which trigger transitions between them, and optional actions.

        addTransition<Activate>(0, 1);
        addTransition<Number>  (1, 1, &Counter::count);
        addTransition<Report>  (1, 0, &Counter::report);

        //~ Note: while the transitions with actions provided could determine the event types based on the
        //~ action handler parameter type, it is suggested to provide it explicitly for increased readability
        //~ anyway.
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

    //~ The `StateMachine` is a special case of `EventService` and can handle messages just as the services
    //~ we created in previous examples:

    counter.handle(Activate{}); // We switch to the counting state
    counter.handle(Number{10});
    counter.handle(Number{15});
    counter.handle(Report{});   // We switch to the idling state

    //~ The difference is that when we are in the wrong state, the action handlers will not be invoked:

    counter.handle(Number{2});
    counter.handle(Report{});

    counter.handle(Activate{});
    counter.handle(Number{12});
    counter.handle(Activate{});
    counter.handle(Report{});

    //~ That's all!

    return 0;
}
