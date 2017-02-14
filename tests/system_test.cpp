#include "engine.h"
#include "system.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class System_test : public ::testing::Test
{
  public:

};

struct Render
{
    MOCK_METHOD0(get, int());
};

struct Position
{
    MOCK_METHOD0(get, int());
};

struct SystemRender : public System<Render, Position>
{
    void update(const double &time)
    {
      //Get all entity
      //Handle entityes
    }
};

TEST_F(System_test, smoke)
{
  std::shared_ptr<SystemBase> system = std::make_shared<SystemBase>();
  ASSERT_TRUE(system);
}

TEST_F(System_test, type_index_check)
{
  Render render;
  Position pos;

  std::shared_ptr<SystemBase> system = std::make_shared<SystemRender>();
  std::shared_ptr<Engine> engine = std::make_shared<Engine>();

  engine->addSystem(0, system);

  engine->update(1.0);
}
