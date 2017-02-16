#include "engine.h"
#include "entity.h"
#include "system.h"

struct Draw
{
};

struct Place
{
    int x;
    int y;
    int z;
};

struct Velocity
{
    int x;
    int y;
    int z;
};

struct Accelerator
{
    int x;
    int y;
    int z;
};

struct SaveSystem : public System<>
{
    void handleEntity(const double &time, std::shared_ptr<Entity> &entity)
    {
      std::shared_ptr<Draw> draw = entity->get<Draw>();
      std::shared_ptr<Place> place = entity->get<Place>();
      std::shared_ptr<Velocity> velocity = entity->get<Velocity>();
      std::shared_ptr<Accelerator> accelerator = entity->get<Accelerator>();

    }
}

int main()
{
  std::shared_ptr<Engine> engine = std::make_shared<Engine>();



  return 0;
}
