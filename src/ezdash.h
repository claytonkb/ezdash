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

    int enable;

    int cols;
    int rows;
    int x_orig;
    int y_orig;

    // These fields used by component A:
    int dash_width;  // = cols / display_cols
    int dash_height; // = rows * display_cols

    int display_cols; // number of display columns, e.g. 3
    int display_col_x_orig[MAX_DISPLAY_COLS];

} ezdash_component;


typedef struct{

    WINDOW* wnd;

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


void ezdash_init();
void ezdash_print_page(ezdash_component comp, int start_row, int num_lines, const char **str_array);
void ezdash_screen_update(ezdash_component comp, int start_row, int num_lines, const char **str_array);

#endif // EZDASH_H

// Clayton Bauman 2019

