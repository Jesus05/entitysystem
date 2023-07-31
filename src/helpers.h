#ifndef HELPERS_H
#define HELPERS_H

#include <memory>

class Entity;
class Engine;
class SystemBase;

std::shared_ptr<Engine> Create_engine();
std::shared_ptr<Entity> Create_entity(const std::string &name = "");

template <typename T>
std::shared_ptr<T> Create_system()
{
    return std::make_shared<T>();
}

template <typename T>
std::shared_ptr<T> Create_component(const T &component = T())
{
    return std::make_shared<T>(component);
}


#endif // HELPERS_H
