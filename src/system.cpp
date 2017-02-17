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

SystemBase::~SystemBase()
{
}

void SystemBase::update(const double &time, std::vector<std::shared_ptr<Entity> > &entityes)
{
  preUpdate(time, entityes);
  for (std::shared_ptr<Entity> &entity : entityes)
  {
    handleEntity(time, entity);
  }
  postUpdate(time, entityes);
}

void SystemBase::setEngine(const std::shared_ptr<Engine> &engine)
{
  m_engine = engine;
}

const std::vector<long long> &SystemBase::componentTypes() const
{
  static std::vector<long long> components;
  return components;
}
