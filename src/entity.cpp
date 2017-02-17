#include "entity.h"

#include "debugmacros.h"

int Entity::nameNumber = 0;

bool Entity::add(const std::type_index &index, std::shared_ptr<void> ptr)
{
  const long long innerIndex = TypeIndexer::index(index);
  if (m_componentMap.count(innerIndex) > 0)
  {
    std::cerr << "Component double!" << V(index.name()) << V(m_name) << V(ptr.get()) << V(m_componentMap.at(innerIndex).get());
    return false;
  }
  m_componentMap[innerIndex] = ptr;
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

bool Entity::exist(const std::vector<long long> &components) const
{
  if (m_componentMap.size() == 0) return false; //Если компонентов нет вообще, то такая сущность ненужна не одной системе
  if (components.size() == 0) return true;
  for (const long long &index : components)
  {
    if (m_componentMap.count(index) == 0) return false; //Как минимум 1 компонента нет
  }
  return true; //Все компоненты есть
}

std::shared_ptr<void> Entity::get(const std::type_index &index)
{
  const long long innerIndex = TypeIndexer::index(index);
  if (m_componentMap.count(innerIndex) == 0)
  {
    std::cerr << "Requested not exist component!" << V(index.name()) << V(m_name) << V(m_componentMap.size());
    return std::shared_ptr<void>();
  }

  return m_componentMap.at(innerIndex);
}
