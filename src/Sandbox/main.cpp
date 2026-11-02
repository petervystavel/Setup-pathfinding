#include "GameManager.h"
#include "SandboxScene.h"

int main()
{
    GameManager* game = GameManager::Get();

    game->LaunchScene<SandboxScene>(1280, 720, "Sandbox", Color{ 25, 25, 35 });

    return 0;
}
