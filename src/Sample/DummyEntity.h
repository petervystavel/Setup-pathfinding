#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
    void OnCollision(Entity* other) override;
};
