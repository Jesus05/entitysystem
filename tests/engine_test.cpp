#include "gtest/gtest.h"
#include "engine.h"
#include "entity.h"

#include "system_mock.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

class Engine_test : public ::testing::Test
{
  protected:
    virtual void SetUp()
    {
      m_eng = std::make_shared<Engine>();
    }
    virtual void TearDown()
    {
      m_eng->removeAllSystems();
      m_eng.reset();
    }

    std::shared_ptr<Engine> m_eng;
};

TEST_F(Engine_test, smoke)
{
  ASSERT_TRUE(m_eng);
}

TEST_F(Engine_test, add_entity)
{
  ASSERT_NO_THROW(m_eng->addEntity(std::make_shared<Entity>("Entity")));
  ASSERT_ANY_THROW(m_eng->addEntity(std::make_shared<Entity>("Entity")));
}

TEST_F(Engine_test, add_entity_null)
{
  ASSERT_ANY_THROW(m_eng->addEntity(std::shared_ptr<Entity>()));
}

TEST_F(Engine_test, remove_entity)
{
  std::shared_ptr<Entity> entity = std::make_shared<Entity>();

  ASSERT_NO_THROW(m_eng->addEntity(entity));
  ASSERT_NO_THROW(m_eng->removeEntity(entity));
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
  std::shared_ptr<SystemBase> system = std::make_shared<SystemBase>();
  ASSERT_NO_THROW(m_eng->addSystem(0, system));
}

TEST_F(Engine_test, add_system_duplicate)
{
  std::shared_ptr<SystemBase> system = std::make_shared<SystemBase>();
  ASSERT_NO_THROW(m_eng->addSystem(0, system));
  ASSERT_NO_THROW(m_eng->addSystem(0, system));
}

TEST_F(Engine_test, add_system_null)
{
  ASSERT_ANY_THROW(m_eng->addSystem(0, std::shared_ptr<SystemBase>()));
}

TEST_F(Engine_test, remove_all_systems)
{
  std::shared_ptr<SystemBase> system = std::make_shared<SystemBase>();
  ASSERT_EQ(system.use_count(), 1);
  m_eng->addSystem(0, system);
  ASSERT_EQ(system.use_count(), 2);
  m_eng->addSystem(0, system);
  ASSERT_EQ(system.use_count(), 3);
  m_eng->removeAllSystems();
  ASSERT_EQ(system.use_count(), 1);
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
  std::shared_ptr<SystemBase> system = std::make_shared<SystemBase>();
  ASSERT_NO_THROW(m_eng->addSystem(0, system));
  ASSERT_NO_THROW(m_eng->addSystem(0, system));
  ASSERT_NO_THROW(m_eng->removeSystem(system));
}

TEST_F(Engine_test, remove_system)
{
  std::shared_ptr<SystemBase> system = std::make_shared<SystemBase>();

  ASSERT_NO_THROW(m_eng->addSystem(0, system));
  ASSERT_NO_THROW(m_eng->removeSystem(system));
}

TEST_F(Engine_test, update)
{
  m_eng->update(1.0);
}

TEST_F(Engine_test, update_one)
{
  std::shared_ptr<System_mock> mock = std::make_shared<System_mock>();
  std::shared_ptr<SystemBase> system_shared(mock);
  EXPECT_CALL(*mock, preUpdate(0.0, _)).Times(1);
  EXPECT_CALL(*mock, postUpdate(0.0, _)).Times(1);

  m_eng->addSystem(0, system_shared);
  m_eng->update(0);
}

TEST_F (Engine_test, update_2_system)
{
  System_mock *system = new System_mock();
  System_mock *system2 = new System_mock();

  std::shared_ptr<SystemBase> system_shared(system);
  std::shared_ptr<SystemBase> system_shared2(system2);

  EXPECT_CALL(*system, preUpdate(_, _)).Times(1);
  EXPECT_CALL(*system2, preUpdate(_, _)).Times(1);

  m_eng->addSystem(0, system_shared);
  m_eng->addSystem(0, system_shared2);

  m_eng->update(1.0);
}

TEST_F(Engine_test, update_priority)
{
  System_mock *system = new System_mock();
  System_mock *system2 = new System_mock();

  std::shared_ptr<SystemBase> system_shared(system);
  std::shared_ptr<SystemBase> system_shared2(system2);

  {
    ::testing::InSequence dummy;

    EXPECT_CALL(*system, preUpdate(_, _)).Times(1);
    EXPECT_CALL(*system2, preUpdate(_, _)).Times(1);
  }

  m_eng->addSystem(0, system_shared);
  m_eng->addSystem(1, system_shared2);

  m_eng->update(2.0);
}

