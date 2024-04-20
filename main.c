#include <stdio.h>
#include <stdlib.h>
#include <locale.h>   //localisation
#include <pdcurses.h> //
#include <unistd.h>   //usleep

int main()
{
    setlocale(LC_ALL, "Rus"); // сyrillic
    system("chcp 65001");     // сyrillic

    /*Variables*/
    const int ysz = 25, xsz = 80; // size of playing field
    int c;                        // input ASCII var
    int bb = 0;                   // counter for number of cells nearby
    int tmblr = 0;
    /*Arrays of chars*/
    char oddarr[ysz][xsz]; // odd [1st] frame
    char evarr[ysz][xsz];  // even [2nd] frame
    char *parr[ysz];
    char **actarr = parr;
    struct crds
    {
        int y, x;
    };

    /*Init screen*/
    initscr();            // init main screen(console)
    keypad(stdscr, TRUE); // keypad mode on
    curs_set(0);          // hide cursor
    noecho();             // no input effect

    /*Color mode*/
    start_color();                          // init color mode
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // init color pair
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
            oddarr[i][j] = '.';
            evarr[i][j] = '.';
        }
    }
    /*Init arrays of pointers*/
    for (int i = 0; i < ysz; i++)
    {
        parr[i] = oddarr[i];
    }
    for (int i = 0; i < ysz; i++)
    {
        parr[i] = evarr[i];
    }

    /*Cords of cells*/
    cl_1.y = ysz / 2;
    cl_1.x = xsz / 2;
    parr[cl_1.y][cl_1.x] = 'O';

    cl_2.y = cl_1.y + 1;
    cl_2.x = xsz / 2;
    parr[cl_2.y][cl_2.x] = 'O';

    cl_3.y = cl_1.y + 2;
    cl_3.x = xsz / 2;
    parr[cl_3.y][cl_3.x] = 'O';

    // cl_4.y = cl_1.y + 2;
    // cl_4.x = (xsz / 2) + 1;
    // parr[cl_4.y][cl_4.x] = 'O';

    while ((c = getch()) != 27 && c == 32)
    {
        clear();
        /*The cycle of searching for places for new life*/
        for (int i = (ysz - ysz); i < ysz; i++)
        {
            for (int j = (xsz - xsz); j < xsz; j++)
            {
                mvprintw(i, j, "%c", parr[i][j]);
                bk_ck.y = i;
                bk_ck.x = j;
                /*checks for implementation of closed field*/
                /*TOP*/
                if ((i - 1) < (ysz - ysz) && (j - 1) < (xsz - xsz)) /*top left*/
                {
                    bk_ck.y = ysz;
                    bk_ck.x = xsz;
                    if (parr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                        bk_ck.x = j;
                    }
                }
                else
                {
                    if (parr[bk_ck.y - 1][bk_ck.x - 1] == 'O')
                    {
                        bb++;
                    }
                }
                if ((i - 1) < (ysz - ysz)) /*top center*/
                {
                    bk_ck.y = ysz;
                    if (parr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                    }
                }
                else
                {
                    if (parr[bk_ck.y - 1][bk_ck.x] == 'O')
                    {
                        bb++;
                    }
                }
                if ((i - 1) < (ysz - ysz) && (j + 1) >= xsz) /*top right*/
                {
                    bk_ck.y = ysz;
                    bk_ck.x = xsz - xsz;
                    if (parr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                        bk_ck.x = j;
                    }
                }
                else
                {
                    if (parr[bk_ck.y - 1][bk_ck.x + 1] == 'O')
                    {
                        bb++;
                    }
                }
                /*MID*/
                if ((j - 1) < (xsz - xsz)) /*mid left*/
                {
                    bk_ck.x = xsz;
                    if (parr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.x = j;
                    }
                }
                else
                {
                    if (parr[bk_ck.y][bk_ck.x - 1] == 'O')
                    {
                        bb++;
                    }
                }
                if ((j + 1) >= xsz) /*mid right*/
                {
                    bk_ck.x = xsz - xsz;
                    if (parr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                    }
                }
                else
                {
                    if (parr[bk_ck.y][bk_ck.x + 1] == 'O')
                    {
                        bb++;
                    }
                }
                /*BOT*/
                if ((i + 1) >= ysz && (j - 1) < (xsz - xsz)) /*bot left*/
                {
                    bk_ck.y = ysz - ysz;
                    bk_ck.x = xsz;
                    if (parr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                        bk_ck.x = j;
                    }
                }
                else
                {
                    if (parr[bk_ck.y + 1][bk_ck.x - 1] == 'O')
                    {
                        bb++;
                    }
                }
                if ((i + 1) >= ysz) /*bot center*/
                {
                    bk_ck.y = ysz - ysz;
                    if (parr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                    }
                }
                else
                {
                    if (parr[bk_ck.y + 1][bk_ck.x] == 'O')
                    {
                        bb++;
                    }
                }
                if ((i + 1) >= ysz && (j + 1) >= xsz) /*bot right*/
                {
                    bk_ck.y = ysz - ysz;
                    bk_ck.x = xsz - xsz;
                    if (parr[bk_ck.y][bk_ck.x] == 'O')
                    {
                        bb++;
                        bk_ck.y = i;
                        bk_ck.x = j;
                    }
                }
                else
                {
                    if (parr[bk_ck.y + 1][bk_ck.x + 1] == 'O')
                    {
                        bb++;
                    }
                }
                /*if around ' ' 3 bb -> 'O'*/
                if (parr[i][j] == '.')
                {
                    if (parr[i] == oddarr[i])
                    {
                        parr[i] = evarr[i];
                    }
                    else
                    {
                        parr[i] = oddarr[i];
                    }
                    if (bb > 2)
                    {
                        parr[i][j] = 'O';
                    }
                    else
                    {
                        parr[i][j] = '.';
                    }
                    if (parr[i] == oddarr[i])
                    {
                        parr[i] = evarr[i];
                    }
                    else
                    {
                        parr[i] = oddarr[i];
                    }
                }
                /*if around 'O' 2 or 3 bb -> 'O' else ' '*/
                else if (parr[i][j] == 'O')
                {
                    if (parr[i] == oddarr[i])
                    {
                        parr[i] = evarr[i];
                    }
                    else
                    {
                        parr[i] = oddarr[i];
                    }
                    if (bb == 2 || bb == 3)
                    {
                        parr[i][j] = 'O';
                    }
                    else if (bb < 2 || bb > 3)
                    {
                        parr[i][j] = '.';
                    }
                    bb = 0;
                    if (parr[i] == oddarr[i])
                    {
                        parr[i] = evarr[i];
                    }
                    else
                    {
                        parr[i] = oddarr[i];
                    }
                }
            }
        }
        if (tmblr == 0)
        {
            for (int i = 0; i < xsz; i++)
            {
                parr[i] = evarr[i];
            }
            tmblr = 1;
            continue;
        }
        else if (tmblr == 1)
        {
            for (int i = 0; i < xsz; i++)
            {
                parr[i] = oddarr[i];
            }
            tmblr = 0;
        }
    }
    endwin();

    return 0;
}

// if (i >= ysz - ysz && i < ysz && j >= xsz - xsz && j < xsz)