#include "gtest/gtest.h"

#include "entity.h"

#include <memory>

class Entity_test : public ::testing::Test
{
  protected:
};

TEST_F(Entity_test, smoke)
{
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  ASSERT_TRUE(ent);
}

TEST_F(Entity_test, name_empty)
{
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  ASSERT_GT(ent->name().size(), sizeof("Entity_") - 1) << ent->name();
  ASSERT_EQ(ent->name().substr(0, sizeof("Entity_") - 1).compare("Entity_"), 0) << ent->name();
}

TEST_F(Entity_test, name_set)
{
  std::shared_ptr<Entity> ent = std::make_shared<Entity>("SomeName");
  ASSERT_EQ(ent->name(), "SomeName");
}
