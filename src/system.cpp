#include "system.h"

void SystemBase::handleEntity(const double &/*time*/, std::shared_ptr<Entity> &/*entity*/)
{

}

void SystemBase::preUpdate(const double &/*time*/, std::vector<std::shared_ptr<Entity> > &/*entityes*/)
{

}

void SystemBase::postUpdate(const double &/*time*/, std::vector<std::shared_ptr<Entity> > &/*entityes*/)
{

}

void SystemBase::onSetEngine()
{

}

SystemBase::SystemBase() : m_isSubsystem(false)
{

}

SystemBase::~SystemBase()
{
}

void SystemBase::update(const double &time, std::vector<std::shared_ptr<Entity> > &entityes)
{
  if (m_isSubsystem)
  {
    m_entityes = entityes;
    return;
  }
  preUpdate(time, entityes);
  for (std::shared_ptr<Entity> &entity : entityes)
  {
    handleEntity(time, entity);
  }
  postUpdate(time, entityes);
}

void SystemBase::setEngine(const std::shared_ptr<Engine> &engine, const int &priority)
{
  m_engine = engine;
  m_priority = priority;
  onSetEngine();
}

const std::vector<long long> &SystemBase::componentTypes() const
{
  static std::vector<long long> components;
  return components;
}

std::vector<std::shared_ptr<Entity> > SystemBase::entityes() const
{
  return m_entityes;
}
