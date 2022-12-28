#include <ncurses.h>

#define ROW 9
#define COL 10

int main(void) {
    int y, x, i, j;
    int maxy,maxx; // to store the maximum rows and columns

    // initialize curses
    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();

    getmaxyx(stdscr,maxy,maxx);

    int grid[ROW][COL] = {{1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
					      {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
					      {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
					      {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
					      {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
					      {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
					      {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
					      {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
					      {1, 1, 1, 0, 0, 0, 1, 0, 0, 1}};
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if(grid[i][j] == 1) {
                attron(A_STANDOUT);
                //printw("%d ", grid[i][j]);
                printw("  ");
                attroff(A_STANDOUT);
            }
            else
                //printw("%d ", grid[i][j]);
                printw("  ");
        }
        printw("    ");
        for (j = 0; j < COL; j++) {
            printw("%d ",grid[i][j]);
        }
        printw("\n");
    }
    refresh();
    getch();
    endwin();
}