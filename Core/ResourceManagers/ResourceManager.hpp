#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP
#include "Core/Common.hpp"
class ResourceManager {
public:
    ResourceManager() {}
    ~ResourceManager() {}
    virtual string name() const = 0;
};
#endif