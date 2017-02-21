#ifndef SYSTEM_H
#define SYSTEM_H

#include "typeindexer.h"

#include <vector>
#include <array>
#include <typeindex>
#include <memory>
#include <tuple>

class Engine;
class Entity;

struct NoneComponent { };

class SystemBase
{
  protected:
    std::shared_ptr<Engine> m_engine;
    std::vector<std::shared_ptr<Entity>> m_entityes;
    bool m_isSubsystem;
    int m_priority;

    virtual void handleEntity(const double &time, std::shared_ptr<Entity> &entity);
    virtual void preUpdate(const double &time, std::vector<std::shared_ptr<Entity>> &entityes);
    virtual void postUpdate(const double &time, std::vector<std::shared_ptr<Entity>> &entityes);

    virtual void onSetEngine();

  public:
    SystemBase();
    virtual ~SystemBase();

    void update(const double &time, std::vector<std::shared_ptr<Entity>> &entityes);
    void setEngine(const std::shared_ptr<Engine> &engine, const int &priority);
    virtual const std::vector<long long> &componentTypes() const;
    std::vector<std::shared_ptr<Entity>> entityes() const;
};

template<typename ... Classes>
class System : public SystemBase
{
  private:
    static const std::vector<long long> m_indexes;
  public:
    typedef std::tuple<std::shared_ptr<Classes> ..., std::shared_ptr<Entity>> NodeType;
    virtual ~System() override;
    virtual const std::vector<long long> &componentTypes() const override;
};

template<typename ...Classes>
System<Classes ...>::~System() { }

template<typename ...Classes>
const std::vector<long long> &System<Classes ...>::componentTypes() const { return m_indexes; }

template<typename ... Classes>
const std::vector<long long> System<Classes ...>::m_indexes = {TypeIndexer::index(typeid(std::shared_ptr<Classes>)) ...};

#endif // SYSTEM_H
