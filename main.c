#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //локализация
#include <pdcurses.h>
#include <windows.h>

int main()
{
    setlocale(LC_ALL, "Rus"); // поддержка кириллицы в терминале
    system("chcp 65001");     // переключаем шрифт для отображения кириллицы

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

    while (1)
    {
        getch();
    }
    endwin();

    return 0;
}