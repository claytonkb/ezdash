// ezdash.c
//

#include "ezdash.h"
#include "cutils.h"
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
//unsigned int sleep(unsigned int seconds);

int r,c;  // current row and column (upper-left is (0,0))


//
//
void ezdash_component_B_print(ezdash_component comp, const char *str){

    //don't clear component B
    wprintw(comp.wnd, str);
    wprintw(comp.wnd, "\n" );

    wrefresh(comp.wnd);

    sleep(1);

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

//    ezdash_component comp = env->A;
    env->A.enable=1;

    env->A.rows = rows;
    env->A.cols = cols;

//    scrollok(env->A.wnd, TRUE); // wprintw() acts like printf now

    env->A.x_orig=x_orig;
    env->A.y_orig=y_orig;

    env->A.wnd = ezdash_new_win(env->wnd, env->A.rows, env->A.cols, env->A.x_orig, env->A.y_orig);

    env->A.dash_width   = env->A.cols / display_cols;
    env->A.dash_height  = env->A.rows * display_cols;
    env->A.display_cols = display_cols;

//    int i;
//    for(i=0;i<MAX_DISPLAY_COLS;i++){
//        comp.display_col_x_orig[i]=0;
//    }

//    return comp;

}


void ezdash_init(ezdash_mode mode, int display_cols){

    int i;
    char d;

    WINDOW* wnd;

    wnd = initscr();    // curses call to initialize window

//    cbreak();           // curses call to set no waiting for Enter key
//    noecho();           // curses call to set no echoing
//    getmaxyx(wnd,nrows,ncols);  // curses call to find size of window
//    clear();            // curses call to clear screen, send cursor to position (0,0)
//    refresh();  // curses call to implement all changes since last refresh

    scrollok(wnd, TRUE); // printw() acts like printf now

    ezdash_env *env = malloc(sizeof(ezdash_env));

    env->mode=mode;
    env->wnd=wnd;
    getmaxyx(wnd, env->term_rows, env->term_cols);

    env->update_period=20;

    env->split_A_BC=0.5;
    env->split_B_C =0.5;
    env->split_A_C =0.5;

    switch(mode){
        case EZ_MODE1:
            env->A.enable=1;
            env->B.enable=0;
            env->C.enable=0;
            break;
        case EZ_MODE2:
            break;
        case EZ_MODE3:
            break;
        case EZ_MODE4:
            break;
        case EZ_MODE5:
            break;
        default:
            _pigs_fly;
    }

    const char *foo[] = {
        "Lorem", "ipsum", "dolor", "sit", "amet", "consectetur", "adipiscing", "elit",
        "Vivamus", "nec", "ipsum", "finibus", "ante", "volutpat", "aliquam", "at",
        "in", "ante", "Nam", "ac", "elit", "non", "justo", "efficitur", "finibus",
        "ac", "eget", "velit", "Ut", "vel", "bibendum", "quam", "In", "consequat",
        "est", "in", "dui", "maximus", "at", "venenatis", "nibh", "sollicitudin",
        "Cras", "vel", "erat", "ullamcorper", "scelerisque", "augue", "non",
        "consequat", "velit", "Fusce", "facilisis", "enim", "nunc", "ut", "pulvinar",
        "massa", "convallis", "Nullam", "laoreet", "urna", "Lorem", "ipsum", "dolor",
        "sit", "amet", "consectetur", "adipiscing", "elit", "Donec", "gravida", "erat",
        "id", "maximus", "placerat", "leo", "dui", "viverra", "ex", "finibus", "augue",
        "felis", "turpis", "Sed", "ipsum", "mi", "lobortis", "mi", "id", "pharetra",
        "maximus", "turpis", "In", "id", "mattis", "nibh", "tempus", "sagittis", "ligula", "Vivamus",
        "tristique", "elit", "in", "sollicitudin", "consequat", "Nam", "quam", "dolor",
        "facilisis", "et", "tempor", "vel", "elementum", "eget", "quam", "Proin",
        "condimentum", "sed", "mi", "in", "blandit", "Nullam", "rhoncus", "dui", "in",
        "lorem", "volutpat", "at", "dictum", "lacus", "tempus", "Class", "aptent",
        "taciti", "sociosqu", "ad", "litora", "torquent", "per", "conubia", "nostra",
        "per", "inceptos", "himenaeos", "Morbi", "facilisis", "massa", "quis",
        "eleifend", "congue", "Nullam", "id", "enim", "congue", "interdum", "tellus",
        "vel", "volutpat", "metus", "Nunc", "ligula", "lacus", "viverra", "eget",
        "faucibus", "volutpat", "non", "felis", "Donec", "ipsum", "metus", "luctus",
        "pellentesque", "lorem", "eu", "faucibus", "tristique", "augue", "Aenean",
        "in", "velit", "ultrices", "congue", "libero", "quis", "molestie", "odio",
        "Integer", "eu", "enim", "congue", "fringilla", "lectus", "vel", "interdum",
        "orci", "Phasellus", "nec", "massa", "vestibulum", "nisl", "iaculis",
        "fringilla", "nec", "quis", "enim", "Sed", "vitae", "aliquam", "turpis", "in",
        "volutpat", "ligula", "Nullam", "facilisis", "imperdiet", "quam", "id",
        "posuere", "Proin", "iaculis", "aliquet", "elit", "quis", "pharetra", "metus",
        "faucibus", "Nam", "eu", "elementum", "diam", "Mauris", "mattis", "magna",
        "et", "nibh", "sagittis", "porttitor", "Orci", "varius", "natoque",
        "penatibus", "et", "magnis", "dis", "parturient", "montes", "nascetur",
        "ridiculus", "mus", "Morbi", "nec", "neque", "nec", "ante", "consectetur",
        "scelerisque", "Duis", "eu", "leo", "massa", "Cras", "tincidunt", "odio",
        "venenatis", "velit", "ultrices", "ac", "rhoncus", "felis", "ornare",
        "Praesent", "facilisis", "dui", "et", "sem", "fringilla", "ut", "commodo",
        "nunc", "scelerisque", "Orci", "varius", "natoque", "penatibus", "et",
        "magnis", "dis", "parturient", "montes", "nascetur", "ridiculus", "mus",
        "Nunc", "facilisis", "eleifend", "euismod", "Nulla", "pellentesque", "pretium",
        "nibh", "vel", "volutpat", "mauris", "sodales", "non", 
        "Phasellus", "quis", "urna", "eros", "Fusce", "erat", "quam", "faucibus",
        "eget", "erat", "vitae", "pulvinar", "pretium", "nisl", "Donec",
        "pellentesque", "urna", "Proin", "non", "sem", "id", "magna", "fermentum",
        "consectetur", "Morbi", "efficitur", "enim", "id", "venenatis", "ornare",
        "Proin", "dignissim", "facilisis", "nulla", "ut", "placerat", "orci",
        "tincidunt", "Pellentesque", "habitant", "morbi", "tristique", "senectus",
        "et", "netus", "et", "malesuada", "fames", "ac", "turpis", "egestas", "Etiam",
        "nunc", "arcu", "facilisis", "vel", "justo", "elementum", "scelerisque",
        "commodo", "odio", "Suspendisse", "potenti", "In", "id", "interdum", "velit",
        "Donec", "tristique", "vehicula", "vulputate", "Donec", "fringilla", "eget",
        "quam", "nec", "gravida", "Nulla", "faucibus", "nisl", "vitae", "velit",
        "iaculis", "sed", "ultrices", "turpis", "tempor", "Maecenas", "eu",
        "efficitur", "eros", "In", "in", "semper", "lectus", "Etiam", "eu", "metus",
        "magna", "Vivamus", "eu", "turpis", "commodo", "hendrerit", "sem", "non",
        "tincidunt", "ipsum", "Nam", "odio", "lorem", "tincidunt", "eget", "varius",
        "nec", "auctor", "in", "turpis", "Aenean", "eu", "augue", "vitae", "justo",
        "tincidunt", "fringilla", "Praesent", "tincidunt", "imperdiet", "quam", "sit",
        "amet", "euismod", "Pellentesque", "porta", "dui", "quis", "elementum",
        "varius", "tellus", "arcu", "sodales", "justo", "nec", "lacinia", "eros", "ex",
        "eget", "tortor", "Fusce", "ultricies", "leo", "sapien", "id", "tempor",
        "ipsum", "tempus", "ut"
    };

#define num_cols 3

//    ezdash_component comp = env->A;

    env->A.enable=1;

//    getmaxyx(wnd,env->A.rows,env->A.cols);
//    env->A.rows /= 2;
//    env->A.cols /= 2;
//    env->A.wnd = ezdash_new_win(wnd, env->A.rows, env->A.cols, 10, 10);
//    scrollok(env->A.wnd, TRUE); // wprintw() acts like printf now
//
//    env->A.x_orig=0;
//    env->A.y_orig=0;
//    env->A.dash_width=env->A.cols / num_cols;
//    env->A.dash_height=env->A.rows * num_cols;
//    env->A.display_cols=num_cols;

//    ezdash_component_A_init(
//            env, 
//            10, 10, 
//            (env->term_cols / 2), (env->term_rows / 2),
//            3);

    ezdash_component_A_init(
            env, 
            0, 0, 
            env->term_cols, env->term_rows,
            3);

    ezdash_component_A_update(env, 0, num_cols*env->A.rows, foo);

    d = getch();    // curses call to input from keyboard

    printw("Type something: ");
    char str[80];
    getstr(str);
    printw("You Entered: %s", str);
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

