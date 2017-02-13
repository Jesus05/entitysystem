#include "gtest/gtest.h"
#include "engine.h"

class Engine_test : public ::testing::Test
{
  protected:
    Engine m_eng;
};

TEST_F(Engine_test, smoke)
{
  ASSERT_TRUE(&m_eng);
}

TEST_F(Engine_test, add_entity)
{
  ASSERT_NO_THROW(m_eng.addEntity(std::make_shared<Entity>()));
  ASSERT_ANY_THROW(m_eng.addEntity(std::make_shared<Entity>()));
}

TEST_F(Engine_test, add_entity_null)
{
  ASSERT_ANY_THROW(m_eng.addEntity(std::shared_ptr<Entity>()));
}

TEST_F(Engine_test, remove_entity)
{
  std::shared_ptr<Entity> entity = std::make_shared<Entity>();

  ASSERT_NO_THROW(m_eng.addEntity(entity));
  ASSERT_NO_THROW(m_eng.removeEntity(entity));
}

//TEST_F(Engine_test, remove_entity_no_added)
//{
//  ASSERT_ANY_THROW(m_eng.removeEntity(std::make_shared<Entity>()));

//  std::shared_ptr<Entity> entity = std::make_shared<Entity>();

//  ASSERT_NO_THROW(m_eng.addEntity(entity));
//  ASSERT_ANY_THROW(m_eng.removeEntity(std::make_shared<Entity>()));
//}

//TEST_F(Engine_test, remove_entity_double_time)
//{
//  std::shared_ptr<Entity> entity = std::make_shared<Entity>();

//  ASSERT_NO_THROW(m_eng.addEntity(entity));
//  ASSERT_NO_THROW(m_eng.removeEntity(entity));
//  ASSERT_ANY_THROW(m_eng.removeEntity(entity));
//}

TEST_F(Engine_test, add_system)
{
  std::shared_ptr<System> system = std::make_shared<System>();
  ASSERT_NO_THROW(m_eng.addSystem(0, system));
}

TEST_F(Engine_test, add_system_duplicate)
{
  std::shared_ptr<System> system = std::make_shared<System>();
  ASSERT_NO_THROW(m_eng.addSystem(0, system));
  ASSERT_NO_THROW(m_eng.addSystem(0, system));
}

TEST_F(Engine_test, add_system_null)
{
  ASSERT_ANY_THROW(m_eng.addSystem(0, std::shared_ptr<System>()));
}

//TEST_F(Engine_test, remove_system_no_added)
//{
//  ASSERT_ANY_THROW(m_eng.removeSystem(std::make_shared<System>()));

//  std::shared_ptr<System> system = std::make_shared<System>();
//  ASSERT_NO_THROW(m_eng.addSystem(0, system));
//  ASSERT_ANY_THROW(m_eng.removeSystem(std::make_shared<System>()));
//}

//TEST_F(Engine_test, remove_system_double)
//{
//  std::shared_ptr<System> system = std::make_shared<System>();
//  ASSERT_NO_THROW(m_eng.addSystem(0, system));
//  ASSERT_NO_THROW(m_eng.removeSystem(system));
//  ASSERT_ANY_THROW(m_eng.removeSystem(system));
//}

TEST_F(Engine_test, remove_system_duplicated)
{
  std::shared_ptr<System> system = std::make_shared<System>();
  ASSERT_NO_THROW(m_eng.addSystem(0, system));
  ASSERT_NO_THROW(m_eng.addSystem(0, system));
  ASSERT_NO_THROW(m_eng.removeSystem(system));
}

TEST_F(Engine_test, remove_system)
{
  std::shared_ptr<System> system = std::make_shared<System>();

  ASSERT_NO_THROW(m_eng.addSystem(0, system));
  ASSERT_NO_THROW(m_eng.removeSystem(system));
}

TEST_F(Engine_test, update)
{
  m_eng.update(1.0);
}

