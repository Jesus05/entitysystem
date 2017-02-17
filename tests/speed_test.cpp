#include "engine.h"
#include "entity.h"
#include "system.h"

#include <random>
#include <chrono>

#include "debugmacros.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <thread>

int speed_test();

//TEST(SpeedTest, one)
//{
////  std::this_thread::sleep_for(std::chrono::seconds(1));
////  speed_test();
//};

struct Draw
{
};

struct Place
{
    double x;
    double y;
    double z;
};

struct Velocity
{
    double x;
    double y;
    double z;
};

struct Accelerator
{
    double x;
    double y;
    double z;
};

struct SaveSystem : public System<>
{
    void handleEntity(const double &/*time*/, std::shared_ptr<Entity> &entity)
    {
      std::shared_ptr<Draw> draw = entity->exist<Draw>() ? entity->get<Draw>() : std::shared_ptr<Draw>();
      std::shared_ptr<Place> place = entity->exist<Place>() ? entity->get<Place>() : std::shared_ptr<Place>();
      std::shared_ptr<Velocity> velocity = entity->exist<Velocity>() ? entity->get<Velocity>() : std::shared_ptr<Velocity>();
      std::shared_ptr<Accelerator> accelerator = entity->exist<Accelerator>() ? entity->get<Accelerator>() : std::shared_ptr<Accelerator>();
      if (draw) {}
      if (place) {}
      if (velocity) {}
      if (accelerator) {}
    }
};

struct DrawSystem : public System<Draw, Place>
{
    void handleEntity(const double &/*time*/, std::shared_ptr<Entity> &entity)
    {
      std::shared_ptr<Draw> draw = entity->get<Draw>();
      std::shared_ptr<Place> place = entity->get<Place>();
    }
};

struct MoveSystem : public System<Place, Velocity>
{
    void handleEntity(const double &time, std::shared_ptr<Entity> &entity)
    {
      std::shared_ptr<Place> place = entity->get<Place>();
      std::shared_ptr<Velocity> velocity = entity->get<Velocity>();
      place->x += velocity->x * time;
      place->y += velocity->y * time;
      place->z += velocity->z * time;
      if (velocity->x == 0 && velocity->y == 0 && velocity->z == 0) entity->remove<Velocity>();
    }
};

struct AcceleratorSystem : public System<Velocity, Accelerator>
{
    void handleEntity(const double &time, std::shared_ptr<Entity> &entity)
    {
      std::shared_ptr<Velocity> velocity = entity->get<Velocity>();
      std::shared_ptr<Accelerator> accelerator = entity->get<Accelerator>();
      velocity->x += accelerator->x * time;
      velocity->y += accelerator->y * time;
      velocity->z += accelerator->z * time;
      if (accelerator->x == 0 && accelerator->y == 0 && accelerator->z == 0) entity->remove<Accelerator>();
    }
};

struct WinGameSystem : public System<Place>
{
    bool win;
    std::shared_ptr<Entity> winner;

    WinGameSystem() : win(false) {}

    void handleEntity(const double &/*time*/, std::shared_ptr<Entity> &entity)
    {
      std::shared_ptr<Place> place = entity->get<Place>();
      if (!place) throw std::invalid_argument("No place!");
      const long long quadSumm = place->x * place->x + place->y * place->y + place->z * place->z;
      static const long long quadMin = 20ll * 20ll;
      if (quadSumm > quadMin)
      {
        win = true;
        static long long max = 0;
        if (max < quadSumm)
        {
          max = quadSumm;
          winner = entity;
        }
      }
    }
};

struct IterationCounterSystem : public System<>
{
    long long mainIteration;
    long long iterationsForEntity;

    IterationCounterSystem() : mainIteration(0), iterationsForEntity(0) { }

    void preUpdate(const double &, std::vector<std::shared_ptr<Entity> > &) override
    {
      mainIteration++;
    }

    void handleEntity(const double &, std::shared_ptr<Entity> &) override
    {
      iterationsForEntity++;
    }
};

struct EmptyDrawSystem : public System<Draw>
{
};

struct EmptyPlaceSystem : public System<Place>
{
};

