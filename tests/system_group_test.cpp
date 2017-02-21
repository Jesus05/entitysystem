#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "system.h"
#include "engine.h"
#include "entity.h"
#include "systemgroup.h"

struct Asteroid
{
    MOCK_METHOD0(checkMoc, void());
};

struct Position2
{
    MOCK_METHOD0(checkMoc, void());
};

struct Collision
{
    MOCK_METHOD0(checkMoc, void());
};

struct Bullet
{
    MOCK_METHOD0(checkMoc, void());
};

class SystemAsteroidCollision : public SystemSub<Asteroid, Position2, Collision>
{
};

class SystemBulletCollision : public SystemSub<Bullet, Position2, Collision>
{
};

class SystemSimpleCollision : public SystemSub<Position2, Collision>
{
};

class SystemCollisionGroup : public SystemGroup<SystemAsteroidCollision, SystemBulletCollision, SystemSimpleCollision>
{
    virtual void update(const double &/*time*/) override
    {
      std::shared_ptr<SystemBase> &asteroids = m_subsystems[0];
      std::shared_ptr<SystemBase> &bullets = m_subsystems[1];
      std::shared_ptr<SystemBase> &collisions = m_subsystems[2];

      for (std::shared_ptr<Entity> &one : asteroids->entityes())
      for (std::shared_ptr<Entity> &two : bullets->entityes())
      {
        one->get<Asteroid>()->checkMoc();
        one->get<Position2>()->checkMoc();
        one->get<Collision>()->checkMoc();
        two->get<Bullet>()->checkMoc();
        two->get<Position2>()->checkMoc();
        two->get<Collision>()->checkMoc();
      }
      for (std::shared_ptr<Entity> &collision : collisions->entityes())
      {
        collision->get<Collision>()->checkMoc();
      }
    }
};

TEST(System_group_test, smoke)
{
  SystemCollisionGroup group;
}

TEST(System_group_test, test)
{
  std::shared_ptr<Asteroid> asteroidC = std::make_shared<Asteroid>();
  std::shared_ptr<Position2> asteroidPosition = std::make_shared<Position2>();
  std::shared_ptr<Collision> asteroidCollision = std::make_shared<Collision>();
  std::shared_ptr<Bullet> bulletC = std::make_shared<Bullet>();
  std::shared_ptr<Position2> bulletPosition = std::make_shared<Position2>();
  std::shared_ptr<Collision> bulletCollision = std::make_shared<Collision>();
  std::shared_ptr<Entity> asteroid = std::make_shared<Entity>();
  std::shared_ptr<Entity> bullet = std::make_shared<Entity>();

  EXPECT_CALL(*asteroidC, checkMoc()).Times(1);
  EXPECT_CALL(*asteroidPosition, checkMoc()).Times(1);
  EXPECT_CALL(*asteroidCollision, checkMoc()).Times(2);
  EXPECT_CALL(*bulletC, checkMoc()).Times(1);
  EXPECT_CALL(*bulletPosition, checkMoc()).Times(1);
  EXPECT_CALL(*bulletCollision, checkMoc()).Times(2);

  asteroid->add(asteroidC)->add(asteroidPosition)->add(asteroidCollision);
  bullet->add(bulletC)->add(bulletCollision)->add(bulletPosition);

  std::shared_ptr<SystemCollisionGroup> collision = std::make_shared<SystemCollisionGroup>();
  std::shared_ptr<Engine> engine = std::make_shared<Engine>();

  engine->addEntity(asteroid);
  engine->addEntity(bullet);

  engine->addSystem(0, collision);

  engine->update(0.0);

  engine->removeAllSystems();
}
