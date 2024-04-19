// Copyright (c) 2024, Charlie Fynn Perkins
// All rights reserved.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree. 

#include "deps/graphics.h"
#include <string.h>
#include <stdlib.h>

// ADDRESS MACROS

#define GETIN_ADDR 0xFFE4

// OTHER MACROS


#define BLINK_MAX 0xFFFF


#ifndef IOLIB_H
#define IOLIB_H


// KERNAL FUNCTION POINTERS RELATED TO I/O

char (*get_in) (void) = (char(*)(void)) GETIN_ADDR;


// CURSOR STRUCTURE AND FUNCTIONS

struct Cursor{
    unsigned char pos_x;
    unsigned char pos_y;
    char colour;
    char cover;
    bool display;
    int period_counter;
};

void cursor_blink(struct Cursor *cursor, unsigned char interval){
    if (++(cursor->period_counter) % interval){
            if (cursor->display){
                set_pixel(cursor->pos_x, cursor->pos_y, cursor->colour, 97);
            }
            else{
                set_pixel(cursor->pos_x, cursor->pos_y, cursor->colour, 0x20);
            }
            cursor->display = !(cursor->display);
        }
}

void cursor_init(struct Cursor *cursor){
    cursor->pos_x = 0;
    cursor->pos_y = 0;
    cursor->colour = WHITE;
    cursor->display = 0;
    cursor->period_counter = 0;
}

void cursor_colour(struct Cursor *cursor, unsigned char colour){
    cursor->colour = colour;
}

void cursor_increment(struct Cursor *cursor){
    unsigned char posx = cursor->pos_x;
    unsigned char posy = cursor->pos_y;
    if (posx < 40){
        ++(cursor->pos_x);
    }
    else{
        cursor->pos_x = 0;
        if (posy < 25){
            ++(cursor->pos_y);
        }
        else{
            // SCROLL SCREEN
        }
    }
}

void cursor_decrement(struct Cursor *cursor){
    unsigned char posx = cursor->pos_x;
    unsigned char posy = cursor->pos_y;
    if (posx > 0){
        --(cursor->pos_x);
    }
    else{
        cursor->pos_x = 40;
        if (posy > 0){
            --(cursor->pos_y);
        }
        else{
            // SCROLL SCREEN
        }
    }
}

void cursor_pos(struct Cursor *cursor, unsigned char posx, unsigned char posy){
    if (posx < 41){
        cursor->pos_x = posx;
    }
    else{
        cursor->pos_x = 40;
    }
    if (posy < 26){
        cursor->pos_y = posy;
    }
    else{
        cursor->pos_y = 25;
    }
}

// HHLPER FUNCTIONS

char *strnslc(int len, char* string){
    char* buff = (char*) malloc(len); // +1
    strncpy(buff, string, len);
    // buff[len] = '\0';
    return buff;
}

bool stringcompare(char* val, char* compar){
    int compar_len, val_len;
    char* chomp;

    compar_len = strlen(compar);
    val_len = strlen(val);

    chomp = strnslc(compar_len, val);

    if (strcmp(chomp, compar) == 0){
        free(chomp);
        return 1;
    }

    free(chomp);
    return 0;
}

// TEXT I/O AND COMMANDLINE

struct CommandLine {
    char buff[37];
};

int write_to_screen(struct Cursor *cursor){
    char buff = '\0';
    buff = get_in();
    switch (buff){
        case 0: {}
        case 3: return 1;
        case 13: {}
        case 20:
            // Backspace
            set_pixel(cursor->pos_x, cursor->pos_y, BLACK, 0x20);
            cursor_decrement(cursor);
        
        default:
            // Text
            set_pixel(cursor->pos_x, cursor->pos_y, cursor->colour, buff);
            cursor_increment(cursor);
    }
    return 0;
}

char* commandline_get(struct Cursor *cursor){
    unsigned char i;
    char* line = (char*) malloc(37); // Could be improves
    // char line[37];
    char buff_a;
    char buff_b = '\0';
    unsigned char line_pos = cursor->pos_y;

    for (i = 6; i < 41; ++i){
        buff_a = get_pixel(i, line_pos);
        line[i - 4] = buff_a;
        if ((buff_a == 0x20) && (buff_b == 0x20)){
            line[i - 3] = '\0';
            break;
        }
        buff_b = buff_a;
    }
    line[36] = '\0';
    screen_to_ascii(line);
    return line;
}

char commandline_execute(struct CommandLine *cmdline){
    // unsigned char i;
    unsigned char len = strlen(cmdline->buff);
    if (stringcompare(cmdline->buff, "exit")){
        return 0;
    }
    
    return 1;
}

char check_enter(struct CommandLine *cmdline, struct Cursor *cursor){
    char buff1 = 0;
    char* line;
    buff1 = get_in();
    if (buff1 == 13){
        line = commandline_get(cursor);
        strcpy(cmdline->buff, line);
        print(cmdline->buff, 23);
        buff1 = commandline_execute(cmdline);
        free(line);
    }
    return buff1;
}

#endif