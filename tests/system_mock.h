#ifndef SYSTEM_MOCK_H
#define SYSTEM_MOCK_H

#include "system.h"
#include "engine.h"

#include "gmock/gmock.h"

class System_mock : public System<>
{
  public:
    MOCK_METHOD2(preUpdate, void(const double &, std::vector<std::shared_ptr<Entity>> &));
    MOCK_METHOD2(postUpdate, void(const double &, std::vector<std::shared_ptr<Entity>> &));

    bool checkEngine(const std::shared_ptr<Engine> &engine) const { return m_engine == engine; }
};

#endif // SYSTEM_MOCK_H
