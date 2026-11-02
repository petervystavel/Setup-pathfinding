#pragma once

#include "Scene.h"

class Player;

class SandboxScene : public Scene
{
    Player* mpEntity1 = nullptr;
    Player* mpEntity2 = nullptr;

    Player* mpSelectedEntity = nullptr;

public:
    void OnInitialize() override;
    void OnUpdate() override;
};
