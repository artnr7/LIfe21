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
    char sch = ' ';                               // space char

    /*Arrays Of Chars*/
    char marr[yarrsz][xarrsz];  // main array
    char bfarr[yarrsz][xarrsz]; // buffer array
    struct crds                 // struct for working with 2-dimensions var
    {
        int y, x;
    };

    /**Files**/
    FILE *act_file;
    int nmb_of_fls = 3; // number of files with coordinates
    int choice;         // var for working with files
    int nmb_of_cls;

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

    /*Entering Arrays Of Chars*/
    for (int i = 0; i < yarrsz; i++)
    {
        for (int j = 0; j < xarrsz; j++)
        {
            marr[i][j] = sch;
        }
    }

    /*Init cells*/
    while (true)
    {
        printf("\nEnter correct number of file[1-3]:");
        scanf("%d", &choice);
        if (choice <= 0 || choice > nmb_of_fls)
        {
            continue;
        }
        if (choice == 1)
        {
            act_file = fopen("shape_samples/1_static_blinker.txt", "r");
            if (!act_file)
            {
                printf("Error occured while opening file\n");
                return 1;
            }
            fscanf(act_file, "nmb_of_cells %d", &nmb_of_cls);
            fseek(act_file, 0, SEEK_SET);
            break;
        }
        if (choice == 2)
        {
            act_file = fopen("shape_samples/2_move_arrow.txt", "r");
            if (!act_file)
            {
                printf("Error occured while opening file\n");
                return 1;
            }
            fscanf(act_file, "nmb_of_cells %d", &nmb_of_cls);
            fseek(act_file, 0, SEEK_SET);
            break;
        }
        if (choice == 3)
        {
            act_file = fopen("shape_samples/3_static_block.txt", "r");
            if (!act_file)
            {
                printf("Error occured while opening file\n");
                return 1;
            }
            fscanf(act_file, "nmb_of_cells %d", &nmb_of_cls);
            fseek(act_file, 0, SEEK_SET);
            break;
        }
    }
    struct crds cell[nmb_of_cls];
    if (choice == 1)
    {
        fscanf(act_file, "nmb_of_cells %d y %d x %d y %d x %d y %d x %d",
               &nmb_of_cls, &cell[0].y, &cell[0].x, &cell[1].y, &cell[1].x, &cell[2].y, &cell[2].x);
    }
    if (choice == 2)
    {
        fscanf(act_file, "nmb_of_cells %d y %d x %d y %d x %d y %d x %d y %d x %d y %d x %d",
               &nmb_of_cls, &cell[0].y, &cell[0].x, &cell[1].y, &cell[1].x, &cell[2].y, &cell[2].x,
               &cell[3].y, &cell[3].x, &cell[4].y, &cell[4].x);
    }
    if (choice == 3)
    {
        fscanf(act_file, "nmb_of_cells %d y %d x %d y %d x %d y %d x %d",
               &nmb_of_cls, &cell[0].y, &cell[0].x, &cell[1].y, &cell[1].x, &cell[2].y, &cell[2].x);
    }
    fclose(act_file);

    /*Cords of cells*/
    for (int i = 0; i < nmb_of_cls; i++)
    {
        marr[cell[i].y][cell[i].x] = 'O';
    }

    /***MAIN GAME CYCLE**************************************************************************************/
    do
    {
        clear(); // clearing the screen
        /*entering array edges*/
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

        /*The Main Cycle Of Searching For Places For New Life*/
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
                if (marr[i][j] == sch)
                {
                    if (bb == 3)
                    {
                        bfarr[i][j] = 'O';
                    }
                    else
                    {
                        bfarr[i][j] = sch;
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
                        bfarr[i][j] = sch;
                    }
                }
                bb = 0;
            }
        }
        /*copying data from buffer to main array*/
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
