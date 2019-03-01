// main.cpp
//

#include "cutils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ezdash.h"

void dev_prompt(void);
void dev_get_line(char *buffer, FILE *stream);
void dev_menu(void);
char *slurp_file(char *filename);
FILE *open_file(char *filename, const char *attr);
int file_size(FILE *file);


int main(void){

//    srand((unsigned)time(NULL));

    dev_prompt();

    _msg("Done");

}


//
//
void dev_prompt(void){

    char *cmd_code_str;
    int   cmd_code=0;

    char buffer[256];

    int i,j;
    char c;
    int dev_i;

    char *cnf_file;

    int    tempi;

    ezdash_env *env;

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
    };

    _say("type 0 for menu");

    while(1){

        _prn("% ");

        dev_get_line(buffer, stdin);

        cmd_code_str = strtok(buffer, " ");
        if(cmd_code_str == NULL) continue;
        cmd_code = atoi(cmd_code_str);

        switch(cmd_code){
            case 0:
                dev_menu();
                break;

            case 1:

#define num_cols 4

                env = ezdash_init(EZ_MODE2, 
                        0.5, 0.5,
                        num_cols);

                ezdash_component_A_update(env, 0, num_cols*env->A.rows, foo);
//                ezdash_component_B_print(env, foo[0]);

//refresh();
//
//wprintw(env->A.wnd, "This is window A\n");
//wrefresh(env->A.wnd);
//
//mvwprintw(env->B.wnd, 0, 0, "This is window B\n");
//wrefresh(env->B.wnd);

                c = getch();

                for(i=40; i<80; i++){
                    ezdash_component_B_print(env, foo[i]);
                    ezdash_component_B_print(env, "\n");
                    sleep(1);
                }

                c = getch();

                endwin();
                break;

            case 2:
                _say("exiting");
                return;

            default:
                _say("unrecognized cmd_code");
                dev_menu();
                break;
        }

        for(i=0;i<256;i++){ buffer[i]=0; } // zero out the buffer

    }

}


//
//
void dev_get_line(char *buffer, FILE *stream){

    int c, i=0;

    while(1){ //FIXME unsafe, wrong
        c = fgetc(stream);
        if(c == EOF || c == '\n'){
            break;
        }
        buffer[i] = c;
        i++;
    }

    buffer[i] = '\0';

}


//
//
void dev_menu(void){

    _say( "\n0     .....    list command codes\n"
            "1     .....    dev one-off\n"
            "2     .....    exit\n");

}


//
//
char *slurp_file(char *filename){

    FILE *f = open_file((char*)filename, "r");
    int size = file_size(f);

    char *file_buffer = (char*)malloc(size+1);
    size_t dummy = fread((char*)file_buffer, 1, size, f);

    fclose(f);

    return file_buffer;

}


//
//
FILE *open_file(char *filename, const char *attr){

    FILE* file;

    file = fopen((char*)filename, attr);

    if(file==NULL)
        _fatal((char*)filename);

    return file;

}


//
//
int file_size(FILE *file){

    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    rewind(file);

    return size;

}


//        "volutpat", "ligula", "Nullam", "facilisis", "imperdiet", "quam", "id",
//        "posuere", "Proin", "iaculis", "aliquet", "elit", "quis", "pharetra", "metus",
//        "faucibus", "Nam", "eu", "elementum", "diam", "Mauris", "mattis", "magna",
//        "et", "nibh", "sagittis", "porttitor", "Orci", "varius", "natoque",
//        "penatibus", "et", "magnis", "dis", "parturient", "montes", "nascetur",
//        "ridiculus", "mus", "Morbi", "nec", "neque", "nec", "ante", "consectetur",
//        "scelerisque", "Duis", "eu", "leo", "massa", "Cras", "tincidunt", "odio",
//        "venenatis", "velit", "ultrices", "ac", "rhoncus", "felis", "ornare",
//        "Praesent", "facilisis", "dui", "et", "sem", "fringilla", "ut", "commodo",
//        "nunc", "scelerisque", "Orci", "varius", "natoque", "penatibus", "et",
//        "magnis", "dis", "parturient", "montes", "nascetur", "ridiculus", "mus",
//        "Nunc", "facilisis", "eleifend", "euismod", "Nulla", "pellentesque", "pretium",
//        "nibh", "vel", "volutpat", "mauris", "sodales", "non", 
//        "Phasellus", "quis", "urna", "eros", "Fusce", "erat", "quam", "faucibus",
//        "eget", "erat", "vitae", "pulvinar", "pretium", "nisl", "Donec",
//        "pellentesque", "urna", "Proin", "non", "sem", "id", "magna", "fermentum",
//        "consectetur", "Morbi", "efficitur", "enim", "id", "venenatis", "ornare",
//        "Proin", "dignissim", "facilisis", "nulla", "ut", "placerat", "orci",
//        "tincidunt", "Pellentesque", "habitant", "morbi", "tristique", "senectus",
//        "et", "netus", "et", "malesuada", "fames", "ac", "turpis", "egestas", "Etiam",
//        "nunc", "arcu", "facilisis", "vel", "justo", "elementum", "scelerisque",
//        "commodo", "odio", "Suspendisse", "potenti", "In", "id", "interdum", "velit",
//        "Donec", "tristique", "vehicula", "vulputate", "Donec", "fringilla", "eget",
//        "quam", "nec", "gravida", "Nulla", "faucibus", "nisl", "vitae", "velit",
//        "iaculis", "sed", "ultrices", "turpis", "tempor", "Maecenas", "eu",
//        "efficitur", "eros", "In", "in", "semper", "lectus", "Etiam", "eu", "metus",
//        "magna", "Vivamus", "eu", "turpis", "commodo", "hendrerit", "sem", "non",
//        "tincidunt", "ipsum", "Nam", "odio", "lorem", "tincidunt", "eget", "varius",
//        "nec", "auctor", "in", "turpis", "Aenean", "eu", "augue", "vitae", "justo",
//        "tincidunt", "fringilla", "Praesent", "tincidunt", "imperdiet", "quam", "sit",
//        "amet", "euismod", "Pellentesque", "porta", "dui", "quis", "elementum",
//        "varius", "tellus", "arcu", "sodales", "justo", "nec", "lacinia", "eros", "ex",
//        "eget", "tortor", "Fusce", "ultricies", "leo", "sapien", "id", "tempor",
//        "ipsum", "tempus", "ut"



// Clayton Bauman 2018

