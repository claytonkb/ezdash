// ezdash.c
//

#include "ezdash.h"
#include "cutils.h"
#include <curses.h>
//#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
//unsigned int sleep(unsigned int seconds);

int r,c;  // current row and column (upper-left is (0,0))


//
//
void ezdash_component_B_print(ezdash_env *env, const char *str){

    //don't clear component B
    wprintw(env->B.wnd, str);
    wprintw(env->B.wnd, "\n" );

    touchwin(env->wnd);
    wrefresh(env->B.wnd);

}


// str_array = {"str1", "str2", ...}
//
void ezdash_component_A_update(ezdash_env *env, int start_row, int num_lines, const char **str_array){

    int i;

    ezdash_component comp = env->A;

    wclear(comp.wnd);

    for(i=start_row; i<num_lines && i<comp.dash_height; i++){

        mvwaddnstr(
            comp.wnd,
            comp.y_orig +  i%comp.rows,
            comp.x_orig + (i/comp.rows)*comp.dash_width,
            str_array[i],
            comp.dash_width );

    }

    wrefresh(comp.wnd);

}


//
//
void ezdash_component_A_init(
        ezdash_env *env, 
        int x_orig, int y_orig, 
        int cols,   int rows, 
        int display_cols){

    env->A.enable=1;

    env->A.rows = rows;
    env->A.cols = cols;

    env->A.x_orig=x_orig;
    env->A.y_orig=y_orig;

    env->A.wnd = ezdash_new_win(env->wnd, env->A.rows, env->A.cols, env->A.x_orig, env->A.y_orig);

    env->A.dash_width   = env->A.cols / display_cols;
    env->A.dash_height  = env->A.rows * display_cols;
    env->A.display_cols = display_cols;

}


//
//
void ezdash_component_B_init(
        ezdash_env *env, 
        int x_orig, int y_orig, 
        int cols,   int rows){

    env->B.enable=1;

    env->B.rows = rows;
    env->B.cols = cols;

    env->B.x_orig=x_orig;
    env->B.y_orig=y_orig;

//wprintw(env->A.wnd, "env->B.x_orig: %d", env->B.x_orig);

    env->B.wnd = ezdash_new_win(env->wnd, env->B.rows, env->B.cols, env->B.x_orig, env->B.y_orig);

    scrollok(env->B.wnd, TRUE); // causes printw() to act like printf

}


//
//
ezdash_env *ezdash_init(ezdash_mode mode, 
        float split_A_BC, float split_B_C, float split_A_C,
        int display_cols){

    int i;
//    char d;

//_d(split_A_BC*132);
//_d(24);
//
//_d(split_A_BC*env->term_cols);
//, 0, 
//(1-split_A_BC)*env->term_cols, env->term_rows);
//

    WINDOW* wnd;

    wnd = initscr();    // curses call to initialize window

//    cbreak();           // curses call to set no waiting for Enter key
//    noecho();           // curses call to set no echoing
//    getmaxyx(wnd,nrows,ncols);  // curses call to find size of window
//    clear();            // curses call to clear screen, send cursor to position (0,0)
//    refresh();  // curses call to implement all changes since last refresh
//    scrollok(wnd, TRUE); // causes printw() to act like printf

    ezdash_env *env = malloc(sizeof(ezdash_env));

    env->mode=mode;
    env->wnd=wnd;
    getmaxyx(wnd, env->term_rows, env->term_cols);

    env->update_period=20;

    env->split_A_BC = split_A_BC;
    env->split_B_C  = split_B_C;
    env->split_A_C  = split_A_C;

    switch(mode){

        case EZ_MODE1:

            env->A.enable=1;
            env->B.enable=0;
            env->C.enable=0;

            ezdash_component_A_init(
                env, 
                0, 0, 
                env->term_cols, env->term_rows,
                display_cols);

            break;

        case EZ_MODE2:

            env->A.enable=1;
            env->B.enable=1;
            env->C.enable=0;

            ezdash_component_A_init(
                env, 
                0, 0, 
                split_A_BC*env->term_cols, env->term_rows,
                display_cols);

            ezdash_component_B_init(
                env, 
                split_A_BC*env->term_cols, 0, 
                (1-split_A_BC)*env->term_cols, env->term_rows);

            break;

        case EZ_MODE3:

            env->A.enable=0;
            env->B.enable=1;
            env->C.enable=1;

            break;

        case EZ_MODE4:

            env->A.enable=1;
            env->B.enable=0;
            env->C.enable=1;

            ezdash_component_A_init(
                env, 
                0, 0, 
                env->term_cols, env->term_rows,
                display_cols);

            break;

        case EZ_MODE5:

            env->A.enable=1;
            env->B.enable=1;
            env->C.enable=1;

            ezdash_component_A_init(
                env, 
                0, 0, 
                env->term_cols, env->term_rows,
                display_cols);

            break;

        default:
            _pigs_fly;

    }

//    d = getch();    // curses call to input from keyboard

//    printw("Type something: ");
//    char str[80];
//    getstr(str);
//    printw("You Entered: %s", str);
//    d = getch();    // curses call to input from keyboard

//    endwin();  // curses call to restore the original window and leave

    return env;

}


//
//
WINDOW *ezdash_new_win(WINDOW *wnd, int win_rows, int win_cols, int y_orig, int x_orig){

    WINDOW *result;

    //WINDOW *subwin(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x);
    result = subwin(wnd,win_rows,win_cols,y_orig,x_orig);

    return result;

}


//
//
void ezdash_del_win(WINDOW *wnd){

    /* box(local_win, ' ', ' '); : This won't produce the desired
    * result of erasing the window. It will leave it's four corners
    * and so an ugly remnant of window.
    */
//    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    /* The parameters taken are
    * 1. win: the window on which to operate
    * 2. ls: character to be used for the left side of the window
    * 3. rs: character to be used for the right side of the window
    * 4. ts: character to be used for the top side of the window
    * 5. bs: character to be used for the bottom side of the window
    * 6. tl: character to be used for the top left corner of the window
    * 7. tr: character to be used for the top right corner of the window
    * 8. bl: character to be used for the bottom left corner of the window
    * 9. br: character to be used for the bottom right corner of the window
    */
//    wrefresh(local_win);
    delwin(wnd);

}


// Clayton Bauman 2019

