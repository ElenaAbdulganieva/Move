#include "TxLib.h"

void DrawStar (int x, int y, double sizeX, double sizeY, COLORREF frame, COLORREF fill);

void Move (int* x, int* y, double sizeX, double sizeY, int* vx, int* vy, int ax, int ay,
           int dt, int leftborder, int rightborder, int upborder, int downborder);

void Management (int* vx, int* vy);

void StarMoveManagement ();

int main (void)
    {
    txCreateWindow (800, 600);

    StarMoveManagement ();

    return 0;
    }

void DrawStar (int x, int y, double sizeX, double sizeY, COLORREF frame, COLORREF fill)
    {
    txSetColor (frame, 5);
    txSetFillColor (fill);

    POINT star [] = {{x              , y - 164 * sizeY},
                     {x +  34 * sizeX, y -  52 * sizeY},
                     {x + 150 * sizeX, y -  50 * sizeY},
                     {x +  59 * sizeX, y +  17 * sizeY},
                     {x +  92 * sizeX, y + 131 * sizeY},
                     {x              , y +  65 * sizeY},
                     {x -  92 * sizeX, y + 131 * sizeY},
                     {x -  59 * sizeX, y +  17 * sizeY},
                     {x - 150 * sizeX, y -  50 * sizeY},
                     {x -  34 * sizeX, y -  52 * sizeY},
                     {x              , y - 164 * sizeY}};
    txPolygon (star, 11);
    }

void Move (int* x, int* y, double sizeX, double sizeY, int* vx, int* vy, int ax, int ay,
           int dt, int leftborder, int rightborder, int upborder, int downborder)
    {
    *vx = *vx + ax * dt;
    *vy = *vy + ay * dt;

    *x += (*vx) * dt;
    *y += (*vy) * dt;

    if (*x > rightborder - 165 * sizeX)
        {
        *vx = - (*vx);
        *x = rightborder - 165 * sizeX;
        }

    if (*y > downborder - 165 * sizeX)
        {
        *vy = - (*vy);
        *y = downborder - 165 * sizeX;
        }

    if (*x < leftborder + 165 * sizeX)
        {
        *vx = - (*vx);
        *x = leftborder + 165 * sizeX;
        }

    if (*y < upborder + 165 * sizeX)
        {
        *vy = - (*vy);
        *y = upborder + 165 * sizeX;
        }
    }

void Management (int* vx, int* vy)
    {
    if (txGetAsyncKeyState (VK_RIGHT)) (*vx) ++;
    if (txGetAsyncKeyState (VK_LEFT))  (*vx) --;
    if (txGetAsyncKeyState (VK_UP))    (*vy) --;
    if (txGetAsyncKeyState (VK_DOWN))  (*vy) ++;

    if (txGetAsyncKeyState (VK_SPACE)) *vx = *vy = 0;
    }

void StarMoveManagement ()
    {
    int x = 100; int y = 100;
    double sizeX = 0.3; double sizeY = 0.3;
    int vx = 5; int vy = 5;
    int ax = 0; int ay = 1;
    int dt = 1;
    int leftborder = 10; int rightborder = 790;
    int upborder = 10; int downborder = 590;

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        DrawStar (x, y, sizeX, sizeY, RGB (x, y, x + y), RGB (x + y, y, y));
        txLine (x, y, x + vx, y + vy);
        txSleep (20);
        DrawStar (x, y, sizeX, sizeY, TX_BLACK, TX_BLACK);
        txLine (x, y, x + vx, y + vy);

        Move (&x, &y, sizeX, sizeY, &vx, &vy, ax, ay, dt,
              leftborder, rightborder, upborder, downborder);

        Management (&vx, &vy);
        }
    }
