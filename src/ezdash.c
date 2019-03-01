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
ezdash_env *ezdash_init(ezdash_mode mode, 
        float vsplit, float hsplit,
        int display_cols){

    int i;

    ezdash_env *env = malloc(sizeof(ezdash_env));

    env->mode=mode;
    env->wnd=initscr();
    getmaxyx(env->wnd, env->term_rows, env->term_cols);

    env->update_period=20;

    env->vsplit = vsplit;
    env->hsplit = hsplit;

    switch(mode){

        case EZ_MODE1:

            env->A.enable=1;
            env->B.enable=0;
            env->C.enable=0;

            ezdash_component_A_init(
                env, 
                env->term_rows, env->term_cols,
                0, 0, 
                display_cols);

            break;

        case EZ_MODE2:

            env->A.enable=1;
            env->B.enable=1;
            env->C.enable=0;

            ezdash_component_A_init(
                env, 
                env->term_rows, vsplit*env->term_cols,
                0, 0, 
                display_cols);

            ezdash_component_B_init(
                env, 
                env->term_rows, (1-vsplit)*env->term_cols,
                0, vsplit*env->term_cols);

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
void ezdash_component_B_print(ezdash_env *env, const char *str){

    refresh();
//    wprintw(env->B.wnd, "This is window B\n");
    wprintw(env->B.wnd, str);
    wrefresh(env->B.wnd);

}


// str_array = {"str1", "str2", ...}
//
void ezdash_component_A_update(ezdash_env *env, int start_row, int num_lines, const char **str_array){

    int i=0;

    refresh();
    wclear(env->A.wnd);

    for(i=0; i<num_lines && i<env->A.dash_height; i++){

        //int mvwaddnstr(WINDOW *win, int row, int col, const char *str, int n);
        mvwaddnstr(
            env->A.wnd,
            i%env->A.rows,
            (i/env->A.rows)*env->A.dash_width,
            str_array[i],
            env->A.dash_width );

    }

    wrefresh(env->A.wnd);

}


//
//
void ezdash_component_A_init(
        ezdash_env *env, 
        int rows, int cols,
        int row_orig, int col_orig, 
        int display_cols){

    env->A.enable=1;

    env->A.rows = rows;
    env->A.cols = cols;

    env->A.row_orig=row_orig;
    env->A.col_orig=col_orig;

    env->A.wnd = ezdash_new_win(env->wnd, env->A.rows, env->A.cols, env->A.row_orig, env->A.col_orig);

    env->A.display_cols = display_cols;
    env->A.dash_width   = env->A.cols / display_cols;
    env->A.dash_height  = env->A.rows * display_cols;

}


//
//
void ezdash_component_B_init(
        ezdash_env *env, 
        int rows,   int cols,
        int row_orig, int col_orig){

    env->B.enable=1;

    env->B.rows = rows;
    env->B.cols = cols;

    env->B.col_orig=col_orig;
    env->B.row_orig=row_orig;

//wprintw(env->A.wnd, "env->B.col_orig: %d", env->B.col_orig);

    env->B.wnd = ezdash_new_win(env->wnd, env->B.rows, env->B.cols, env->B.row_orig, env->B.col_orig);

    scrollok(env->B.wnd, TRUE); // causes printw() to act like printf

}




//
//
WINDOW *ezdash_new_win(WINDOW *wnd, int win_rows, int win_cols, int y_orig, int x_orig){

    WINDOW *result;

    //WINDOW *subwin(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x);
//    result = subwin(wnd,win_rows,win_cols,y_orig,x_orig);

    //WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);
    result = newwin(win_rows,win_cols,y_orig,x_orig);

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

