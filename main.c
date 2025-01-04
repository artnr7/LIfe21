#include <stdio.h>
#include <stdlib.h>
#include <pdcurses.h> //console
#include <unistd.h>   //usleep

void change(char *arr[], int *prty, char *orr, char *err)
{
    if (*prty == 1)
    {
        arr = err;
        *prty = 2;
    }
    else if (*prty == 2)
    {
        arr = orr;
        *prty = 1;
    }
}

int main()
{
    /***PRE-GAME*******************************************************************************/

    /**VARIABLES**/
    /*Main Vars*/
    const int ysz = 25, xsz = 80;                 // size of playing field
    const int yarrsz = ysz + 2, xarrsz = xsz + 2; // arrays size
    int c;                                        // input var for ASCII
    int bb = 0;                                   // counter for number of live cells nearby
    char sch = '.';                               // space char

    /*Arrays Of Chars*/
    char orr[yarrsz][xarrsz]; // odd array
    char err[yarrsz][xarrsz]; // even array
    char(*arr)[yarrsz] = orr; // реализация с безымянными периодическими массивами
    int prty = 1;             // четность - нечетность
    struct crds               // struct for working with 2-dimensions var
    {
        int y, x;
    };

    /**FILES**/
    /*File vars*/
    FILE *act_file;
    int nmb_of_fls = 3; // number of files with coordinates
    int choice;         // var for working with files
    int nmb_of_cls;

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

    /**PDCURSES**/
    /*Init Screen*/
    initscr();   // init main screen(console)
    curs_set(0); // hide cursor
    noecho();    // no enter effect

    /*Color Mode*/
    start_color();                          // init color mode
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // create color pair
    bkgd(COLOR_PAIR(1));                    // color background pair

    /*Entering Arrays Of Chars*/
    for (int i = 0; i < yarrsz; i++)
    {
        for (int j = 0; j < xarrsz; j++)
        {
            orr[i][j] = sch;
            err[i][j] = sch;
        }
    }

    /*Cords of cells*/
    for (int i = 0; i < nmb_of_cls; i++)
    {
        arr[cell[i].y][cell[i].x] = 'O';
    }

    /***GAME*************************************************************************************************/
    /***MAIN GAME CYCLE**************************************************************************************/
    do
    {
        clear(); // clearing the screen
        /*entering array edges*/
        for (int i = 1; i < xarrsz - 1; i++)
        {
            arr[0][i] = arr[yarrsz - 2][i];
            arr[yarrsz - 1][i] = arr[1][i];
        }
        for (int i = 1; i < yarrsz - 1; i++)
        {
            arr[i][0] = arr[i][xarrsz - 2];
            arr[i][xarrsz - 1] = arr[i][1];
        }
        arr[0][0] = arr[yarrsz - 2][xarrsz - 2];
        arr[0][xarrsz - 1] = arr[yarrsz - 2][1];
        arr[yarrsz - 1][0] = arr[1][xarrsz - 2];
        arr[yarrsz - 1][xarrsz - 1] = arr[1][1];

        /*The Main Cycle Of Searching For Places For New Life*/
        for (int i = 1; i < yarrsz - 1; i++)
        {
            for (int j = 1; j < xarrsz - 1; j++)
            {
                mvprintw(i - 1, j - 1, "%c", arr[i][j]);
                if (arr[i - 1][j - 1] == 'O') /*top left*/
                {
                    bb++;
                }
                if (arr[i - 1][j] == 'O') /*top center*/
                {
                    bb++;
                }
                if (arr[i - 1][j + 1] == 'O') /*top right*/
                {
                    bb++;
                }
                if (arr[i][j - 1] == 'O') /*mid left*/
                {
                    bb++;
                }
                if (arr[i][j + 1] == 'O') /*mid right*/
                {
                    bb++;
                }
                if (arr[i + 1][j - 1] == 'O') /*bot left*/
                {
                    bb++;
                }
                if (arr[i + 1][j] == 'O') /*bot center*/
                {
                    bb++;
                }
                if (arr[i + 1][j + 1] == 'O') /*bot right*/
                {
                    bb++;
                }
                /*if around ' ' 3 bb -> 'O'*/
                if (arr[i][j] == sch)
                {
                    change(arr, &prty, orr, err);
                    if (bb == 3)
                    {
                        arr[i][j] = 'O';
                    }
                    else
                    {
                        arr[i][j] = sch;
                    }
                    change(arr, &prty, orr, err);
                }
                /*if around 'O' 2 or 3 bb -> 'O' else ' '*/
                else if (arr[i][j] == 'O')
                {
                    change(arr, &prty, orr, err);
                    if (bb == 2 || bb == 3)
                    {
                        arr[i][j] = 'O';
                    }
                    if (bb < 2 || bb > 3)
                    {
                        arr[i][j] = sch;
                    }
                    change(arr, &prty, orr, err);
                }
                bb = 0;
            }
        }
        change(arr, &prty, orr, err);
    } while ((c = getch()) != 27 && c == 32);
    endwin();

    return 0;
}
