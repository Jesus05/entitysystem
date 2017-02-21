#ifndef SYSTEMGROUP_H
#define SYSTEMGROUP_H

#include "system.h"
#include "engine.h"

template<typename ... Classes>
class SystemSub : public System<Classes...>
{
  public:
    SystemSub();
    virtual ~SystemSub() override;
};

template<typename ... Classes>
SystemSub<Classes...>::SystemSub() { SystemBase::m_isSubsystem = true; }

template<typename ... Classes>
SystemSub<Classes...>::~SystemSub() { }

template<typename ... SystemSubs>
class SystemGroup : public System<NoneComponent>
{
  protected:
    std::vector<std::shared_ptr<SystemBase>> m_subsystems;
    virtual void onSetEngine() override;
    virtual void update(const double &time);
    virtual void postUpdate(const double &time, std::vector<std::shared_ptr<Entity> > &entityes) override;
  public:
    SystemGroup();
    virtual ~SystemGroup();
};

template<typename ...SystemSubs>
void SystemGroup<SystemSubs...>::onSetEngine()
{
  for (std::shared_ptr<SystemBase> systemsub : m_subsystems)
  {
    m_engine->addSystem(m_priority-1, systemsub);
  }
}

template<typename ...SystemSubs>
void SystemGroup<SystemSubs...>::update(const double &/*time*/){ }

template<typename ...SystemSubs>
void SystemGroup<SystemSubs...>::postUpdate(const double &time, std::vector<std::shared_ptr<Entity> > &/*entityes*/) { update(time); }

template<typename ...SystemSubs>
SystemGroup<SystemSubs...>::SystemGroup() : m_subsystems({std::make_shared<SystemSubs>()...}) { }

template<typename ...SystemSubs>
SystemGroup<SystemSubs...>::~SystemGroup()
{
  if (!m_engine) return;
  for (std::shared_ptr<SystemBase> systemsub : m_subsystems)
  {
    m_engine->removeSystem(systemsub);
  }
}

#endif // SYSTEMGROUP_H
