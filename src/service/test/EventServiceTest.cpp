#include <essm/service/EventService.hpp>

#include <gmock/gmock.h>

TEST(EventServiceTest, shouldExecuteUnitTest)
{
    essm::EventService es;
    EXPECT_EQ(es.handle(0), essm::ProcessingStatus::Failure);
}
