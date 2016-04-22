#include "PhyManager.h"

#include <cmath>

PhyManager::PhyManager()
{
    _dt = 0.016;
}

// manage entities collisions
void PhyManager::update()
{
    double coeff = 1.0;

    int entitiesCount = _entities.size();
    for (int i(0); i<entitiesCount; ++i)
    {
        Entity2D* entity1 = _entities[i];
        double currentX = entity1->getX();
        double currentY = entity1->getY();
        double currentRadius = entity1->getR();

        for (int k(i+1); k<entitiesCount; k++)
        {
            Entity2D* entity2 = _entities[k];
            double colliderRadius = entity2->getR();

            double minDist = currentRadius+colliderRadius;
            double vx, vy, dist2;

            vx = currentX-entity2->getX();
            vy = currentY-entity2->getY();

            dist2 = vx*vx+vy*vy;

            if (dist2 && dist2 < minDist*minDist)
            {
                double dist = sqrt(dist2);
                double deltaDist = minDist-dist;

                vx *= 0.5*coeff*deltaDist/(dist);
                vy *= 0.5*coeff*deltaDist/(dist);

                entity1->move(vx, vy);
                entity2->move(-vx, -vy);
            }
        }
    }
}

void PhyManager::addEntity(Entity2D* &entity)
{
    _entities.push_back(entity);
}
