#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <array>
#include <typeindex>
#include <memory>

class Engine;
class Entity;

class SystemBase
{
  protected:
    std::shared_ptr<Engine> m_engine;
  public:
    virtual void update(const double &time);
    void setEngine(const std::shared_ptr<Engine> &engine);
};

template<typename ... Classes>
class System : public SystemBase
{
  protected:
    static const std::array<std::type_index, sizeof...(Classes)> m_indexes;
};

template<typename ... Classes>
const std::array<std::type_index, sizeof...(Classes)> System<Classes ...>::m_indexes = {typeid(std::shared_ptr<Classes>) ...};

#endif // SYSTEM_H
