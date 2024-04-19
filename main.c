// Copyright (c) 2024, Charlie Fynn Perkins
// All rights reserved.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree. 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include "deps/graphics.h"
#include "deps/iolib.h"

#ifndef BLACKSCREEN_C
#define BLACKSCREEN_C

void home_screen(void){
    print("welcome to robco industries (tm) termlink", 0);
    print(">set terminal/inquire", 2);
    print("rit v-300", 4);
    print(">set file/protection=owner:rwed accounts.f", 6);
    print(">set halt restart/maint", 7);
    print("initialising robco industries(tm) hf boot agent v2.3.0", 9);
    print("retros bios", 10);
    print("rbios-4.02.08.00 52ee5.e7.e8", 11);
    print("copyright 2201-2203 robco ind.", 12);
    print("uppermem: 64kb", 13);
    print("root (5a8)", 14);
    print("maintenance mode", 15);
    print("> run debug/accounts.f", 17);
    print("type EXIT to leave...", 19);
    print(">>>", 20);
}

int main (void){
    // Initial Stack Allocation
    struct Cursor cursor;
    struct CommandLine cmdline;

    // Page Setup
    black_screen();

    // Cursor Config
    cursor_init(&cursor);
    cursor_colour(&cursor, GREEN);

    // Initial Setup
    home_screen();
    cursor_pos(&cursor, 5, 20);

    // Main loop
    while(1){
        cursor_blink(&cursor, BLINK_MAX);
        // if (write_to_screen(&cursor)){};
        if (check_enter(&cmdline, &cursor)){
            return EXIT_SUCCESS;
        }
    }

    // return EXIT_SUCCESS;
}

#endif