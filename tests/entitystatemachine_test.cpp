#include "gtest/gtest.h"

#include "entitystatemachine.h"

#include "entity.h"

struct Position
{
};

TEST(State_test, smoke)
{
  EntityStateMachine esm(std::make_shared<Entity>());
}

TEST(State_test, add_state)
{
  EntityStateMachine esm(std::make_shared<Entity>());
  ASSERT_NO_THROW(esm.createState(1));
  ASSERT_ANY_THROW(esm.createState(1));
  ASSERT_TRUE(esm.createState(2));
}

TEST(State_test, change_state)
{
  std::shared_ptr<Entity> entity = std::make_shared<Entity>();
  EntityStateMachine esm(entity);
  std::shared_ptr<Entity> state1 = esm.createState(1);
  std::shared_ptr<Position> position = std::make_shared<Position>();
  state1->add(position);

  ASSERT_NO_THROW(esm.changeState(1));
  ASSERT_NO_THROW(entity->get<Position>());
  ASSERT_EQ(entity->get<Position>(), position);
}

TEST(State_test, change_state_wrong)
{
  EntityStateMachine esm(std::make_shared<Entity>());
  esm.createState(1);
  ASSERT_NO_THROW(esm.changeState(1));
  ASSERT_ANY_THROW(esm.changeState(2));
}
