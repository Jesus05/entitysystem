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

TEST_F(Entity_test, component_exist)
{
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  std::shared_ptr<Entity> ent2 = std::make_shared<Entity>();
  std::shared_ptr<Place> place = std::make_shared<Place>();
  std::shared_ptr<Draw> draw = std::make_shared<Draw>();
  std::vector<long long> empty;
  std::vector<long long> onlyPlace = {TypeIndexer::index(typeid(std::shared_ptr<Place>))};
  std::vector<long long> onlyDraw = {TypeIndexer::index(typeid(std::shared_ptr<Draw>))};
  std::vector<long long> both1 = {TypeIndexer::index(typeid(std::shared_ptr<Place>)), TypeIndexer::index(typeid(std::shared_ptr<Draw>))};
  std::vector<long long> both2 = {TypeIndexer::index(typeid(std::shared_ptr<Draw>)), TypeIndexer::index(typeid(std::shared_ptr<Place>))};

  ASSERT_FALSE(ent->exist(empty));
  ASSERT_FALSE(ent->exist(onlyPlace));
  ASSERT_FALSE(ent->exist(onlyDraw));
  ASSERT_FALSE(ent->exist(both1));
  ASSERT_FALSE(ent->exist(both2));
  ent->add(place);
  ASSERT_TRUE(ent->exist(empty));
  ASSERT_TRUE(ent->exist(onlyPlace));
  ASSERT_FALSE(ent->exist(onlyDraw));
  ASSERT_FALSE(ent->exist(both1));
  ASSERT_FALSE(ent->exist(both2));
  ent2->add(draw);
  ASSERT_TRUE(ent2->exist(empty));
  ASSERT_FALSE(ent2->exist(onlyPlace));
  ASSERT_TRUE(ent2->exist(onlyDraw));
  ASSERT_FALSE(ent2->exist(both1));
  ASSERT_FALSE(ent2->exist(both2));
  ent->add(draw);
  ASSERT_TRUE(ent->exist(empty));
  ASSERT_TRUE(ent->exist(onlyPlace));
  ASSERT_TRUE(ent->exist(onlyDraw));
  ASSERT_TRUE(ent->exist(both1));
  ASSERT_TRUE(ent->exist(both2));
}

TEST_F(Entity_test, component_remove)
{
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  std::shared_ptr<Place> place = std::make_shared<Place>();
  std::shared_ptr<Draw> draw = std::make_shared<Draw>();
  std::vector<long long> empty;
  std::vector<long long> onlyPlace = {TypeIndexer::index(typeid(std::shared_ptr<Place>))};
  std::vector<long long> onlyDraw = {TypeIndexer::index(typeid(std::shared_ptr<Draw>))};
  std::vector<long long> both1 = {TypeIndexer::index(typeid(std::shared_ptr<Place>)), TypeIndexer::index(typeid(std::shared_ptr<Draw>))};
  std::vector<long long> both2 = {TypeIndexer::index(typeid(std::shared_ptr<Draw>)), TypeIndexer::index(typeid(std::shared_ptr<Place>))};

  ent->add(place)->add(draw);
  ASSERT_TRUE(ent->exist(empty));
  ASSERT_TRUE(ent->exist(onlyPlace));
  ASSERT_TRUE(ent->exist(onlyDraw));
  ASSERT_TRUE(ent->exist(both1));
  ASSERT_TRUE(ent->exist(both2));
  ASSERT_NO_THROW(ent->remove<Place>());
  ASSERT_TRUE(ent->exist(empty));
  ASSERT_FALSE(ent->exist(onlyPlace));
  ASSERT_TRUE(ent->exist(onlyDraw));
  ASSERT_FALSE(ent->exist(both1));
  ASSERT_FALSE(ent->exist(both2));
  ASSERT_ANY_THROW(ent->remove<Place>());
  ASSERT_TRUE(ent->exist(empty));
  ASSERT_FALSE(ent->exist(onlyPlace));
  ASSERT_TRUE(ent->exist(onlyDraw));
  ASSERT_FALSE(ent->exist(both1));
  ASSERT_FALSE(ent->exist(both2));
  ent->remove<Draw>();
  ASSERT_FALSE(ent->exist(empty));
  ASSERT_FALSE(ent->exist(onlyPlace));
  ASSERT_FALSE(ent->exist(onlyDraw));
  ASSERT_FALSE(ent->exist(both1));
  ASSERT_FALSE(ent->exist(both2));
}

TEST_F(Entity_test, component_exist2)
{
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  std::shared_ptr<Place> place = std::make_shared<Place>();
  std::shared_ptr<Draw> draw = std::make_shared<Draw>();

  ASSERT_FALSE(ent->exist<Place>());
  ASSERT_FALSE(ent->exist<Draw>());
  ent->add(place);
  ASSERT_TRUE(ent->exist<Place>());
  ASSERT_FALSE(ent->exist<Draw>());
  ent->add(draw);
  ASSERT_TRUE(ent->exist<Place>());
  ASSERT_TRUE(ent->exist<Draw>());
}

TEST_F(Entity_test, component_usafeGet)
{
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  std::shared_ptr<Place> place = std::make_shared<Place>();
  std::shared_ptr<Draw> draw = std::make_shared<Draw>();

  ASSERT_FALSE(ent->unsafeGet<Place>());
  ASSERT_FALSE(ent->unsafeGet<Draw>());
  ent->add(place);
  ASSERT_EQ(ent->unsafeGet<Place>(), place);
  ent->add(draw);
  ASSERT_EQ(ent->unsafeGet<Draw>(), draw);
}

TEST_F(Entity_test, add_and_update)
{
  std::shared_ptr<Entity> ent = std::make_shared<Entity>();
  std::shared_ptr<Entity> ent2 = std::make_shared<Entity>();
  std::shared_ptr<Place> place = std::make_shared<Place>();
  std::shared_ptr<Place> place2 = std::make_shared<Place>();
  std::shared_ptr<Draw> draw2 = std::make_shared<Draw>();

  ent->add(place);
  ent2->add(place2)->add(draw2);

  ent->addAndUpdate(ent2);
  ASSERT_TRUE(ent->exist<Draw>());
  ASSERT_EQ(ent->get<Place>(), place2);
}
