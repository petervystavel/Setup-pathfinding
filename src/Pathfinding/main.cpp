#include <vector>
#include <conio.h>

#include "Grid.h"

#define NOMINMAX
#include <windows.h>

void gotoxy(short x, short y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };
    SetConsoleCursorPosition(hConsole, position);
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

class App
{
    Grid* mGrid;

    GridCoord mPlayerCoord;
    GridCoord mCursorCoord;

    bool mValidPath = false;

    std::vector<std::vector<char>> map =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
        {'#','#','#','#','#',' ','#',' ',' ',' ' },
        {' ','#','#','#',' ',' ','#',' ',' ',' ' },
        {' ',' ','#',' ',' ',' ','#',' ',' ',' ' },
        {' ',' ',' ',' ',' ',' ','#',' ',' ',' ' },
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
        {' ',' ',' ',' ',' ',' ','#',' ',' ',' ' },
        {' ',' ',' ',' ',' ',' ','#',' ',' ',' ' },
        {' ',' ',' ',' ',' ',' ','#','#',' ',' ' },
        {' ',' ',' ',' ',' ',' ','#','#','#',' ' },
    };

public:
    App()
    {
        mGrid = new Grid(map);
        mPlayerCoord = { 0, 0 };
        mCursorCoord = { 0, 0 };
    }

    ~App()
    {
        delete mGrid;
    }

    void Run()
    {
        hidecursor();

        while (true)
        {
            Display();

            Input();

            mValidPath = mGrid->BuildPath(mPlayerCoord, mCursorCoord);
        }
    }

private:
    void Display()
    {
        gotoxy(0, 0); //refresh

        for (int row = 0; row < mGrid->RowCount; row++)
        {
            for (int col = 0; col < mGrid->ColCount; col++)
            {
                std::cout << "[";

                if (mCursorCoord.Is(row, col))
                {
                    std::cout << BG_GREEN;
                }
                else if (mGrid->GetTile({ row, col })->path)
                {
                    std::cout << BG_RED;
                }

                if (mPlayerCoord.Is(row, col))
                {
                    std::cout << PLAYER;
                }
                else
                {
                    std::cout << map[row][col];
                }

                std::cout << DEFAULT;

                std::cout << "]";
            }

            std::cout << std::endl;
        }
    }

    void Input()
    {
        while (true)
        {
            int input = _getch();
            GridCoord newCoord;
            switch (input)
            {
            case 'z':
                newCoord = { mCursorCoord.row - 1, mCursorCoord.col };
                if (mGrid->IsValidIndex(newCoord))
                    mCursorCoord = newCoord;

                return;

            case 's':
                newCoord = { mCursorCoord.row + 1, mCursorCoord.col };
                if (mGrid->IsValidIndex(newCoord))
                    mCursorCoord = newCoord;

                return;

            case 'q':
                newCoord = { mCursorCoord.row, mCursorCoord.col - 1 };
                if (mGrid->IsValidIndex(newCoord))
                    mCursorCoord = newCoord;

                return;

            case 'd':
                newCoord = { mCursorCoord.row, mCursorCoord.col + 1 };
                if (mGrid->IsValidIndex(newCoord))
                    mCursorCoord = newCoord;

                return;

            case '\r':
                if (mValidPath)
                    mPlayerCoord = mCursorCoord;
                return;
            }
        }
    }
};

int main()
{
    App app;

    app.Run();

    return 0;
}
