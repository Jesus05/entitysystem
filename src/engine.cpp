#include "engine.h"

#include <algorithm>

#include "debugmacros.h"

template <typename T1, typename T2>
void removeAllFromMap(T1 &from, T2 &to)
{
  for (auto iter = from.begin(); iter != from.end(); iter++)
  {
    auto our = iter->second;
    if (to.count(our) == 0) continue;
    to.erase(our); //Надо проверить так быстрее или без этой строки
    iter = from.erase(iter);
    if (iter == from.end()) break;
  }
  to.clear();
}

void Engine::afterUpdate()
{
  removeAllFromMap(m_systems, m_systemToRemove);
  removeAllFromMap(m_entityes, m_entityToRemove);
}

Engine::Engine() : m_isUpdating(false)
{
}

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
  m_entityToRemove.insert(entity);
  if (!m_isUpdating) afterUpdate();
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
  m_systemToRemove.insert(system);
  if (m_isUpdating) afterUpdate();
}

void Engine::update(const double &time)
{
  m_isUpdating = true;
  for (TSystemPair pair : m_systems)
  {
    std::shared_ptr<System> &system = pair.second;
    system->update(time);
  }
  m_isUpdating = false;
  afterUpdate();
}

const bool &Engine::isUpdating() const
{
  return m_isUpdating;
}
