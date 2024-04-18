#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //локализация
#include <pdcurses.h>
#include <unistd.h> //usleep

int main()
{
    setlocale(LC_ALL, "Rus"); // поддержка кириллицы в терминале
    system("chcp 65001");     // переключаем шрифт для отображения кириллицы

    /*Variables*/
    const int ysz = 25, xsz = 80; // size of main screen
    int c;                        // input var
    int bb = 0;                   // counter for number of cells nearby
    int tmblr = 0;
    struct crds
    {
        int y;
        int x;
    };

    /*Init screen*/
    initscr();            // init main screen
    keypad(stdscr, TRUE); // keypad mode on
    curs_set(0);          // hide cursor
    noecho();             // no input effect

    /*Nodelay mode*/
    // cbreak();                               //
    // nodelay(stdscr, TRUE);                  //

    /*Color mode*/
    start_color();                          // запускаем цветной режим
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // режим цветов
    bkgd(COLOR_PAIR(1));                    // цвет фона, режим 1

    /*Init cells with cords and a block of check*/
    struct crds cell_1;
    struct crds cell_2;
    struct crds cell_3;
    struct crds blck_chck;

    /*Init array of chars*/
    char crdarr[80][25] = {0};
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            crdarr[i][j] = ' ';
        }
    }

    char mcrdarr[80][25] = {0};
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            mcrdarr[i][j] = ' ';
        }
    }

    /*Cords of cells*/
    cell_1.y = ysz / 2;
    cell_1.x = xsz / 2;
    crdarr[cell_1.y][cell_1.x] = 'O';

    cell_2.y = cell_1.y + 1;
    cell_2.x = xsz / 2;
    crdarr[cell_2.y][cell_2.x] = 'O';

    cell_3.y = cell_1.y + 2;
    cell_3.x = xsz / 2;
    crdarr[cell_3.y][cell_3.x] = 'O';

    blck_chck.y = 0;
    blck_chck.x = 0;

    while ((c = getch()) != 27 && c == 32)
    {
        clear();

        mvaddch(cell_1.y, cell_1.x, 'O');
        mvaddch(cell_2.y, cell_2.x, 'O');
        mvaddch(cell_3.y, cell_3.x, 'O');

        /*The cycle of searching for places for new life*/

        if (tmblr == 0)
        {
            for (int i = 0; i < 25; i++)
            {
                for (int j = 0; j < 80; j++)
                {
                    if (crdarr[i][j] == ' ')
                    {
                        /*TOP*/
                        if (crdarr[i - 1][j - 1] == 'O') /*left top*/
                        {
                            bb++;
                        }
                        else if (crdarr[i - 1][j] == 'O') /*center top*/
                        {
                            bb++;
                        }
                        else if (crdarr[i - 1][j + 1] == 'O') /*right top*/
                        {
                            bb++;
                        }

                        /*MID*/
                        else if (crdarr[i][j - 1] == 'O') /*left mid*/
                        {
                            bb++;
                        }
                        else if (crdarr[i][j + 1] == 'O') /*right mid*/
                        {
                            bb++;
                        }

                        /*BOT*/
                        else if (crdarr[i + 1][j - 1] == 'O') /*left bot*/
                        {
                            bb++;
                        }
                        else if (crdarr[i + 1][j] == 'O') /*left bot*/
                        {
                            bb++;
                        }
                        else if (crdarr[i + 1][j] == 'O') /*right bot*/
                        {
                            bb++;
                        }

                        if (bb > 2)
                        {
                            mcrdarr[i][j] = 'O';
                        }
                        bb = 0;
                    }
                    else if (crdarr[i][j] == 'O')
                    {
                        /*TOP*/
                        if (crdarr[i - 1][j - 1] == ' ') /*left top*/
                        {
                            bb++;
                        }
                        else if (crdarr[i - 1][j] == ' ') /*center top*/
                        {
                            bb++;
                        }
                        else if (crdarr[i - 1][j + 1] == ' ') /*right top*/
                        {
                            bb++;
                        }

                        /*MID*/
                        else if (crdarr[i][j - 1] == ' ') /*left mid*/
                        {
                            bb++;
                        }
                        else if (crdarr[i][j + 1] == ' ') /*right mid*/
                        {
                            bb++;
                        }

                        /*BOT*/
                        else if (crdarr[i + 1][j - 1] == ' ') /*left bot*/
                        {
                            bb++;
                        }
                        else if (crdarr[i + 1][j] == ' ') /*left bot*/
                        {
                            bb++;
                        }
                        else if (crdarr[i + 1][j] == ' ') /*right bot*/
                        {
                            bb++;
                        }

                        if (bb > 1)
                        {
                            mcrdarr[i][j] = 'O';
                        }
                        bb = 0;
                    }
                }
            }
            tmblr = 1;
        }
        else if (tmblr == 1)
        { /*нечетный код*/
        }

        usleep(100000);

        endwin();

        return 0;
    }