#include "entity.h"

int Entity::nameNumber = 0;

Entity::Entity(const std::string &name) :
  m_name(name)
{
  if (m_name == "") m_name = std::string("Entity_") + std::to_string(nameNumber++);
}

const std::string &Entity::name()
{
  return m_name;
}
