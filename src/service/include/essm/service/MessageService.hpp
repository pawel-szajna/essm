#pragma once

#include <essm/events/Event.hpp>
#include <essm/types/ProcessingStatus.hpp>

#include <functional>
#include <unordered_map>

#include <essm/logger/Logger.hpp>

namespace essm
{
template<typename ServiceImpl>
class MessageService
{
public:

    template<typename MessageType>
    ProcessingStatus handle(const MessageType& message)
    try
    {
        return handlers.at(EventTraits<MessageType>::eventId)((void*)(&message));
    }
    catch (std::out_of_range&)
    {
        essm_logger_error("ESSMservice",
                          "Service does not offer a handler for event {} ({:#x})",
                          EventTraits<MessageType>::eventName,
                          EventTraits<MessageType>::eventId);
        return ProcessingStatus::Failure;
    }

protected:

    template<typename MessageType>
    void registerHandler(ProcessingStatus(ServiceImpl::*handler)(const MessageType&))
    {
        handlers.emplace(
                EventTraits<MessageType>::eventId,
                [this, handler] (void* message)
                {
                    return (((ServiceImpl*)(this))->*handler)(*(MessageType*)(message));
                });
    }

private:

    std::unordered_map<unsigned int, std::function<ProcessingStatus(void*)>> handlers{};

};
}
