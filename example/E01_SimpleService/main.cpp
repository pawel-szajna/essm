#include <iostream>

#include <essm/service/MessageService.hpp>

essm_event(1, Increment)
{
    int amount;
};

essm_event(2, Report)
{};

essm_event(3, Invalid)
{};

class AccumulateService : public essm::MessageService<AccumulateService>
{
    using ProcessingStatus = essm::ProcessingStatus;

public:

    AccumulateService()
    {
        registerHandler(&AccumulateService::handleIncrement);
        registerHandler(&AccumulateService::handleReport);
    }

    ProcessingStatus handleIncrement(const Increment& increment)
    {
        amount += increment.amount;
        return ProcessingStatus::Success;
    }

    ProcessingStatus handleReport(const Report&)
    {
        std::cout << "Current value: " << amount << std::endl;
        return ProcessingStatus::Success;
    }

private:

    int amount{0};

};

int main()
{
    auto service = AccumulateService{};
    service.handle(Increment{2});
    service.handle(Report{});
    service.handle(Increment{3});
    service.handle(Report{});
    service.handle(Invalid{});
    return 0;
}
