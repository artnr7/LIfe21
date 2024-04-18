#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //локализация
#include <pdcurses.h>
#include <windows.h>

int main()
{
    setlocale(LC_ALL, "Rus"); // поддержка кириллицы в терминале
    system("chcp 65001");     // переключаем шрифт для отображения кириллицы

    /**/
    int y = 24;
    int x = 79;
    int c; // input
    struct cell
    {
        int y;
        int x;
    };

    /**/                                    //
    initscr();                              //
    keypad(stdscr, TRUE);                   //
    curs_set(0);                            // hide cursor
    noecho();                               // no input effect
    /**/                                    //
    cbreak();                               //
    nodelay(stdscr, TRUE);                  //
    /**/                                    //
    start_color();                          // запускаем цветной режим
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // режим цветов
    bkgd(COLOR_PAIR(1));                    // цвет фона, режим 1

    struct cell first;
    struct cell second;
    struct cell third;
    while ((c = getch()) != 27)
    {
        if (c == 32)
        {
            first.y = y / 2;
            first.x = x / 2;
            mvaddch(first.y, first.x, 'O');
            second.y = first.y + 1;
            second.x = x / 2;
            mvaddch(second.y, first.x, 'O');
            third.y = first.y + 2;
            third.x = x / 2;
            mvaddch(third.y, first.x, 'O');
        }
    }
    endwin();

    return 0;
}