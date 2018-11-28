// curses_demo.c
//
// Build hints: gcc -o curses_demo curses_demo.c -lncurses


#include <curses.h>  // required

int r,c;  // current row and column (upper-left is (0,0))

// str_array = {"str1", "str2", ...}
//
void curses_print_page(int start_row, int num_lines, const char **str_array){ // curses_print_page#

    int i;

    clear();
    move(start_row,0);

    for(i=0; i<num_lines; i++){
        printw(str_array[i]);
    }
    refresh();

}


void main(){  

    int i;  char d;

    WINDOW* wnd;

    wnd = initscr();    // curses call to initialize window
//    cbreak();           // curses call to set no waiting for Enter key
//    noecho();           // curses call to set no echoing
//    getmaxyx(wnd,nrows,ncols);  // curses call to find size of window
//    clear();            // curses call to clear screen, send cursor to position (0,0)

//    refresh();  // curses call to implement all changes since last refresh

    const char *foo[] = {
        "foo\n",
        "bartering\n",
    };

   const char *bar[] = {
        "a\n",
        "z\n",
    };

    curses_print_page(1, 2, foo);

    d = getch();    // curses call to input from keyboard

    curses_print_page(1, 2, bar);

    d = getch();    // curses call to input from keyboard

//    r = 0; c = 0;
//
//    while (1)  {
//
//        d = getch();    // curses call to input from keyboard
//        if(d=='q')break;
//
//        draw(d);        // draw the character
//
//    }

//    while(1);

    endwin();  // curses call to restore the original window and leave

}



