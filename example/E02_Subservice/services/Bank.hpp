#pragma once

#include "../Events.hpp"

#include <essm/service/MessageService.hpp>

#include <string>
#include <unordered_map>

class IBank
{
public:

    virtual void addBalance(const std::string& client, int amount) = 0;
    virtual int getBalance(const std::string& client) const = 0;
};

class BankingService : public essm::MessageService, public IBank
{
    using ProcessingStatus = essm::ProcessingStatus;

public:

    BankingService();

    ProcessingStatus handleTransaction(const Transaction& transaction);

    void addBalance(const std::string& client, int amount) override;
    int getBalance(const std::string& client) const override;

private:

    std::unordered_map<std::string, int> balances{};
};
