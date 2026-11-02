#include "SampleScene.h"

#include "DummyEntity.h"
#include "InputManager.h"
#include "Debug.h"

void SandboxScene::OnInitialize()
{
    mpEntity1 = CreateEntity<Player>(40.f, Color::Cyan);
    mpEntity1->SetPosition({ 300.f, 360.f });
    mpEntity1->SetRigidBody(true);

    mpEntity2 = CreateEntity<Player>(60.f, Color::Orange);
    mpEntity2->SetPosition({ 700.f, 360.f });
    mpEntity2->SetRigidBody(true);
}

void SandboxScene::OnUpdate()
{
    Debug::DrawText({ 10.f, 10.f },
        "Clic gauche : selectionner un cercle, puis cliquer pour le déplacer.", Color::White);

    InputManager* input = InputManager::Get();

    Vector2f mousePos = input->GetMousePosition();

    if (input->IsMouseDown(SDL_BUTTON_LEFT))
    {
        if (mpEntity1->IsPointInside(mousePos))
        {
            mpSelectedEntity = mpEntity1;
        }
        else if (mpEntity2->IsPointInside(mousePos))
        {
            mpSelectedEntity = mpEntity2;
        }
        else if (mpSelectedEntity != nullptr)
        {
            mpSelectedEntity->GoTo(mousePos, 200.f);
        }
    }

    if (mpSelectedEntity != nullptr)
    {
        Debug::DrawCircle(mpSelectedEntity->GetPosition(), 5.f, Color::Magenta, true);
    }
}
