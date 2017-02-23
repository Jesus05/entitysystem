#ifndef ENTITY_H
#define ENTITY_H

#include "typeindexer.h"

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
    std::map<long long, std::shared_ptr<void>> m_componentMap;

    bool add(const std::type_index &index, std::shared_ptr<void> ptr);
    std::shared_ptr<void> get(const std::type_index &index);

  public:
    Entity(const std::string &name = "");
    const std::string &name();
    template <class T>
    std::shared_ptr<Entity> add(std::shared_ptr<T> component);
    template <class T>
    std::shared_ptr<T> get();
    bool exist(const std::vector<long long> &components) const;
    std::vector<std::shared_ptr<void>> get(const std::vector<long long> &components) const;
    template<class T>
    bool exist() const;
    template <class T>
    inline std::shared_ptr<T> unsafeGet();
    template<class T>
    void remove();
};

///Все что ниже вынести в entity.hpp

#include <iostream>

template<class T>
std::shared_ptr<Entity> Entity::add(std::shared_ptr<T> component)
{
  if (!component) throw std::invalid_argument(std::string("unable to add NULL component! ") + typeid(T).name());
  if (!add(typeid(std::shared_ptr<T>), component)) throw std::invalid_argument(std::string("unable to add component! ") + typeid(T).name());
  return shared_from_this();
}

template<class T>
std::shared_ptr<T> Entity::get()
{
  std::shared_ptr<void> temp = get(typeid(std::shared_ptr<T>));
  if (!temp) throw std::invalid_argument(std::string("Uanble to get component! ") + typeid(T).name());
  return std::static_pointer_cast<T>(temp);
}

template<class T>
bool Entity::exist() const
{
  return m_componentMap.count(TypeIndexer::index(typeid(std::shared_ptr<T>))) != 0;
}

template<class T>
inline std::shared_ptr<T> Entity::unsafeGet()
{
  if (exist<T>()) return std::static_pointer_cast<T>(get(typeid(std::shared_ptr<T>)));
  return std::shared_ptr<T>();
}

template<class T>
void Entity::remove()
{
  if (exist<T>()) m_componentMap.erase(TypeIndexer::index(typeid(std::shared_ptr<T>)));
  else throw std::invalid_argument(std::string("Uanble to remove component! ") + typeid(T).name());
}

#include "entity.hpp"

#endif // ENTITY_H
