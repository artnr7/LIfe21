#include <stdio.h>
#include <stdlib.h>
#include <pdcurses.h> //
#include <unistd.h>   //usleep

int main()
{
    /*Variables*/
    const int ysz = 25, xsz = 80; // size of playing field
    int c;                        // input ASCII var
    int bb = 0;                   // counter for number of cells nearby
    /*Arrays of chars*/
    char marr[ysz][xsz];  // main array
    char bfarr[ysz][xsz]; // buffer array
    struct crds
    {
        int y, x;
    };

    /*Init screen*/
    initscr();   // init main screen(console)
    curs_set(0); // hide cursor
    noecho();    // no input effect

    /*Color mode*/
    start_color();                          // init color mode
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // init color pair
    bkgd(COLOR_PAIR(1));                    // color background pair

    /**************************************************************************************************/
    /*Init cells and a block of check*/
    struct crds cl_1;
    struct crds cl_2;
    struct crds cl_3;
    struct crds cl_4;
    struct crds bk_ck;

    /*Init arrays of chars*/
    for (int i = (ysz - ysz); i < ysz; i++)
    {
        for (int j = (xsz - xsz); j < xsz; j++)
        {
            marr[i][j] = ' ';
            bfarr[i][j] = ' ';
        }
    }

    /*Cords of cells*/
    cl_1.y = ysz / 2;
    cl_1.x = xsz / 2;
    marr[cl_1.y][cl_1.x] = 'O';

    cl_2.y = cl_1.y + 1;
    cl_2.x = xsz / 2;
    marr[cl_2.y][cl_2.x] = 'O';

    cl_3.y = cl_1.y + 2;
    cl_3.x = xsz / 2;
    marr[cl_3.y][cl_3.x] = 'O';

    cl_4.y = cl_1.y + 2;
    cl_4.x = (xsz / 2) + 1;
    marr[cl_4.y][cl_4.x] = 'O';

    while ((c = getch()) != 27 && c == 32)
    {
        clear();
        /*The cycle of searching for places for new life*/
        for (int i = (ysz - ysz); i < ysz; i++)
        {
            for (int j = (xsz - xsz); j < xsz; j++)
            {
                mvprintw(i, j, "%c", marr[i][j]);
                bk_ck.y = i;
                bk_ck.x = j;
                /*checks for implementation of closed field*/
                /*TOP*/
                if ((i - 1) < (ysz - ysz) && (j - 1) < (xsz - xsz)) /*top left*/
                {
                    bk_ck.y = ysz - 1;
                    bk_ck.x = xsz - 1;
                    if (marr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                        bk_ck.x = j;
                    }
                }
                else
                {
                    if (marr[bk_ck.y - 1][bk_ck.x - 1] == 'O')
                    {
                        bb++;
                    }
                }
                if ((i - 1) < (ysz - ysz)) /*top center*/
                {
                    bk_ck.y = ysz - 1;
                    if (marr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                    }
                }
                else
                {
                    if (marr[bk_ck.y - 1][bk_ck.x] == 'O')
                    {
                        bb++;
                    }
                }
                if ((i - 1) < (ysz - ysz) && (j + 1) >= xsz) /*top right*/
                {
                    bk_ck.y = ysz - 1;
                    bk_ck.x = xsz - xsz;
                    if (marr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                        bk_ck.x = j;
                    }
                }
                else
                {
                    if (marr[bk_ck.y - 1][bk_ck.x + 1] == 'O')
                    {
                        bb++;
                    }
                }
                /*MID*/
                if ((j - 1) < (xsz - xsz)) /*mid left*/
                {
                    bk_ck.x = xsz - 1;
                    if (marr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.x = j;
                    }
                }
                else
                {
                    if (marr[bk_ck.y][bk_ck.x - 1] == 'O')
                    {
                        bb++;
                    }
                }
                if ((j + 1) >= xsz) /*mid right*/
                {
                    bk_ck.x = xsz - xsz;
                    if (marr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                    }
                }
                else
                {
                    if (marr[bk_ck.y][bk_ck.x + 1] == 'O')
                    {
                        bb++;
                    }
                }
                /*BOT*/
                if ((i + 1) >= ysz && (j - 1) < (xsz - xsz)) /*bot left*/
                {
                    bk_ck.y = ysz - ysz;
                    bk_ck.x = xsz - 1;
                    if (marr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                        bk_ck.x = j;
                    }
                }
                else
                {
                    if (marr[bk_ck.y + 1][bk_ck.x - 1] == 'O')
                    {
                        bb++;
                    }
                }
                if ((i + 1) >= ysz) /*bot center*/
                {
                    bk_ck.y = ysz - ysz;
                    if (marr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                    }
                }
                else
                {
                    if (marr[bk_ck.y + 1][bk_ck.x] == 'O')
                    {
                        bb++;
                    }
                }
                if ((i + 1) >= ysz && (j + 1) >= xsz) /*bot right*/
                {
                    bk_ck.y = ysz - ysz;
                    bk_ck.x = xsz - xsz;
                    if (marr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                        bk_ck.x = j;
                    }
                }
                else
                {
                    if (marr[bk_ck.y + 1][bk_ck.x + 1] == 'O')
                    {
                        bb++;
                    }
                }
                /*if around ' ' 3 bb -> 'O'*/
                if (marr[i][j] == ' ')
                {
                    if (bb == 3)
                    {
                        bfarr[i][j] = 'O';
                    }
                    else
                    {
                        bfarr[i][j] = ' ';
                    }
                }
                /*if around 'O' 2 or 3 bb -> 'O' else ' '*/
                else if (marr[i][j] == 'O')
                {
                    if (bb == 2 || bb == 3)
                    {
                        bfarr[i][j] = 'O';
                    }
                    else if (bb < 2 || bb > 3)
                    {
                        bfarr[i][j] = ' ';
                    }
                }
                bb = 0;
            }
        }

        for (int i = (ysz - ysz); i < ysz; i++)
        {
            for (int j = (xsz - xsz); j < xsz; j++)
            {
                marr[i][j] = bfarr[i][j];
            }
        }
    }
    endwin();

    return 0;
}
// if (i >= ysz - ysz && i < ysz && j >= xsz - xsz && j < xsz)