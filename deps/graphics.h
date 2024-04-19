// Copyright (c) 2024, Charlie Fynn Perkins
// All rights reserved.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree. 

#include <string.h>

/*
 * graphics.h
 * This file contains useful functions for manually changing graphics on the Commodore 64
 */

// GRAPHICS RELATED ADDRESSES
#define BORDER_ADDR 0xD020
#define BACKGROUND_ADDR 0xD021
#define SCREEN_ADDR 0x0400
#define COLOUR_ADDR 0xD800

// COLOUR MACROS
#define BLACK 0x0
#define WHITE 0x1
#define RED 0x2
#define CYAN 0x3
#define PURPLE 0x4
#define GREEN 0x5
#define BLUE 0x6;
#define YELLOW 0x7
#define ORANGE 0x8
#define BROWN 0x9
#define PINK 0xA
#define DARK_GREY 0xB
#define GREY 0xC
#define LIGHT_GREEN 0xD
#define LIGHT_BLUE 0xE
#define LIGHT_GREY 0xF


#ifndef GRAPHICS_H
#define GRAPHICS_H

void set_pixel(unsigned char x, unsigned char y, char col, char symb){
    int px = 40*y + x;
    *(char*)(SCREEN_ADDR + px) = symb;
    *(char*)(COLOUR_ADDR + px) = col;
}

void set_border(char val){
    *(char*)BORDER_ADDR = val;
}

void set_background(char val){
    *(char*)BACKGROUND_ADDR = val;
}

void black_screen(void){
    unsigned char i;
    unsigned char j;

    set_background(BLACK);
    set_border(BLACK);
    for (i = 0; i < 25; ++i){
        for(j = 0; j < 40; ++j){
            set_pixel(j, i, BLACK, 0x20);
        }
    }
}

void print_charset(void){
    char i, x, y;
    x = y = i = 0;

    while(i < 255){
        set_pixel(x, y, GREEN, i);
        ++x;
        if (!((x) % 5)){
            if (!((x) % 40)){
                ++y;
                x=0;
                }
            else{
                set_pixel(x, y, GREEN, 0x20);
                ++x;
                }
        }
        i++;
    }
}

void print(char string[], char line){
     int i;
     for (i = 0; i < strlen(string); ++i){
        set_pixel(i, line, GREEN, string[i]);
     }
}

char* keyb_to_screen_block(char* string){
    int i, len;
    len = strlen(string);
    for (i = 0; i < len; ++i){
        // Lowercase
        if ((string[i] >= 0x41) && (string[i] <= (0x41 + 0x1A))){
            string[i] -= 192;
        }
    }
    return string;
}

char* keyb_to_screen_normal(char* string){
    int i, len;
    len = strlen(string);
    for (i = 0; i < len; ++i){
        // Lowercase
        if ((string[i] >= 65) && (string[i] < (65 + 64))){
            string[i] -= 64;
        }
        // Uppercase
        else if ((string[i] >= 192) && (string[i] < (192 + 63))){
            string[i] -= 128;
        }
    }
    return string;
}

char get_pixel(unsigned char x, unsigned char y){
    int px = 40*y + x;
    return *(char*)(SCREEN_ADDR + px);
}

char* screen_to_ascii(char* string){
    int i;
    unsigned char len = strlen(string);

    for (i = 0; i < len; ++i){
        if ((string[i] > 0) && (string[i] <= 26)){
            string[i] += 96;
        }
        else if ((string[i] > 64) && (string[i] <= 90)){
            //
        }
        else if ((string[i] > 128) && (string[i] <= 154)){
            string[i] -= 32;
        }
        else if ((string[i] > 192) && (string[i] <= 218)){
            string[i] -= 127;
        }
    }
    return string;
}

#endif