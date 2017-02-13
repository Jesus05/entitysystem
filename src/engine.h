#ifndef ENGINE_H
#define ENGINE_H

#include <set>
#include <map>
#include <memory>
#include <string>

struct Entity
{
  const std::string &name() { static std::string name = ""; return name; }
};

struct System
{
  virtual void update(const double &time) { };
};

struct Engine
{
  private:
    typedef std::pair<int, std::shared_ptr<System>> TSystemPair;
    typedef std::multimap<int, std::shared_ptr<System>> TSystemMap;
    typedef std::pair<std::string, std::shared_ptr<Entity>> TEntityPair;
    typedef std::map<std::string, std::shared_ptr<Entity>> TEntityMap;

    TEntityMap m_entityes;
    TSystemMap m_systems;

    std::set<std::shared_ptr<System>> m_systemToRemove;
    std::set<std::shared_ptr<Entity>> m_entityToRemove;

    bool m_isUpdating;

    void afterUpdate();

  public:

    Engine();

    void addEntity(std::shared_ptr<Entity> entity);
    void removeEntity(std::shared_ptr<Entity> entity);
    void addSystem(const int &priority, std::shared_ptr<System> system);
    void removeSystem(std::shared_ptr<System> system);

    void update(const double &time);

    const bool &isUpdating() const;
};

#endif // ENGINE_H
