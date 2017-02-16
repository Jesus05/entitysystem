#ifndef ENGINE_H
#define ENGINE_H

#include <set>
#include <map>
#include <memory>
#include <vector>

struct Entity;
class SystemBase;

struct Engine : public std::enable_shared_from_this<Engine>
{
  private:
    typedef std::pair<int, std::shared_ptr<SystemBase>> TSystemPair;
    typedef std::multimap<int, std::shared_ptr<SystemBase>> TSystemMap;
    typedef std::pair<std::string, std::shared_ptr<Entity>> TEntityPair;
    typedef std::map<std::string, std::shared_ptr<Entity>> TEntityMap;

    TEntityMap m_entityes;
    TSystemMap m_systems;

    std::set<std::shared_ptr<SystemBase>> m_systemToRemove;
    std::set<std::shared_ptr<Entity>> m_entityToRemove;

    bool m_isUpdating;

    void afterUpdate();
    std::vector<std::shared_ptr<Entity>> getEntityesForSystem(std::shared_ptr<SystemBase> &system);

  public:

    Engine();

    void addEntity(std::shared_ptr<Entity> entity);
    void removeEntity(std::shared_ptr<Entity> entity);
    void addSystem(const int &priority, std::shared_ptr<SystemBase> system);
    void removeSystem(std::shared_ptr<SystemBase> system);

    void update(const double &time);

    void removeAllSystems();

    const bool &isUpdating() const;
};

#endif // ENGINE_H
