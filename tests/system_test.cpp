#include "engine.h"

#include "gtest/gtest.h"

#include <memory>

class System_test : public ::testing::Test
{
  public:

};

TEST_F(System_test, smoke)
{
  std::shared_ptr<System> system = std::make_shared<System>();
  ASSERT_TRUE(system);
}

