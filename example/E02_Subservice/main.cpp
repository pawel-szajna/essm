#include <essm/logger/Logger.hpp>

#include "services/Bank.hpp"
#include "services/Payment.hpp"

void giveSomeMoney(IBank& bank)
{
    bank.addBalance("John", 1500);
    bank.addBalance("Mary", 2000);
    bank.addBalance("Tom", 300);
}

int main()
{
    essm_info("Creating services...");

    auto bank = std::make_unique<BankingService>();
    giveSomeMoney(*bank);

    bank->handle(Transaction{"John", "Tom", 100});

    auto beerStore = std::make_unique<PaymentService>("John", "beer", 25, 10, *bank);
    auto meatStore = std::make_unique<PaymentService>("Mary", "meat", 10, 50, *bank);
    auto carStore = std::make_unique<PaymentService>("Tom", "car", 2000, 2, *bank);

    beerStore->handle(Order{"Tom", 2});
    carStore->handle(Order{"John", 1});
    meatStore->handle(Order{"John", 5});
    meatStore->handle(Order{"Tom", 5});
    beerStore->handle(Order{"Mary", 30});
    beerStore->handle(Order{"Tom", 1});
}
