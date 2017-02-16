#include "engine.h"
#include "system.h"
#include "entity.h"

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
    void handleEntity(const double &/*time*/, std::shared_ptr<Entity> &entity) override
    {
       entity->get<Render>()->get();
       entity->get<Position>()->get();
    }
};

TEST_F(System_test, smoke)
{
  std::shared_ptr<SystemBase> system = std::make_shared<SystemBase>();
  ASSERT_TRUE(system);
}

TEST_F(System_test, type_index_check)
{
  std::shared_ptr<Render> render = std::make_shared<Render>();
  std::shared_ptr<Position> position = std::make_shared<Position>();

  std::shared_ptr<SystemBase> system = std::make_shared<SystemRender>();
  std::shared_ptr<Engine> engine = std::make_shared<Engine>();
  std::shared_ptr<Entity> entity = std::make_shared<Entity>();
  entity->add(render)
      ->add(position);

  EXPECT_CALL(*render, get()).Times(1);
  EXPECT_CALL(*position, get()).Times(1);

  engine->addEntity(entity);
  engine->addSystem(0, system);

  engine->update(1.0);

  engine->removeAllSystems();
}
