#include <stdio.h>
#include <stdlib.h>
#include <pdcurses.h> //console
#include <unistd.h>   //usleep

int main()
{
    /***PRE-GAME*******************************************************************************/

    /**VARIABLES**/
    /*Main Var*/
    const int ysz = 15, xsz = 48; // size of playing field
    int c;                        // input var for ASCII
    int bb = 0;                   // counter for number of live cells nearby
    char vch = '-';

    // /*Files*/
    // FILE *act_file;
    // int nmbr_of_fls = 2; // number of files with coordinates
    // int choice;          // var for working with files
    // char line[254];      // writing line from file

    /*Arrays Of Chars*/
    char marr[ysz][xsz];  // main array
    char bfarr[ysz][xsz]; // buffer array
    struct crds           // struct for working with 2-dimensions var
    {
        int y, x;
    };
    // int *nmbr_cells[5];

    /*Init a block of check*/
    struct crds bk_ck;

    /**PDCURSES**/
    /*Init Screen*/
    initscr();   // init main screen(console)
    curs_set(0); // hide cursor
    noecho();    // no enter effect

    /*Color Mode*/
    start_color();                          // init color mode
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // create color pair
    bkgd(COLOR_PAIR(1));                    // color background pair

    /***GAME**************************************************************************************/
    // /*Init cells*/
    // while (true)
    // {
    //     printf("Enter correct number of file[1-3]:");
    //     scanf("%d", &choice);
    //     if (choice <= nmbr_of_fls - nmbr_of_fls || choice > nmbr_of_fls)
    //     {
    //         continue;
    //     }
    //     if (choice == 1)
    //     {
    //         act_file = fopen("shape_samples/1_static_blinker.txt", "r");
    //         while (fgets(line, 254, act_file))
    //         {
    //             printf("%s", line);
    //         }
    //         fclose(act_file);
    //         break;
    //     }
    //     if (choice == 2)
    //     {
    //         act_file = fopen("shape_samples/2_move_arrow.txt", "r");
    //         while (fgets(line, 254, act_file))
    //         {
    //             printf("%s", line);
    //         }
    //         fclose(act_file);
    //         break;
    //     }
    // }
    // for (int i = 0; i < 5; i++)
    // {
    //     nmbr_cells[i] = crds[i];
    // }

    /*Entering Arrays Of Chars*/
    for (int i = (ysz - ysz); i < ysz; i++)
    {
        for (int j = (xsz - xsz); j < xsz; j++)
        {
            marr[i][j] = vch;
            bfarr[i][j] = vch;
        }
    }

    /*Init cells and a block of check*/
    struct crds cl_1;
    struct crds cl_2;
    struct crds cl_3;
    struct crds cl_4;
    struct crds cl_5;

    /*Cords of cells*/
    cl_1.y = 7;
    cl_1.x = 24;
    marr[cl_1.y][cl_1.x] = 'O';

    cl_2.y = 8;
    cl_2.x = 25;
    marr[cl_2.y][cl_2.x] = 'O';

    cl_3.y = 9;
    cl_3.x = 25;
    marr[cl_3.y][cl_3.x] = 'O';

    cl_4.y = 9;
    cl_4.x = 24;
    marr[cl_4.y][cl_4.x] = 'O';

    cl_5.y = 9;
    cl_5.x = 23;
    marr[cl_5.y][cl_5.x] = 'O';

    /***MAIN GAME CYCLE**************************************************************************************/
    while ((c = getch()) != 27 && c == 32)
    {
        clear();
        /*The Cycle Of Searching For Places For New Life*/
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
                    }
                    bk_ck.y = i;
                    bk_ck.x = j;
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
                    }
                    bk_ck.y = i;
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
                    }
                    bk_ck.y = i;
                    bk_ck.x = j;
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
                    }
                    bk_ck.x = j;
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
                    bk_ck.x = j;
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
                    }
                    bk_ck.y = i;
                    bk_ck.x = j;
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
                    }
                    bk_ck.y = i;
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
                    }
                    bk_ck.y = i;
                    bk_ck.x = j;
                }
                else
                {
                    if (marr[bk_ck.y + 1][bk_ck.x + 1] == 'O')
                    {
                        bb++;
                    }
                }
                ////////////////////////////////////////////////////////////////
                // if ((i + 1) >= ysz && j < xsz)
                // {
                //     bk_ck.y = ysz - ysz;
                //     bk_ck.x = j - 1;
                //     if (marr[bk_ck.y][bk_ck.x] == 'O')
                //     {
                //         bb++;
                //     }
                //     bk_ck.x = j + 1;
                //     if (marr[bk_ck.y][bk_ck.x] == 'O')
                //     {
                //         bb++;
                //     }
                //     bk_ck.y = i;
                //     bk_ck.x = j;
                // }
                // if ((i - 1) < ysz - ysz && j < xsz)
                // {
                //     bk_ck.y = ysz - 1;
                //     bk_ck.x = j - 1;
                //     if (marr[bk_ck.y][bk_ck.x] == 'O')
                //     {
                //         bb++;
                //     }
                //     bk_ck.x = j + 1;
                //     if (marr[bk_ck.y][bk_ck.x] == 'O')
                //     {
                //         bb++;
                //     }
                //     bk_ck.y = i;
                //     bk_ck.x = j;
                // }
                //  if (j - 1 < xsz - xsz && i < ysz)
                // {
                //     bk_ck.y = i - 1;
                //     bk_ck.x = xsz - 1;
                //     if (marr[bk_ck.y][bk_ck.x] == 'O')
                //     {
                //         bb++;
                //     }
                //     bk_ck.y = i + 1;
                //     if (marr[bk_ck.y][bk_ck.x] == 'O')
                //     {
                //         bb++;
                //     }
                //     bk_ck.y = i;
                //     bk_ck.x = j;
                // }
                // if (j + 1 >= xsz && i < ysz)
                // {
                //     bk_ck.y = i - 1;
                //     bk_ck.x = xsz - xsz;
                //     if (marr[bk_ck.y][bk_ck.x] == 'O')
                //     {
                //         bb++;
                //     }
                //     bk_ck.y = i + 1;
                //     if (marr[bk_ck.y][bk_ck.x] == 'O')
                //     {
                //         bb++;
                //     }
                //     bk_ck.y = i;
                //     bk_ck.x = j;
                // }
                // //////////////////////////////////////////////////////////
                /*if around ' ' 3 bb -> 'O'*/
                if (marr[i][j] == vch)
                {
                    if (bb == 3)
                    {
                        bfarr[i][j] = 'O';
                    }
                    else
                    {
                        bfarr[i][j] = vch;
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
                        bfarr[i][j] = vch;
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
