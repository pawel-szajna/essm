#pragma once

#include "../Events.hpp"

#include <essm/service/MessageService.hpp>

#include <string>

class BankingService;

class PaymentService : public essm::MessageService<PaymentService>
{
    using Bank = essm::MessageService<BankingService>;
    using ProcessingStatus = essm::ProcessingStatus;

public:

    PaymentService(std::string owner,
                   std::string name,
                   int price,
                   int stock,
                   Bank& bank);

    ProcessingStatus handleOrder(const Order& order);

private:

    std::string owner;
    std::string name;
    int price;
    int stock;
    Bank& bank;
};
