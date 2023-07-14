#pragma once

#include <essm/types/ProcessingStatus.hpp>
#include <essm/types/Traits.hpp>
#include <essm/logger/Logger.hpp>
#include <essm/service/EventService.hpp>

#include <optional>
#include <vector>

namespace essm
{
class StateMachine : public EventService
{
    struct Transition
    {
        using Action = std::optional<std::function<ProcessingStatus(void*)>>;

        types::StateId state{};
        types::EventId event{};
        types::StateId target{};
        Action action{};
    };

protected:

    template<typename Event>
    void addTransition(types::StateId state, types::StateId target)
    {
        addTransition<Event>(state, target, std::nullopt);
    }

    template<typename Event, typename ServiceImpl>
    void addTransition(types::StateId state,
                       types::StateId target,
                       ProcessingStatus(ServiceImpl::*handler)(const Event&))
    {
        addTransition<Event>(state, target,
                             Transition::Action{[this, handler](void* event) {
                                 return (((ServiceImpl*)(this))->*handler)(*(Event*)(event));
                             }});
    }

private:

    template<typename Event>
    void addTransition(types::StateId state, types::StateId target, Transition::Action action)
    {
        __essm_logger_debug("ESSMfsm", "Registering transition {} -> {} on {}", state, target, EventTraits<Event>::name);
        registerHandler<StateMachine, Event>(&StateMachine::forward);
        transitions.emplace_back(Transition{state, EventTraits<Event>::id, target, std::move(action)});
    }

    template<typename Event>
    ProcessingStatus forward(const Event& event)
    {
        auto transition = std::find_if(transitions.begin(),
                                       transitions.end(),
                                       [state = this->state](const Transition& t)
                                       {
                                           return t.state == state and t.event == EventTraits<Event>::id;
                                       });
        if (transition == transitions.end())
        {
            __essm_logger_warn("ESSMfsm",
                               "No support for event {} ({:#x}) in current state",
                               EventTraits<Event>::name,
                               EventTraits<Event>::id);
            return ProcessingStatus::Failure;
        }
        auto result = ProcessingStatus::Success;
        if (transition->action)
        {
            result = (*transition->action)((void*)(&event));
        }
        state = transition->target;
        __essm_logger_debug("ESSMfsm", "Processing finished, current state is {}", state);
        return result;
    }

    types::StateId state{};
    std::vector<Transition> transitions{};

};
}
