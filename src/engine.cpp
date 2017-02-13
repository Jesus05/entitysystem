#include "engine.h"

#include <algorithm>

#include "debugmacros.h"

void Engine::addEntity(std::shared_ptr<Entity> entity)
{
  const std::string &name = entity->name();

  if (!entity)
  {
    std::cerr << "Entity is null." << V(name) << V(entity.get());
    throw std::invalid_argument("Entity is null!");
  }

  if (m_entityes.count(name) != 0)
  {
    std::cerr << "Entity is exist." << V(name) << V(m_entityes.at(name).get()) << V(entity.get());
    throw std::invalid_argument("Entity exist!");
  }
  m_entityes[name] = entity;
}

void Engine::removeEntity(std::shared_ptr<Entity> entity)
{
  const std::string &name = entity->name();

  if (m_entityes.count(name) == 0)
  {
    std::cerr << "Entity not exist." << V(name) << V(entity.get());
    throw std::invalid_argument("Entity not exist!");
  }
  std::shared_ptr<Entity> &ent = m_entityes[name];
  if (ent.get() != entity.get())
  {
    std::cerr << "Entity have other pointer." << V(name) << V(entity.get()) << V(ent.get());
    throw std::invalid_argument("Entity have other pointer!");
  }
  m_entityes.erase(name);
}

void Engine::addSystem(const int &priority, std::shared_ptr<System> system)
{
  if (!system)
  {
    std::cerr << "System is null" << V(system.get());
    throw std::invalid_argument("System is null!");
  }
  m_systems.insert(std::make_pair(priority, system));
}

void Engine::removeSystem(std::shared_ptr<System> system)
{
  bool isExist = false;

  for (TSystemMap::iterator iter = m_systems.begin(); iter != m_systems.end(); iter++)
  {
    std::shared_ptr<System> our = iter->second;
    if (our != system) continue;
    isExist = true;
    iter = m_systems.erase(iter);
  }

  if (!isExist)
  {
    std::cerr << "System not exist" << V(system.get());
    throw std::invalid_argument("System not exist!");
  }
}
