#ifndef SYSTEM_H
#define SYSTEM_H

#include "typeindexer.h"

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

    virtual void handleEntity(const double &time, std::shared_ptr<Entity> &entity);
    virtual void preUpdate(const double &time, std::vector<std::shared_ptr<Entity>> &entityes);
    virtual void postUpdate(const double &time, std::vector<std::shared_ptr<Entity>> &entityes);

  public:
    virtual ~SystemBase();

    void update(const double &time, std::vector<std::shared_ptr<Entity>> &entityes);
    void setEngine(const std::shared_ptr<Engine> &engine);
    virtual const std::vector<long long> &componentTypes() const;
};

template<typename ... Classes>
class System : public SystemBase
{
  private:
    static const std::vector<long long> m_indexes;
  public:
    virtual ~System() { };
    virtual const std::vector<long long> &componentTypes() const { return m_indexes; }
};

template<typename ... Classes>
const std::vector<long long> System<Classes ...>::m_indexes = {TypeIndexer::index(typeid(std::shared_ptr<Classes>)) ...};

#endif // SYSTEM_H
