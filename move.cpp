#include "TxLib.h"
#include "stdio.h"

struct Star
    {
    int x, y;
    double sizeX, sizeY;
    };

struct Border
    {
    int leftborder, rightborder, upborder, downborder;
    };

struct Speed
    {
    int vx, vy, ax, ay, dt;
    };

void DrawStar (struct Star star, COLORREF frame, COLORREF fill);

void Move (struct Star* star, struct Speed* speed, struct Border border);

void Management (int* vx, int* vy);

void StarMoveManagement ();

double Distance (int x, int y, int x1, int y1);

bool ControlCollision (int x, int y, int x1, int y1, double sizeX, double sizeX1);

void CollisionTrajectory ();

int ControlScore (int score, int x, int y, int x1, int y1, double sizeX, double sizeX1);

void PrintTablo (int score, int x, int y);

void Description ();

//-----------------------------------------------------------------------------

int main (void)
    {
    txCreateWindow (800, 600);

    Description ();

    StarMoveManagement ();

    return 0;
    }

//-----------------------------------------------------------------------------

void DrawStar (struct Star star, COLORREF frame, COLORREF fill)
    {
    txSetColor (frame, 2);
    txSetFillColor (fill);

    POINT zvezda [] = {{star.x                   , star.y - 164 * star.sizeY},
                       {star.x +  34 * star.sizeX, star.y -  52 * star.sizeY},
                       {star.x + 150 * star.sizeX, star.y -  50 * star.sizeY},
                       {star.x +  59 * star.sizeX, star.y +  17 * star.sizeY},
                       {star.x +  92 * star.sizeX, star.y + 131 * star.sizeY},
                       {star.x                   , star.y +  65 * star.sizeY},
                       {star.x -  92 * star.sizeX, star.y + 131 * star.sizeY},
                       {star.x -  59 * star.sizeX, star.y +  17 * star.sizeY},
                       {star.x - 150 * star.sizeX, star.y -  50 * star.sizeY},
                       {star.x -  34 * star.sizeX, star.y -  52 * star.sizeY},
                       {star.x                   , star.y - 164 * star.sizeY}};
    txPolygon (zvezda, 11);
    }

//-----------------------------------------------------------------------------

void Move (struct Star* star, struct Speed* speed, struct Border border)
    {
    speed -> vx = speed -> vx + speed -> ax * speed -> dt;
    speed -> vy = speed -> vy + speed -> ay * speed -> dt;

    star -> x += (speed -> vx) * speed -> dt;
    star -> y += (speed -> vy) * speed -> dt;

    if (star -> x > border.rightborder - 165 * star -> sizeX)
        {
        txPlaySound ("ball.wav");
        speed -> vx = - (speed -> vx);
        star -> x = border.rightborder - 165 * star -> sizeX;
        return;
        }

    if (star -> y > border.downborder - 165 * star -> sizeX)
        {
        txPlaySound ("ball.wav");
        speed -> vy = - (speed -> vy);
        star -> y = border.downborder - 165 * star -> sizeX;
        return;
        }

    if (star -> x < border.leftborder + 165 * star -> sizeX)
        {
        txPlaySound ("ball.wav");
        speed -> vx = - (speed -> vx);
        star -> x = border.leftborder + 165 * star -> sizeX;
        return;
        }

    if (star -> y < border.upborder + 165 * star -> sizeX)
        {
        txPlaySound ("ball.wav");
        speed -> vy = - (speed -> vy);
        star -> y = border.upborder + 165 * star -> sizeX;
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

    Star star1 = {100, 100, 0.3, 0.3};
    Star star2 = {200, 200, 0.2, 0.2};

    int score = 0;

    Speed speed1 = {5, 5, 0, 1, 1};
    Speed speed2 = {3, 5, 0, 1, 2};

    Border border = {10, 790, 10, 590};

    while (! txGetAsyncKeyState (VK_ESCAPE))
        {
        txBitBlt (txDC (), 0, 0, 800, 600, fon,   0, 0);
        txBitBlt (txDC (), 700, 0, 100, 50, tablo, 0, 0);
        PrintTablo (score, 730, 10);

        DrawStar (star1, TX_WHITE, TX_LIGHTGREEN);
        txLine (star1.x, star1.y, star1.x + speed1.vx, star1.y + speed1.vy);
        DrawStar (star2, TX_WHITE, TX_LIGHTRED);
        txLine (star2.x, star2.y, star2.x + speed2.vx, star2.y + speed2.vy);
        txSleep (20);

        DrawStar (star1, TX_BLACK, TX_BLACK);
        txLine (star1.x, star1.y, star1.x + speed1.vx, star1.y + speed1.vy);
        DrawStar (star2, TX_BLACK, TX_BLACK);
        txLine (star2.x, star2.y, star2.x + speed2.vx, star2.y + speed2.vy);

        Move (&star1, &speed1, border);
        Move (&star2, &speed2, border);

        score = ControlScore (score, star1.x, star1.y, star2.x, star2.y,
                              star1.sizeX, star2.sizeX);

        CollisionTrajectory (star1.x, star1.y, star2.x, star2.y,
                             star1.sizeX, star2.sizeX, &speed1.vx, &speed2.vx);

        Management (&speed1.vx, &speed1.vy);
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

    Star star = {550, 120, 0.2, 0.2};

    while (! txGetAsyncKeyState (VK_SPACE))
        {
        txBitBlt (txDC (), 0, 0, 800, 600, fon, 0, 0);
        DrawStar (star, TX_WHITE, TX_ORANGE);
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

//-----------------------------------------------------------------------------

