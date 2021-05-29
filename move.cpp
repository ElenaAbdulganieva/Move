#include "TXlib.h"

void MoveBallManagement (int x, int y, int r, int vx, int vy, int dt,
                         int leftborder, int rightborder, int upborder, int downborder);

void Management (int vx, int vy);

int main ()
    {
    txCreateWindow (800, 600);

    MoveBallManagement (100, 100, 30, 15, -5, 1, 10, 790, 10, 590);
    MoveBall           (300, 300, 30, 10,  5, 2, 10, 790, 10, 590);
    return 0;
    }

void MoveBallManagement (int x, int y, int r, int vx, int vy, int dt,
                         int leftborder, int rightborder, int upborder, int downborder)
    {
     while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txSetColor     (RGB (x, y, x + y));
        txSetFillColor (RGB (x + y, x, y));
        txCircle (x, y, r);

        x += vx * dt;
        y += vy * dt;

        if (x > rightborder - r)
            {
            vx = - vx;
            x = rightborder - r;
            }

        if (y > downborder - r)
            {
            vy = - vy;
            y = downborder - r;
            }

        if (x < leftborder + r)
            {
            vx = - vx;
            x = leftborder + r;
            }

        if (y < upborder + r)
            {
            vy = - vy;
            y = upborder + r;
            }

        Management (vx, vy);

        txSleep (20);
        }
    }

void Management (int vx, int vy)
    {
    if (txGetAsyncKeyState (VK_RIGHT)) vx ++;
    if (txGetAsyncKeyState (VK_LEFT))  vx --;
    if (txGetAsyncKeyState (VK_UP))    vy --;
    if (txGetAsyncKeyState (VK_DOWN))  vy ++;

    if (txGetAsyncKeyState (VK_SPACE)) vx = vy = 0;
    }
