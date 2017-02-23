#ifndef ENTITYSTATEMACHINE_H
#define ENTITYSTATEMACHINE_H

#include <map>
#include <memory>

class Entity;

class EntityStateMachine
{
  private:
    std::shared_ptr<Entity> m_entity;
    std::map<int, std::shared_ptr<Entity>> m_states;
    int m_currentState;

    void removeOtherState();
  public:
    EntityStateMachine(std::shared_ptr<Entity> entity);
    std::shared_ptr<Entity> createState(const int &state);
    void changeState(const int &state);
};

#endif // ENTITYSTATEMACHINE_H
