https://github.com/tony/NCURSES-Programming-HOWTO-examples
http://www.cs.ukzn.ac.za/~hughm/os/notes/ncurses.html
http://www.clifford.at/stfl/

ez-dash
-------

    Simple TUI dashboard. Output-only, no input. Can enter/exit dashboard
    mode to alternate between taking CLI commands and displaying results of
    CLI commands.

ez-cli
------

    Consists of three TUI components:

        A) dashboard output (left-side of terminal)
        B) scrolling output (main part of terminal); the idea is to redirect
            stdout/stderr to this area
        C) commandline input (bottom of terminal)

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

        NOTE: There will be a visible boundary between A and B,C but no
        visible boundary between B and C. Ideally, C will be a scrollable
        edit-box but single-line command entry will serve the purpose if
        this turns out to be unexpectedly complex.

        NOTE: Hopefully, we have some pthreads/signals stuff working to give
        the TUI a nice look-and-feel.

        NOTE: command-line input string
            Choose some max safe length and provide this to the input routine;
            just drop any additional input until <CR> is pressed
            

