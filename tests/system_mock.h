#ifndef SYSTEM_MOCK_H
#define SYSTEM_MOCK_H

#include "system.h"

#include "gmock/gmock.h"

class System_mock : public System<>
{
  public:
    MOCK_METHOD1(update, void(const double &));

    bool checkEngine(const std::shared_ptr<Engine> &engine) const { return m_engine == engine; }
};

#endif // SYSTEM_MOCK_H
