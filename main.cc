#include <ncurses.h>

int main() {
    int startx = 0, starty = 1, width = 80, height = 22;
    int ch;
    WINDOW *win;

    initscr();
    cbreak();

    keypad(stdscr, TRUE);

    printw("Press F1 to exit");
    refresh();

    win = newwin(height, width, starty, startx);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);

    while ((ch = getch()) != KEY_F(1)) {
        clear();
        refresh();
        delwin(win);
        win = newwin(++height, ++width, starty, startx);
        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        wrefresh(win);
    }

    endwin();
    return 0;
}