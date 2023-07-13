#pragma once

#include <essm/events/Event.hpp>
#include <essm/types/ProcessingStatus.hpp>

#include <functional>
#include <unordered_map>

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
        std::cerr << "Service does not offer a handler for message #" << EventTraits<MessageType>::eventId
                  << ": " << EventTraits<MessageType>::eventName << std::endl;
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