TEST_F(Engine_test, update_double_system)
{
  System_mock *system = new System_mock();

  std::shared_ptr<SystemBase> system_shared(system);

  EXPECT_CALL(*system, preUpdate(_, _)).Times(2);

  m_eng->addSystem(0, system_shared);
  m_eng->addSystem(0, system_shared);

  m_eng->update(3.0);
}

TEST_F(Engine_test, setParent)
{
  System_mock *system = new System_mock();
  std::shared_ptr<SystemBase> system_shared(system);

  m_eng->addSystem(0, system_shared);

  ASSERT_TRUE(system->checkEngine(m_eng));
}

TEST_F(Engine_test, check_is_update)
{
  std::shared_ptr<System_mock> mock = std::make_shared<System_mock>();

  ASSERT_FALSE(m_eng->isUpdating());

  auto tt = [&]() { ASSERT_TRUE(m_eng->isUpdating()); };

  EXPECT_CALL(*mock, preUpdate(_, _));

  ON_CALL(*mock, preUpdate(_, _)).WillByDefault(InvokeWithoutArgs(tt));

  m_eng->addSystem(0, mock);

  m_eng->update(0.0);
}

TEST_F(Engine_test, add_system_in_update)
{
  std::shared_ptr<System_mock> mock = std::make_shared<System_mock>();
  std::shared_ptr<System_mock> mock2 = std::make_shared<System_mock>();
  std::shared_ptr<System_mock> mock3 = std::make_shared<System_mock>();
  std::shared_ptr<System_mock> mock4 = std::make_shared<System_mock>();

  m_eng->addSystem(1, mock);
  m_eng->addSystem(4, mock4);

  auto tt = [&]() { m_eng->addSystem(3, mock3); };
  auto tt4 = [&]() { m_eng->addSystem(2, mock2); };

  EXPECT_CALL(*mock, preUpdate(_, _)).Times(1);
  EXPECT_CALL(*mock2, preUpdate(_, _)).Times(0);
  EXPECT_CALL(*mock3, preUpdate(_, _)).Times(1);
  EXPECT_CALL(*mock4, preUpdate(_, _)).Times(1);

  ON_CALL(*mock, preUpdate(_, _)).WillByDefault(InvokeWithoutArgs(tt));
  ON_CALL(*mock4, preUpdate(_, _)).WillByDefault(InvokeWithoutArgs(tt4));

  m_eng->update(0.0);
}

TEST_F(Engine_test, remove_system_in_update)
{
  std::shared_ptr<System_mock> mock = std::make_shared<System_mock>();
  std::shared_ptr<System_mock> mock2 = std::make_shared<System_mock>();
  std::shared_ptr<System_mock> mock3 = std::make_shared<System_mock>();

  m_eng->addSystem(1, mock);
  m_eng->addSystem(2, mock2);
  m_eng->addSystem(3, mock3);

  auto tt = [&]() { m_eng->removeSystem(mock2); m_eng->removeSystem(mock3); };

  EXPECT_CALL(*mock, preUpdate(_, _)).Times(2);
  EXPECT_CALL(*mock2, preUpdate(_, _)).Times(1);
  EXPECT_CALL(*mock3, preUpdate(_, _)).Times(1);
  ON_CALL(*mock, preUpdate(_, _)).WillByDefault(InvokeWithoutArgs(tt));

  m_eng->update(0.0);
  m_eng->update(0.0); //Ожидаеться что 2 системы не удасться удалить (вывод в cerr)
}

TEST_F(Engine_test, remove_all_system_in_update)
{
  std::shared_ptr<System_mock> mock = std::make_shared<System_mock>();
  std::shared_ptr<System_mock> mock2 = std::make_shared<System_mock>();
  std::shared_ptr<System_mock> mock3 = std::make_shared<System_mock>();

  m_eng->addSystem(1, mock);
  m_eng->addSystem(2, mock2);
  m_eng->addSystem(3, mock3);

  auto tt = [&]() { m_eng->removeAllSystems(); };

  EXPECT_CALL(*mock, preUpdate(_, _)).Times(1);
  EXPECT_CALL(*mock2, preUpdate(_, _)).Times(1);
  EXPECT_CALL(*mock3, preUpdate(_, _)).Times(1);
  ON_CALL(*mock, preUpdate(_, _)).WillByDefault(InvokeWithoutArgs(tt));

  m_eng->update(0.0);
  m_eng->update(0.0);
}
