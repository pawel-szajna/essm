#include "Bank.hpp"

#include <essm/logger/Logger.hpp>

BankingService::BankingService()
{
    registerHandler(&BankingService::handleTransaction);
}

auto BankingService::handleTransaction(const Transaction& transaction) -> ProcessingStatus
{
    essm_info("Attempting to transfer ${} from {} to {}",
              transaction.amount, transaction.from, transaction.to);

    if (not balances.contains(transaction.from))
    {
        essm_warn("Transaction failed: unknown sender {}", transaction.from);
        return ProcessingStatus::Failure;
    }

    if (not balances.contains(transaction.to))
    {
        essm_warn("Transaction failed: unknown receiver {}", transaction.to);
        return ProcessingStatus::Failure;
    }

    auto& senderBalance = balances.at(transaction.from);
    if (senderBalance < transaction.amount)
    {
        essm_warn("Transaction failed: {} has only ${}, cannot afford ${} transaction",
                  transaction.from, senderBalance, transaction.amount);
        return ProcessingStatus::Failure;
    }

    auto& receiverBalance = balances.at(transaction.to);

    senderBalance -= transaction.amount;
    receiverBalance += transaction.amount;

    essm_debug("After transaction: {}'s balance: ${}, {}'s balance: ${}",
               transaction.from, senderBalance, transaction.to, receiverBalance);

    return ProcessingStatus::Success;
}

int BankingService::getBalance(const std::string& client) const
{
    return balances.contains(client) ? balances.at(client) : 0;
}

void BankingService::addBalance(const std::string& client, int amount)
{
    balances[client] += amount;
}
