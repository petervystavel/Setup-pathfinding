#include "Grid.h"

#include <algorithm>
#include <cassert>

Grid::Grid(const std::vector< std::vector<char>>& map)
{
    RowCount = map.size();
    ColCount = map[0].size();

    mTiles.resize(RowCount);
    for (int row = 0; row < RowCount; ++row)
    {
        mTiles[row].resize(ColCount);
        for (int col = 0; col < ColCount; ++col)
        {
            Tile& tile = mTiles[row][col];
            tile.coord = { row, col };
            tile.obstacle = map[row][col] == OBSTACLE;
            tile.height = map[row][col] == HEIGHT ? 5 : 1;

            tile.added = false;
            tile.path = false;
            tile.cameFrom = nullptr;
        }
    }
}

void Grid::Reset()
{
    for (int row = 0; row < RowCount; row++)
    {
        for (int col = 0; col < ColCount; col++)
        {
            Tile& tile = mTiles[row][col];

            tile.cost = -1;
            tile.added = false;
            tile.path = false;
            tile.cameFrom = nullptr;
        }
    }

    mBuiltPath.clear();
}

bool Grid::IsValidIndex(GridCoord coord)
{
    if (coord.row < 0 || coord.row >= RowCount)
        return false;

    if (coord.col < 0 || coord.col >= ColCount)
        return false;
}

Tile* Grid::GetTile(GridCoord coord)
{
    if (IsValidIndex(coord) == false)
        return nullptr;

    return &mTiles[coord.row][coord.col];
}

int Grid::GetHeightCost(Tile* t1, Tile* t2)
{
    return std::abs(t1->height - t2->height) + 1;
}

void Insert(std::list<Tile*>& remains, Tile* tile)
{
    auto it = remains.begin();

    for (; it != remains.end(); ++it)
    {
        if ((*it)->cost > tile->cost)
            break;
    }

    remains.insert(it, tile);
}

void Reinsert(std::list<Tile*>& remains, Tile* tile)
{
    auto it = std::find(remains.begin(), remains.end(), tile);

    assert(it != remains.end());

    remains.erase(it);
    Insert(remains, tile);
}

void Grid::TryAddTile(std::list<Tile*>& remains, Tile* current, Tile* neighbor)
{
    if (neighbor == nullptr || neighbor->obstacle)
        return;

    int newCost = current->cost + GetHeightCost(current, neighbor);

    if (neighbor->added && newCost >= neighbor->cost)
        return;

    neighbor->cost = newCost;
    neighbor->cameFrom = current;

    if (neighbor->added)
    {
        Reinsert(remains, neighbor);
    }
    else
    {
        Insert(remains, neighbor);
        neighbor->added = true;
    }
}

bool Grid::BuildPath(GridCoord startCoord, GridCoord endCoord)
{
    Reset();

    Tile* start = GetTile(startCoord);
    Tile* end = GetTile(endCoord);

    std::list<Tile*> remains;
    start->added = true;
    start->cost = 0;
    remains.push_back(start);

    while (remains.size() > 0)
    {
        Tile* current = remains.front();
        remains.pop_front();

        if (current == end)
        {
            while (current->cameFrom != nullptr)
            {
                current->path = true;
                mBuiltPath.push_back(current);
                current = current->cameFrom;
            }

            std::reverse(mBuiltPath.begin(), mBuiltPath.end());

            return true;
        }

        constexpr GridCoord directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        for (int i = 0; i < 4; ++i)
        {
            GridCoord coord = current->coord + directions[i];

            Tile* neighbor = GetTile(coord);

            TryAddTile(remains, current, neighbor);
        }
    }

    return false;
}