struct EmptyAllSystem : public System<Draw, Place, Accelerator, Velocity>
{
};

struct EmptyEmptySystem : public System<>
{
};

int speed_test()
{
  std::shared_ptr<Engine> engine = std::make_shared<Engine>();
  std::shared_ptr<WinGameSystem> winGame = std::make_shared<WinGameSystem>();
  std::shared_ptr<IterationCounterSystem> iterations = std::make_shared<IterationCounterSystem>();

  engine->addSystem(0, std::make_shared<DrawSystem>());
  engine->addSystem(1, winGame);
  engine->addSystem(2, std::make_shared<SaveSystem>());
  engine->addSystem(3, std::make_shared<MoveSystem>());
  engine->addSystem(4, std::make_shared<AcceleratorSystem>());
  engine->addSystem(5, iterations);

  for (int i = 0; i < 32; i++)
  {
    if (i % 2) engine->addSystem(5, std::make_shared<EmptyDrawSystem>());
    else if (i % 3) engine->addSystem(5, std::make_shared<EmptyPlaceSystem>());
    else if (i % 5) engine->addSystem(5, std::make_shared<EmptyAllSystem>());
    else engine->addSystem(5, std::make_shared<EmptyEmptySystem>());
  }

  std::default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> component(1,4);

  for (int i = 0; i < 3200; i++)
  {
    std::shared_ptr<Entity> ent = std::make_shared<Entity>();
    std::shared_ptr<Draw> draw = std::make_shared<Draw>();
    std::shared_ptr<Place> place = std::make_shared<Place>();
    std::shared_ptr<Velocity> velocity = std::make_shared<Velocity>();
    std::shared_ptr<Accelerator> accelerator = std::make_shared<Accelerator>();
    place->x = component(generator) - 2;
    place->y = component(generator) - 2;
    place->z = component(generator) - 2;
    velocity->x = component(generator) - 2;
    velocity->y = component(generator) - 2;
    velocity->z = component(generator) - 2;
    accelerator->x = component(generator) - 2;
    accelerator->y = component(generator) - 2;
    accelerator->z = component(generator) - 2;
    if (component(generator) > 1) ent->add(draw);
    if (component(generator) > 1) ent->add(place);
    if (component(generator) > 1) ent->add(velocity);
    if (component(generator) > 1) ent->add(accelerator);
    engine->addEntity(ent);

//    std::cout << ent->name() << ":" << ent->exist<Draw>() << ent->exist<Place>() << ent->exist<Velocity>() << ent->exist<Accelerator>() << std::endl;
  }

  std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point begin2 = std::chrono::high_resolution_clock::now();

  while (!winGame->win)
  {
    std::chrono::high_resolution_clock::duration d = std::chrono::high_resolution_clock::now() - begin;
    begin = std::chrono::high_resolution_clock::now();
    double time = d.count() / 1000000000.0;
    engine->update(time);
//    std::cout << "time:" << time << std::endl;
  }

  std::chrono::high_resolution_clock::duration d = std::chrono::high_resolution_clock::now() - begin2;
  double time = d.count() / 1000000.0;
  std::cout << "AllTime:" << time << std::endl;
  std::cout << "Iterations:" << iterations->mainIteration << " " << iterations->iterationsForEntity << std::endl;
  std::cout << "avgTime:" << time / iterations->mainIteration << " " << time / iterations->iterationsForEntity << std::endl;

  std::shared_ptr<Entity> entity = winGame->winner;

  std::cout << entity->name() << std::endl;
  std::shared_ptr<Place> place = entity->get<Place>();
  std::cout << "place:" << place->x << " " << place->y << " " << place->z << std::endl;
  std::shared_ptr<Velocity> vel = entity->unsafeGet<Velocity>();
  if (vel) std::cout << "velocity:" << vel->x << " " << vel->y << " " << vel->z << std::endl;
  std::shared_ptr<Accelerator> acc = entity->unsafeGet<Accelerator>();
  if (acc) std::cout << "accelerator:" << acc->x << " " << acc->y << " " << acc->z << std::endl;
  if (entity->exist<Draw>()) std::cout << "draw." << std::endl;

  return 0;
}
