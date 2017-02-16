#include "entity.h"

#include "debugmacros.h"

int Entity::nameNumber = 0;

bool Entity::add(const std::type_index &index, std::shared_ptr<void> ptr)
{
  if (m_componentMap.count(index) > 0)
  {
    std::cerr << "Component double!" << V(index.name()) << V(m_name) << V(ptr.get()) << V(m_componentMap.at(index).get());
    return false;
  }
  m_componentMap[index] = ptr;
  return true;
}

Entity::Entity(const std::string &name) :
  m_name(name)
{
  if (m_name == "") m_name = std::string("Entity_") + std::to_string(nameNumber++);
}

const std::string &Entity::name()
{
  return m_name;
}

bool Entity::exist(const std::vector<std::type_index> &components) const
{
  if (components.size() == 0) return true;
  for (const std::type_index &index : components)
  {
    if (m_componentMap.count(index) == 0) return false; //Как минимум 1 компонента нет
  }
  return true; //Все компоненты есть
}

std::shared_ptr<void> Entity::get(const std::type_index &index)
{
  if (m_componentMap.count(index) == 0)
  {
    std::cerr << "Requested not exist component!" << V(index.name()) << V(m_name) << V(m_componentMap.size());
    return std::shared_ptr<void>();
  }

  return m_componentMap.at(index);
}
