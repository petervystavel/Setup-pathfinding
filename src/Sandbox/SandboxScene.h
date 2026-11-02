#pragma once

#include "Scene.h"
#include "Grid.h"

constexpr float PLAYER_MOVE_DELAY = 0.25f;

class SandboxScene : public Scene
{
    Entity* mpPlayer;
    Grid* mpGrid;

    Vector2f mTileSize;
    Vector2f mOffset;

    GridCoord mMouseCoord;
    GridCoord mPlayerCoord;

    std::vector<Tile*> mBuiltPath;
    int mIndexBuiltPath;
    float mMoveTimer;
    float mMoveDelay;

protected:
    void OnInitialize() override;
    void OnUpdate() override;

    Color GetTileColor(int row, int col);
    void SetPlayerCoord(GridCoord coord);
};
