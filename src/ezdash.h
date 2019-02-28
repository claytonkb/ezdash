// ezdash.h
//

#include <curses.h>

#ifndef EZDASH_H
#define EZDASH_H

#define MAX_DISPLAY_COLS 12 // completely arbitrary... should be based on term_cols

typedef enum ezdash_mode_enum
        { EZ_MODE1, EZ_MODE2, EZ_MODE3, EZ_MODE4, EZ_MODE5 }
        ezdash_mode;

typedef enum ezdash_border_enum
        { EZ_BORDER_OFF, EZ_BORDER_ON }
        ezdash_border;

typedef struct{

    WINDOW* wnd;

    int enable;

    int cols;
    int rows;
    int x_orig;
    int y_orig;

    // These fields used by component A:
    int dash_width;  // = cols / display_cols
    int dash_height; // = rows * display_cols
    int display_cols; // number of display columns, e.g. 3
//    int display_col_x_orig[MAX_DISPLAY_COLS];

} ezdash_component;


typedef struct{

    WINDOW* wnd; // stdscr base window

    int term_rows;
    int term_cols;

    ezdash_mode mode;

    ezdash_component A;
    ezdash_component B;
    ezdash_component C;

    // border enables
    ezdash_border outer_border;
    ezdash_border column_borders;
    ezdash_border A_border;
    ezdash_border BC_border;
    ezdash_border AC_border;

    // split ratios
    float split_A_BC;
    float split_B_C;
    float split_A_C;

    // units in milliseconds; must be greater than 15
    int update_period;

    // string buffer for CLI input
    char cli_input[256];

} ezdash_env;


ezdash_env *ezdash_init(ezdash_mode mode, 
        float split_A_BC, float split_B_C, float split_A_C,
        int display_cols);
void ezdash_component_A_update(ezdash_env *env, int start_row, int num_lines, const char **str_array);
void ezdash_component_B_print(ezdash_env *env, const char *str);
//void ezdash_update_components(ezdash_component comp, int start_row, int num_lines, const char **str_array);
//WINDOW *ezdash_new_win(int height, int width, int starty, int startx);
WINDOW *ezdash_new_win(WINDOW *wnd, int height, int width, int starty, int startx);
void ezdash_del_win(WINDOW *wnd);
void ezdash_component_A_init(
        ezdash_env *env, 
        int x_orig, int y_orig, 
        int cols,   int rows, 
        int display_cols);
void ezdash_component_B_init(
        ezdash_env *env, 
        int x_orig, int y_orig, 
        int cols,   int rows);


#endif // EZDASH_H

// Clayton Bauman 2019

