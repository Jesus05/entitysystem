#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <memory>
#include <typeindex>
#include <map>
#include <vector>

class Entity : public std::enable_shared_from_this<Entity>
{
  private:
    std::string m_name;
    static int nameNumber;
    std::map<std::type_index, std::shared_ptr<void>> m_componentMap;

    bool add(const std::type_index &index, std::shared_ptr<void> ptr);
    std::shared_ptr<void> get(const std::type_index &index);

  public:
    Entity(const std::string &name = "");
    const std::string &name();
    template <class T>
    std::shared_ptr<Entity> add(std::shared_ptr<T> &component);
    template <class T>
    std::shared_ptr<T> get();
    bool exist(const std::vector<std::type_index> &components) const;
};

///Все что ниже вынести в entity.hpp

#include <iostream>

template<class T>
std::shared_ptr<Entity> Entity::add(std::shared_ptr<T> &component)
{
  if (!add(typeid(std::shared_ptr<T>), component)) throw std::invalid_argument("unable to add component!");
  return shared_from_this();
}

template<class T>
std::shared_ptr<T> Entity::get()
{
  std::shared_ptr<void> temp = get(typeid(std::shared_ptr<T>));
  if (!temp) throw std::invalid_argument("Uanble to get component!");
  return std::static_pointer_cast<T>(temp);
}

#include "entity.hpp"

#endif // ENTITY_H
