#include "entitystatemachine.h"

#include "entity.h"

EntityStateMachine::EntityStateMachine(std::shared_ptr<Entity> entity)
  : m_entity(entity)
{
  if (!entity) throw std::invalid_argument("Entity is NULL!");
}

std::shared_ptr<Entity> EntityStateMachine::createState(const int &state)
{
  if (m_states.count(state) > 0) throw std::invalid_argument("Unable to create State is already exist!");
  std::shared_ptr<Entity> entity = std::make_shared<Entity>();
  m_states[state] = entity;
  return entity;
}

void EntityStateMachine::changeState(const int &state)
{
  if (m_states.count(state) == 0) throw std::invalid_argument("State not exist!");
  m_entity->addAndUpdate(m_states[state]);
}
