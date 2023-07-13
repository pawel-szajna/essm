#include "Payment.hpp"

#include <essm/logger/Logger.hpp>

PaymentService::PaymentService(std::string owner,
                               std::string name,
                               int price,
                               int stock,
                               Bank& bank)
    : owner{std::move(owner)}
    , name{std::move(name)}
    , price{price}
    , stock{stock}
    , bank{bank}
{
    registerHandler(&PaymentService::handleOrder);
}

auto PaymentService::handleOrder(const Order& order) -> ProcessingStatus
{
    essm_info("{} ordered {} {}s", order.buyer, order.amount, name);

    if (stock <= 0)
    {
        essm_warn("{} is out of stock!", name);
        return ProcessingStatus::Failure;
    }

    int cost = price * order.amount;

    if (order.amount > stock)
    {
        essm_warn("Ordered {} but only have {} in stock", order.amount, stock);
        cost = price * stock;
    }

    if (bank.handle(Transaction{order.buyer, owner, cost}) == ProcessingStatus::Failure)
    {
        essm_warn("Bank transaction failed, sale aborted");
        return ProcessingStatus::Failure;
    }

    stock -= std::min(order.amount, stock);
    essm_debug("Current stock of {}: {}", name, stock);
    return ProcessingStatus::Success;
}
