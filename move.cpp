#include "TxLib.h"
#include "stdio.h"

void DrawStar (int x, int y, double sizeX, double sizeY, COLORREF frame, COLORREF fill);

void Move (int* x, int* y, double sizeX, double sizeY, int* vx, int* vy, int ax, int ay,
           int dt, int leftborder, int rightborder, int upborder, int downborder);

void Management (int* vx, int* vy);

void StarMoveManagement ();

double Distance (int x, int y, int x1, int y1);

bool ControlCollision (int x, int y, int x1, int y1, double sizeX, double sizeX1);

void CollisionTrajectory ();

int ControlScore (int score, int x, int y, int x1, int y1, double sizeX, double sizeX1);

void PrintTablo (int score, int x, int y);

void Description ();

int main (void)
    {
    txCreateWindow (800, 600);

    Description ();

    StarMoveManagement ();

    return 0;
    }

//-----------------------------------------------------------------------------

void DrawStar (int x, int y, double sizeX, double sizeY, COLORREF frame, COLORREF fill)
    {
    txSetColor (frame, 2);
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

//-----------------------------------------------------------------------------

void Move (int* x, int* y, double sizeX, double sizeY, int* vx, int* vy, int ax, int ay,
           int dt, int leftborder, int rightborder, int upborder, int downborder)
    {
    *vx = *vx + ax * dt;
    *vy = *vy + ay * dt;

    *x += (*vx) * dt;
    *y += (*vy) * dt;

    if (*x > rightborder - 165 * sizeX)
        {
        txPlaySound ("ball.wav");
        *vx = - (*vx);
        *x = rightborder - 165 * sizeX;
        return;
        }

    if (*y > downborder - 165 * sizeX)
        {
        txPlaySound ("ball.wav");
        *vy = - (*vy);
        *y = downborder - 165 * sizeX;
        return;
        }

    if (*x < leftborder + 165 * sizeX)
        {
        txPlaySound ("ball.wav");
        *vx = - (*vx);
        *x = leftborder + 165 * sizeX;
        return;
        }

    if (*y < upborder + 165 * sizeX)
        {
        txPlaySound ("ball.wav");
        *vy = - (*vy);
        *y = upborder + 165 * sizeX;
        return;
        }
    }

//-----------------------------------------------------------------------------

void Management (int* vx, int* vy)
    {
    if (txGetAsyncKeyState (VK_RIGHT)) (*vx) ++;
    if (txGetAsyncKeyState (VK_LEFT))  (*vx) --;
    if (txGetAsyncKeyState (VK_UP))    (*vy) --;
    if (txGetAsyncKeyState (VK_DOWN))  (*vy) ++;

    if (txGetAsyncKeyState (VK_SPACE)) *vx = *vy = 0;
    }

//-----------------------------------------------------------------------------

double Distance (int x, int y, int x1, int y1)
    {
    double dist = sqrt((y - y1) * (y - y1) + (x - x1) * (x - x1));

    return dist;
    }

//-----------------------------------------------------------------------------

bool ControlCollision (int x, int y, int x1, int y1, double sizeX, double sizeX1)
    {
    return Distance (x, y, x1, y1) <= 165 * (sizeX + sizeX1);
    }

//-----------------------------------------------------------------------------

void CollisionTrajectory (int x, int y, int x1, int y1, double sizeX, double sizeX1, int* vx, int* vx1)
    {
    if (ControlCollision (x, y, x1, y1, sizeX, sizeX1))
        {
        txSelectFont   ("Times", 50);
        txSetColor     (TX_WHITE);
        txSetFillColor (TX_WHITE);
        txTextOut      (300, 200, "OOPS...");
        txPlaySound ("oops.wav");
        txSleep (50);
        *vx  = - *vx;
        *vx1 = - *vx1;
        }
    }

//-----------------------------------------------------------------------------

int ControlScore (int score, int x, int y, int x1, int y1, double sizeX, double sizeX1)
    {
    if (ControlCollision (x, y, x1, y1, sizeX, sizeX1))
        {
        score = score - 20;
        }
    else
        {
        score ++;
        }

    return score;
    }

//-----------------------------------------------------------------------------

void PrintTablo (int score, int x, int y)
    {
    char str[1];
    sprintf (str, "%d", score);
    txSelectFont   ("Times", 30);
    txSetColor     (TX_WHITE);
    txSetFillColor (TX_WHITE);
    txTextOut (x, y, str);
    }

//-----------------------------------------------------------------------------

void StarMoveManagement ()
    {
    txBegin ();

    HDC fon = txLoadImage ("fon.bmp");
    HDC tablo = txLoadImage ("tablo.bmp");

    FILE *res;
    res = fopen ("results.txt", "a");

    int x = 100; int y = 100; int x1 = 200; int y1 = 200;
    double sizeX = 0.3; double sizeY = 0.3;
    double sizeX1 = 0.2; double sizeY1 = 0.2;
    int score = 0;

    int vx = 5; int vy = 5; int vx1 = 3; int vy1 = 5;
    int ax = 0; int ay = 1; int ax1 = 0; int ay1 = 1;
    int dt = 1; int dt1 = 2;

    int leftborder = 10; int rightborder = 790;
    int upborder = 10; int downborder = 590;

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txBitBlt (txDC (), 0, 0, 800, 600, fon,   0, 0);
        txBitBlt (txDC (), 700, 0, 100, 50, tablo, 0, 0);
        PrintTablo (score, 730, 10);

        DrawStar (x, y, sizeX, sizeY, TX_WHITE, TX_LIGHTGREEN);
        txLine (x, y, x + vx, y + vy);
        DrawStar (x1, y1, sizeX1, sizeY1, TX_WHITE, TX_LIGHTRED);
        txLine (x1, y1, x1 + vx1, y1 + vy1);
        txSleep (20);

        DrawStar (x, y, sizeX, sizeY, TX_BLACK, TX_BLACK);
        txLine (x, y, x + vx, y + vy);
        DrawStar (x1, y1, sizeX1, sizeY1, TX_BLACK, TX_BLACK);
        txLine (x1, y1, x1 + vx1, y1 + vy1);

        Move (&x, &y, sizeX, sizeY, &vx, &vy, ax, ay, dt,
              leftborder, rightborder, upborder, downborder);
        Move (&x1, &y1, sizeX1, sizeY1, &vx1, &vy1, ax1, ay1, dt1,
              leftborder, rightborder, upborder, downborder);

        score = ControlScore (score, x, y, x1, y1, sizeX, sizeX1);

        CollisionTrajectory (x, y, x1, y1, sizeX, sizeX1, &vx, &vx1);

        Management (&vx, &vy);
        }

    txDeleteDC (fon);
    txDeleteDC (tablo);
    fprintf(res, "%d\n", score);
    fclose (res);
    txEnd ();
    }

