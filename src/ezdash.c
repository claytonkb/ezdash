// ezdash.c
//

#include "ezdash.h"
#include <curses.h>


int r,c;  // current row and column (upper-left is (0,0))

void ezdash_screen_update(ezdash_component comp, int start_row, int num_lines, const char **str_array){

    clear();

    ezdash_print_page(comp, start_row, num_lines, str_array);

    refresh();

}


// str_array = {"str1", "str2", ...}
//
void ezdash_print_page(ezdash_component comp, int start_row, int num_lines, const char **str_array){

    int i;

    for(i=0; i<num_lines && i<comp.dash_height; i++){

        mvaddnstr(
            comp.y_orig +  i%comp.rows,
            comp.x_orig + (i/comp.rows)*comp.dash_width,
            str_array[i],
            comp.dash_width );

    }

}


void ezdash_init(ezdash_mode mode, int num_cols){

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
        "ipsum", "tempus", "ut", 
    };

#define num_cols 12

    ezdash_component comp;
    comp.enable=1;

    getmaxyx(wnd,comp.rows,comp.cols);

    comp.x_orig=0;
    comp.y_orig=0;
    comp.dash_width=comp.cols/num_cols;
    comp.dash_height=comp.rows*num_cols;
    comp.display_cols=num_cols;

    for(i=0;i<MAX_DISPLAY_COLS;i++){
        comp.display_col_x_orig[i]=0;
    }

    ezdash_screen_update(comp, 1, num_cols*comp.rows, foo);

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


// Clayton Bauman 2019

