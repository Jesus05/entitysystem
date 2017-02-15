#include "gtest/gtest.h"

#include "entity.h"

#include <memory>

class Entity_test : public ::testing::Test
{
  protected:
};

struct Place
{
};

struct Draw
{
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

TEST_F(Entity_test, component_add)
{
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  std::shared_ptr<Place> place = std::make_shared<Place>();
  ASSERT_EQ(ent->add(place), ent);
}

TEST_F(Entity_test, component_get)
{
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  std::shared_ptr<Place> place = std::make_shared<Place>();
  ASSERT_ANY_THROW(ent->get<Place>());
  ent->add(place);
  ASSERT_ANY_THROW(ent->get<Draw>());
  std::shared_ptr<Place> place2 = ent->get<Place>();
  ASSERT_EQ(place, place2);
}

TEST_F(Entity_test, component_add_double)
{
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  std::shared_ptr<Place> place = std::make_shared<Place>();
  std::shared_ptr<Draw> draw = std::make_shared<Draw>();
  ASSERT_EQ(ent->add(place)->add(draw), ent);
}
