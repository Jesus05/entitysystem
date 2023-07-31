#include "helpers.h"

#include "engine.h"
#include "entity.h"
#include "system.h"

std::shared_ptr<Engine> Create_engine()
{
    return std::make_shared<Engine>();
}

std::shared_ptr<Entity> Create_entity(const std::string &name)
{
    return std::make_shared<Entity>(name);
}
