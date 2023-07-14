#pragma once

#include <essm/events/EventTraits.hpp>
#include <essm/logger/Logger.hpp>
#include <essm/types/ProcessingStatus.hpp>

#include <functional>
#include <unordered_map>

namespace essm
{
class EventService
{
public:

    template<typename MessageType>
    ProcessingStatus handle(const MessageType& message)
    try
    {
        __essm_logger_debug("ESSMservice",
                            "Received event {} ({:#x})",
                            EventTraits<MessageType>::name,
                            EventTraits<MessageType>::id);
        return handlers.at(EventTraits<MessageType>::id)((void*)(&message));
    }
    catch (std::out_of_range&)
    {
        __essm_logger_error("ESSMservice",
                            "Service does not offer a handler for event {} ({:#x})",
                            EventTraits<MessageType>::name,
                            EventTraits<MessageType>::id);
        return ProcessingStatus::Failure;
    }

protected:

    template<typename ServiceImpl, typename MessageType>
    void registerHandler(ProcessingStatus(ServiceImpl::*handler)(const MessageType&))
    {
        __essm_logger_debug("ESSMservice",
                            "Registered event handler for {} ({:#x})",
                            EventTraits<MessageType>::name,
                            EventTraits<MessageType>::id);
        handlers.emplace(
                EventTraits<MessageType>::id,
                [this, handler] (void* message)
                {
                    return (((ServiceImpl*)(this))->*handler)(*(MessageType*)(message));
                });
    }

private:

    std::unordered_map<unsigned int, std::function<ProcessingStatus(void*)>> handlers{};

};
}
