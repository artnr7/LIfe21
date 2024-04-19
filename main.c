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
    int tmblr = 0;                // switching between odd and even frames

    struct crds
    {
        int y;
        int x;
    };

    /*Init screen*/
    initscr();            // init main screen(console)
    keypad(stdscr, TRUE); // keypad mode on
    curs_set(0);          // hide cursor
    noecho();             // no input effect

    /*Nodelay mode*/
    // cbreak();              //
    // nodelay(stdscr, TRUE); //

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
    char crdarr[ysz][xsz];  // odd [1st] frame
    char mcrdarr[ysz][xsz]; // even [2nd] frame
    for (int i = (ysz - ysz); i < ysz; i++)
    {
        for (int j = (xsz - xsz); j < xsz; j++)
        {
            crdarr[i][j] = '-';
            mcrdarr[i][j] = '-';
        }
    }

    /*Cords of cells*/
    cl_1.y = ysz / 2;
    cl_1.x = xsz / 2;
    crdarr[cl_1.y][cl_1.x] = 'O';

    cl_2.y = cl_1.y + 1;
    cl_2.x = xsz / 2;
    crdarr[cl_2.y][cl_2.x] = 'O';

    cl_3.y = cl_1.y + 2;
    cl_3.x = xsz / 2;
    crdarr[cl_3.y][cl_3.x] = 'O';

    // cl_4.y = cl_1.y + 2;
    // cl_4.x = (xsz / 2) + 1;
    // crdarr[cl_4.y][cl_4.x] = 'O';

    while ((c = getch()) != 27 && c == 32)
    {
        clear();

        /*The cycle of searching for places for new life*/
        for (int i = (ysz - ysz); i < ysz; i++)
        {
            for (int j = (xsz - xsz); j < xsz; j++)
            {
                if (tmblr == 0)
                {
                    mvprintw(i, j, "%c", crdarr[i][j]);
                    /*if around ' ' 3 bb -> 'O'*/
                    if (crdarr[i][j] == '-')
                    {
                        /*checks for implementation of closed field*/
                        if ((i - 1) < 0)
                        {
                            bk_ck.y = ysz;
                        }

                        if ((i - 1) < 0 && (j - 1) < (xsz - xsz))
                        {
                            bk_ck.y = ysz;
                            bk_ck.x = xsz;
                        }
                        if ((i - 1) < 0 && (j + 1) > xsz)
                        {
                            bk_ck.y = ysz;
                            bk_ck.x = xsz;
                        }
                        if ((j - 1) < (xsz - xsz))
                        {
                            bk_ck.x = xsz;
                        }
                        if ((j + 1) > (xsz - 1))
                        {
                            bk_ck.x = xsz - xsz;
                        }

                        if ((i + 1) > (ysz - 1))
                        {
                            bk_ck.y = ysz - ysz;
                            if (crdarr[bk_ck.y][bk_ck.x] == 'O')
                            {
                                bb++;
                            }
                        }
                        if ((i + 1) > (ysz - 1))
                        {
                            bk_ck.y = ysz - ysz;
                            if (crdarr[bk_ck.y][bk_ck.x] == 'O')
                            {
                                bb++;
                            }
                        }
                        if ((j - 1) < (xsz - xsz))
                        {
                            bk_ck.x = xsz;
                            if (crdarr[bk_ck.y][bk_ck.x] == 'O')
                            {
                                bb++;
                            }
                        }
                        else if ((j + 1) > (xsz - 1))
                        {
                            bk_ck.x = xsz - xsz;
                            if (crdarr[bk_ck.y][bk_ck.x] == 'O')
                            {
                                bb++;
                            }
                        }
                    }
                    bk_ck.y = i;
                    bk_ck.x = j;

                    /*TOP*/
                    if (crdarr[bk_ck.y - 1][bk_ck.x - 1] == 'O') /*left top*/
                    {
                        bb++;
                    }
                    if (crdarr[bk_ck.y - 1][bk_ck.x] == 'O') /*center top*/
                    {
                        bb++;
                    }
                    if (crdarr[bk_ck.y - 1][bk_ck.x + 1] == 'O') /*right top*/
                    {
                        bb++;
                    }

                    /*MID*/
                    if (crdarr[bk_ck.y][bk_ck.x - 1] == 'O') /*left mid*/
                    {
                        bb++;
                    }
                    if (crdarr[bk_ck.y][bk_ck.x + 1] == 'O') /*right mid*/
                    {
                        bb++;
                    }

                    /*BOT*/
                    if (crdarr[bk_ck.y + 1][bk_ck.x - 1] == 'O') /*left bot*/
                    {
                        bb++;
                    }
                    if (crdarr[bk_ck.y + 1][bk_ck.x] == 'O') /*left bot*/
                    {
                        bb++;
                    }
                    if (crdarr[bk_ck.y + 1][bk_ck.x + 1] == 'O') /*right bot*/
                    {
                        bb++;
                    }

                    if (bb > 2)
                    {
                        mcrdarr[bk_ck.y][bk_ck.x] = 'O';
                    }
                    bb = 0;
                }
                /*if around 'O' 2 or 3 bb -> 'O' else ' '*/
                else if (crdarr[i][j] == 'O')
                {
                    /*TOP*/
                    if (crdarr[bk_ck.y - 1][bk_ck.x - 1] == 'O') /*left top*/
                    {
                        bb++;
                    }
                    if (crdarr[bk_ck.y - 1][bk_ck.x] == 'O') /*center top*/
                    {
                        bb++;
                    }
                    if (crdarr[bk_ck.y - 1][bk_ck.x + 1] == 'O') /*right top*/
                    {
                        bb++;
                    }

                    /*MID*/
                    if (crdarr[bk_ck.y][bk_ck.x - 1] == 'O') /*left mid*/
                    {
                        bb++;
                    }
                    if (crdarr[bk_ck.y][bk_ck.x + 1] == 'O') /*right mid*/
                    {
                        bb++;
                    }

                    /*BOT*/
                    if (crdarr[bk_ck.y + 1][bk_ck.x - 1] == 'O') /*left bot*/
                    {
                        bb++;
                    }
                    if (crdarr[bk_ck.y + 1][bk_ck.x] == 'O') /*left bot*/
                    {
                        bb++;
                    }
                    if (crdarr[bk_ck.y + 1][bk_ck.x + 1] == 'O') /*right bot*/
                    {
                        bb++;
                    }

                    if (bb == 2 || bb == 3)
                    {
                        mcrdarr[i][j] = 'O';
                    }
                    else if (bb < 2 || bb > 3)
                    {
                        mcrdarr[i][j] = '-';
                    }
                    bb = 0;
                }
            }
            else if (tmblr == 1)
            {
                mvprintw(i, j, "%c", mcrdarr[i][j]);
                /*if around ' ' 3 bb -> 'O'*/
                if (mcrdarr[i][j] == '-')
                {
                    /*TOP*/
                    if (mcrdarr[bk_ck.y - 1][bk_ck.x - 1] == 'O') /*left top*/
                    {
                        bb++;
                    }
                    if (mcrdarr[bk_ck.y - 1][bk_ck.x] == 'O') /*center top*/
                    {
                        bb++;
                    }
                    if (mcrdarr[bk_ck.y - 1][bk_ck.x + 1] == 'O') /*right top*/
                    {
                        bb++;
                    }

                    /*MID*/
                    if (mcrdarr[bk_ck.y][bk_ck.x - 1] == 'O') /*left mid*/
                    {
                        bb++;
                    }
                    if (mcrdarr[bk_ck.y][bk_ck.x + 1] == 'O') /*right mid*/
                    {
                        bb++;
                    }

                    /*BOT*/
                    if (mcrdarr[bk_ck.y + 1][bk_ck.x - 1] == 'O') /*left bot*/
                    {
                        bb++;
                    }
                    if (mcrdarr[bk_ck.y + 1][bk_ck.x] == 'O') /*left bot*/
                    {
                        bb++;
                    }
                    if (mcrdarr[bk_ck.y + 1][bk_ck.x + 1] == 'O') /*right bot*/
                    {
                        bb++;
                    }

                    if (bb > 2)
                    {
                        crdarr[i][j] = 'O';
                    }
                    bb = 0;
                }
                /*if around 'O' 2 or 3 bb -> 'O' else ' '*/
                else if (mcrdarr[i][j] == 'O')
                {
                    /*TOP*/
                    if (mcrdarr[bk_ck.y - 1][bk_ck.x - 1] == 'O') /*left top*/
                    {
                        bb++;
                    }
                    if (mcrdarr[bk_ck.y - 1][bk_ck.x] == 'O') /*center top*/
                    {
                        bb++;
                    }
                    if (mcrdarr[bk_ck.y - 1][bk_ck.x + 1] == 'O') /*right top*/
                    {
                        bb++;
                    }

                    /*MID*/
                    if (mcrdarr[bk_ck.y][bk_ck.x - 1] == 'O') /*left mid*/
                    {
                        bb++;
                    }
                    if (mcrdarr[bk_ck.y][bk_ck.x + 1] == 'O') /*right mid*/
                    {
                        bb++;
                    }

                    /*BOT*/
                    if (mcrdarr[bk_ck.y + 1][bk_ck.x - 1] == 'O') /*left bot*/
                    {
                        bb++;
                    }
                    if (mcrdarr[bk_ck.y + 1][bk_ck.x] == 'O') /*left bot*/
                    {
                        bb++;
                    }
                    if (mcrdarr[bk_ck.y + 1][bk_ck.x + 1] == 'O') /*right bot*/
                    {
                        bb++;
                    }

                    if (bb == 2 || bb == 3)
                    {
                        crdarr[i][j] = 'O';
                    }
                    else if (bb < 2 || bb > 3)
                    {
                        crdarr[i][j] = '-';
                    }
                    bb = 0;
                }
            }
        }
    }
    // switching between odd and even frames
    if (true)
    {
        if (tmblr == 0)
        {
            tmblr = 1;
            continue;
        }
        else if (tmblr == 1)
        {
            tmblr = 0;
        }
    }
}
endwin();
return 0;
}