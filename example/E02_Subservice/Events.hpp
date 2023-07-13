#pragma once

#include <essm/events/Event.hpp>

#include <string>

essm_event(Transaction)
{
    std::string from;
    std::string to;
    int amount;
};

essm_event(Order)
{
    std::string buyer;
    int amount;
};
