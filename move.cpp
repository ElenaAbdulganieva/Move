#include "TXlib.h"

void Management (int vx, int vy);

void DrawStar (int x, int y, double sizeX, double sizeY);

void StarManagement
(int x, int y, double sizeX, double sizeY, int vx, int vy, int dt,
 int leftborder, int rightborder, int upborder, int downborder);

int main ()
    {
    txCreateWindow (800, 600);

    StarManagement (200, 200, 0.3, 0.3, 5, 5, 1, 10, 790, 10, 590);

    return 0;
    }

void Management (int vx, int vy)
    {
    if (txGetAsyncKeyState (VK_RIGHT)) vx ++;
    if (txGetAsyncKeyState (VK_LEFT))  vx --;
    if (txGetAsyncKeyState (VK_UP))    vy --;
    if (txGetAsyncKeyState (VK_DOWN))  vy ++;

    if (txGetAsyncKeyState (VK_SPACE)) vx = vy = 0;
    }

void DrawStar (int x, int y, double sizeX, double sizeY)
    {
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

void StarManagement
(int x, int y, double sizeX, double sizeY, int vx, int vy, int dt,
 int leftborder, int rightborder, int upborder, int downborder)
    {
    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetColor (RGB (x + y, y, x), 5);
        txSetFillColor (RGB (x, y, x + y));
        DrawStar (x, y, sizeX, sizeY);

        txSleep (20);

        txSetColor (TX_BLACK, 5);
        txSetFillColor (TX_BLACK);
        DrawStar (x, y, sizeX, sizeY);

        x += vx * dt;
        y += vy * dt;

        if (x > rightborder - 165 * sizeX)
            {
            vx = - vx;
            x = rightborder - 165 * sizeX;
            }

        if (y > downborder - 165 * sizeX)
            {
            vy = - vy;
            y = downborder - 165 * sizeX;
            }

        if (x < leftborder + 165 * sizeX)
            {
            vx = - vx;
            x = leftborder + 165 * sizeX;
            }

        if (y < upborder + 165 * sizeX)
            {
            vy = - vy;
            y = upborder + 165 * sizeX;
            }

        Management (vx, vy);
        }
    }
