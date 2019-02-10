// ezdash.h
//

#include <curses.h>

#ifndef EZDASH_H
#define EZDASH_H

void ezdash_init();

typedef enum ezdash_mode_enum
        { MODE1, MODE2, MODE3, MODE4, MODE5 }
        ezdash_mode;

typedef struct{

    WINDOW* wnd;

    ezdash_mode mode;

    // component enables
    int en_component_A;
    int en_component_B;
    int en_component_C;

    // border enables
    int en_outer_border;
    int en_column_borders;
    int en_A_border;
    int en_BC_border;
    int en_AC_border;

    // mode A column count
    int num_columns;

    // split ratios
    float split_A_BC;
    float split_B_C;
    float split_A_C;

    // units in milliseconds; must be greater than 15
    int update_period;

    // string buffer for CLI input
    char *cli_input;

} ezdash_env;



#endif // EZDASH_H

// Clayton Bauman 2019

