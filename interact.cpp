#include "interact.h"

#include "Game.h"

#include <iterator>
#include <fstream>

#define TIMER 10001

string fileName;

void InitSystem(string fileN) {
    fileName = fileN;
}


int Interact(HDC hdc, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HBRUSH Brush;
    HGDIOBJ hOldBrush;
    PAINTSTRUCT ps;

    static Game* game;
    static int flagStart = 0;
    GAME_STATUS gameStatus;


    switch (message) {
    case WM_TIMER:
        if (flagStart) {
            game->DrawCellsOnEntities(hdc);

            gameStatus = game->Update();
            switch (gameStatus) {
            case GAME_LOSE:
                TextOut(hdc, 10, 10, TEXT("YOU HAVE LOST"), strlen("YOU HAVE LOST"));
                flagStart = 0;
                break;
            case GAME_WIN: 
                TextOut(hdc, 10, 10, TEXT("YOU HAVE WON"), strlen("YOU HAVE WON"));
                flagStart = 0;
                break;
            }
            game->DrawEntities(hdc);
        }
        break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_RETURN:
            if (!flagStart) {
                flagStart = 1;
                ifstream inFile;
                inFile.open(fileName, std::ifstream::in);
                game = new Game(inFile, 1, 100);
                SetTimer(hWnd, TIMER, 100, NULL);
                game->DrawAll(hdc);
                return 0;
            }
            break;

        case VK_LEFT:
            if (flagStart) {
                game->SetPacmanDirection(LEFT);
            }
            break;

        case VK_RIGHT:
            if (flagStart) {
                game->SetPacmanDirection(RIGHT);
            }
            break;

        case VK_UP:
            if (flagStart) {
                game->SetPacmanDirection(DOWN);
            }
            break;

        case VK_DOWN:
            if (flagStart) {
                game->SetPacmanDirection(UP);
            }
            break;
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}