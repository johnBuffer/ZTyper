#ifndef PHYMANAGER_H_INCLUDED
#define PHYMANAGER_H_INCLUDED

#include <vector>
#include "Entity2D.h"

class PhyManager
{
public:
    PhyManager();

    void update();

    void addEntity(Entity2D* entity);
    void remove(Entity2D* entity);

private:
    double                 _dt;
    std::vector<Entity2D*> _entities;
};

#endif // PHYMANAGER_H_INCLUDED
