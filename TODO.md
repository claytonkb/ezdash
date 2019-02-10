https://github.com/tony/NCURSES-Programming-HOWTO-examples  
http://www.cs.ukzn.ac.za/~hughm/os/notes/ncurses.html  
http://www.clifford.at/stfl/  

ez-dash
-------

    Up to three TUI components:

        A) dashboard output (left-side of terminal)

            Updates are written to screen via a ptr-array

        B) scrolling output (main part of terminal); the idea is to redirect
            stdout/stderr to this area

            Updates are written via single-line prints (printf-style); ezdash
            handles scrolling-emulation via ncurses

        C) commandline input (bottom of terminal)

            ezdash handles key input/echoing/clearing/cursor and signals
            parent when input is available or sends appropriate Ctl+C/Z/X sigs

        +--------+----------------------------------+
        |        |                                  |
        |        |                                  |
        |        |                                  |
        |        |               B                  |
        |   A    |                                  |
        |        |                                  |
        |        |                                  |
        |        |----------------------------------+
        |        |               C                  |
        +--------+----------------------------------+

    Modes:

        Mode 1 (dashboard mode):

            Component A uses entire screen
            Can be split into multiple columns (borders or no borders)

        Mode 2 (dashboard + scrolling mode):

            Screen is vsplit into A & B components
            Mode A is single column only
            Border/no-border configurable
            % split between A/B

        Mode 3 (scrolling + CLI)

            Screen is hsplit into B & C components
            Border/no-border configurable
            % split between B/C

        Mode 4 (dashboard + CLI)

            Screen is hsplit into A & C components
            Component A can be split into multiple columns (border or no borders)
            Border/no-border configurable between A/C
            % split between A/C

        Mode 5 (A+B+C)

            All components visible as depicted above
            Border/no-border configurable between B/C and A/(BC)
            % splits between B/C and A/(BC)

        NOTE: Hopefully, we have some pthreads/signals stuff working to give
        the TUI a nice look-and-feel.

        NOTE: command-line input string
            Choose some max safe length and provide this to the input routine;
                just drop any additional input until <CR> is pressed
            This CLI is not suitable for long, shell-style commands
            
        NOTE: scrolling in curses
            https://www.mkssoftware.com/docs/man3/curs_scroll.3.asp            