//-----------------------------------------------------------------------------

void Description ()
    {
    HDC fon = txLoadImage ("fon.bmp");
    txPlaySound ("begin.wav");

    while (! txGetAsyncKeyState (VK_SPACE))
        {
        txBitBlt (txDC (), 0, 0, 800, 600, fon, 0, 0);
        DrawStar (550, 120, 0.2, 0.2, TX_WHITE, TX_ORANGE);
        txSelectFont   ("Times", 50);
        txSetColor     (TX_WHITE);
        txSetFillColor (TX_WHITE);
        txTextOut (250, 100, "Поймай звезду");
        txSelectFont   ("Times", 30);
        txTextOut (100, 160, "Краткое описание игры:");
        txTextOut (100, 200, "Тебе нужно продержаться как можно дольше и");
        txTextOut (100, 240, "не набрать 1000 очков");
        txTextOut (100, 280, "За каждое столкновение со звездой -20 очков");
        txTextOut (100, 320, "Управление:");
        txTextOut (100, 360, "стрелки - изменить траекторию");
        txTextOut (100, 400, "пробел - уронить звезду");
        txTextOut (100, 440, "ESC - закончить игру");
        txTextOut (100, 520, "       Для начала игры нажми пробел...");
        txSleep (50);
        }

    txDeleteDC (fon);
    txPlaySound ();
    }
