#include "system.h"

void SystemBase::update(const double &time)
{

}

void SystemBase::setEngine(const std::shared_ptr<Engine> &engine)
{
  m_engine = engine;
}
