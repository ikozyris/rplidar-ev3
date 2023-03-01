#include <ncurses.h>

#define ROW 9
#define COL 10

int main(void) {
    int y, x, i, j,ch;
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
                attron(A_BOLD);
                //printw("%d ", grid[i][j]);
                printw("X ");
                attroff(A_BOLD);
            }
            else
                //printw("%d ", grid[i][j]);
                printw("  ");
        }
        printw("\n");
    }
    getyx(stdscr,y,x);
    while(1) {
        ch = getch();        
        switch(ch)  {
            case KEY_DOWN:
                y=y+1;
                wmove(stdscr,y, x);
                break;
            case KEY_UP:
                y=y-1;
                wmove(stdscr,y, x);
                break;
            case KEY_LEFT:
                x=x-1;
                wmove(stdscr,y, x);
                break;
            case KEY_RIGHT:
                x=x+1;
                wmove(stdscr,y, x);
                break;
            case 10:
                getyx(stdscr,y,x);
                FILE *fp;
                fp = fopen("y-x", "w");
                fprintf(fp,"%d %d", y, x/2);
                fclose(fp);
                break;
            case 'q':
                endwin();
                return 0;
        }
    }
    refresh();
    endwin();
}