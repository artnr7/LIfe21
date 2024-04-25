#include <stdio.h>
#include <stdlib.h>
#include <pdcurses.h> //console
#include <unistd.h>   //usleep

int main()
{
    /***PRE-GAME*******************************************************************************/

    /**VARIABLES**/
    /*Main Var*/
    const int ysz = 25, xsz = 80;                 // size of playing field
    const int yarrsz = ysz + 2, xarrsz = xsz + 2; // arrays size
    int c;                                        // input var for ASCII
    int bb = 0;                                   // counter for number of live cells nearby
    char vch = ' ';                               // char space

    // /*Files*/
    // FILE *act_file;
    // int nmbr_of_fls = 2; // number of files with coordinates
    // int choice;          // var for working with files
    // char line[254];      // writing line from file

    /*Arrays Of Chars*/

    char marr[yarrsz][xarrsz];  // main array
    char bfarr[yarrsz][xarrsz]; // buffer array
    struct crds                 // struct for working with 2-dimensions var
    {
        int y, x;
    };
    // int *nmbr_cells[5];

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

    /*Init cells*/
    struct crds cl_1;
    struct crds cl_2;
    struct crds cl_3;
    struct crds cl_4;
    struct crds cl_5;

    /*Entering Arrays Of Chars*/
    for (int i = 0; i < yarrsz; i++)
    {
        for (int j = 0; j < xarrsz; j++)
        {
            marr[i][j] = vch;
            bfarr[i][j] = vch;
        }
    }

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
    do
    {
        clear();
        for (int i = 1; i < xarrsz - 1; i++)
        {
            marr[0][i] = marr[yarrsz - 2][i];
            bfarr[0][i] = bfarr[yarrsz - 2][i];
            marr[yarrsz - 1][i] = marr[1][i];
            bfarr[yarrsz - 1][i] = bfarr[1][i];
        }
        for (int i = 1; i < yarrsz - 1; i++)
        {
            marr[i][0] = marr[i][xarrsz - 2];
            bfarr[i][0] = bfarr[i][xarrsz - 2];
            marr[i][xarrsz - 1] = marr[i][1];
            bfarr[i][xarrsz - 1] = bfarr[i][1];
        }
        marr[0][0] = marr[yarrsz - 2][xarrsz - 2];
        bfarr[0][0] = bfarr[yarrsz - 2][xarrsz - 2];
        marr[0][xarrsz - 1] = marr[yarrsz - 2][1];
        bfarr[0][xarrsz - 1] = bfarr[yarrsz - 2][1];
        marr[yarrsz - 1][0] = marr[1][xarrsz - 2];
        bfarr[yarrsz - 1][0] = bfarr[1][xarrsz - 2];
        marr[yarrsz - 1][xarrsz - 1] = marr[1][1];
        bfarr[yarrsz - 1][xarrsz - 1] = bfarr[1][1];

        /*The Cycle Of Searching For Places For New Life*/
        for (int i = 1; i < yarrsz - 1; i++)
        {
            for (int j = 1; j < xarrsz - 1; j++)
            {
                mvprintw(i - 1, j - 1, "%c", marr[i][j]);
                if (marr[i - 1][j - 1] == 'O') /*top left*/
                {
                    bb++;
                }
                if (marr[i - 1][j] == 'O') /*top center*/
                {
                    bb++;
                }
                if (marr[i - 1][j + 1] == 'O') /*top right*/
                {
                    bb++;
                }
                if (marr[i][j - 1] == 'O') /*mid left*/
                {
                    bb++;
                }
                if (marr[i][j + 1] == 'O') /*mid right*/
                {
                    bb++;
                }
                if (marr[i + 1][j - 1] == 'O') /*bot left*/
                {
                    bb++;
                }
                if (marr[i + 1][j] == 'O') /*bot center*/
                {
                    bb++;
                }
                if (marr[i + 1][j + 1] == 'O') /*bot right*/
                {
                    bb++;
                }
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
                    if (bb < 2 || bb > 3)
                    {
                        bfarr[i][j] = vch;
                    }
                }
                bb = 0;
            }
        }

        for (int i = 1; i < yarrsz - 1; i++)
        {
            for (int j = 1; j < xarrsz - 1; j++)
            {
                marr[i][j] = bfarr[i][j];
            }
        }
    } while ((c = getch()) != 27 && c == 32);
    endwin();

    return 0;
}
