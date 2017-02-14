#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity
{
  private:
    std::string m_name;
    static int nameNumber;
  public:
    Entity(const std::string &name = "");
    const std::string &name();
};

#endif // ENTITY_H
