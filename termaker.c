/*  termaker.c
	COPYRIGHT (C) 2026 Endy (endy.justatwink@gmail.com)
    Licensed under GNU GPL v3

    Github - https://github.com/endytw/Termaker
    
    Description:
    Main Termaker's logic file.
*/


#include "termaker.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#if defined(__linux__) || defined(__unix__) || defined(__unix) || defined(unix)
    #include <unistd.h>
    #include <sys/ioctl.h>

    struct winsize window;
#elif defined(_WIN32) || defined(_WIN64)
    #include <windows.h>

    static HANDLE handle;
    static WORD word;
	
	static CONSOLE_SCREEN_BUFFER_INFO scr_buffer;
#endif

/*  Initilization and end of program.

    What initialization doing?

        * Clears screen
        * Gets screen's size (Different methods for Windows and unix-like systems)

    What end of program doing?

        * Clears screen
*/

int rows = 0;
int cols = 0;

/*		========== WARNING ==========

		Structure "pos" doesn't update if you use (v)(s/n/sn)printf().
		It updates only through move() function.

*/

position pos = {0, 0};

int init(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
    #if defined(__linux__) || defined(__unix__) || defined(__unix) || defined(unix)
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
        rows = window.ws_row;
        cols = window.ws_col;
    #elif defined(_WIN32) || defined(_WIN64)

        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO i;
        GetConsoleScreenBufferInfo(handle, &i);
        word = i.wAttributes;
    
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &scr_buffer);
    
        rows = scr_buffer.srWindow.Bottom - scr_buffer.srWindow.Top + 1;
        cols = scr_buffer.srWindow.Right - scr_buffer.srWindow.Left + 1;
    #endif

    return 0;
}

int end(void) {
	#if defined(_WIN32)
		COORD start_point = {0, 0};
		SetConsoleCursorPosition(handle, start_point);
		DWORD written;
		FillConsoleOutputCharacter(handle, ' ', rows * cols, start_point, &written);
		FillConsoleOutputAttribute(handle, word, rows * cols, start_point, &written);
		
		WORD attribute = (WORD)((0x0 << 4) | (0x0F & 0x0F));
		SetConsoleTextAttribute(handle, attribute);
	#else
		printf("\033[2J\033[H\033[0m");
	#endif
    fflush(stdout);
    return 0;
}

/*	Basic functions.

	reload_frame() updates screen's size
	set_color() sets color through WindowsAPI (SetConsoleTextAttribute) or through escape sequences
	move() moves cursor position to selected coordinates

*/

void reload_frame(void) {
    #if defined(__linux__) || defined(__unix__) || defined(__unix) || defined(unix)
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
        rows = window.ws_row;
        cols = window.ws_col;
    #elif defined(_WIN32) || defined(_WIN64)
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &scr_buffer);
    
        rows = scr_buffer.srWindow.Bottom - scr_buffer.srWindow.Top + 1;
        cols = scr_buffer.srWindow.Right - scr_buffer.srWindow.Left + 1;
    #endif
    return;
}

void set_color(int color_number, int bg_color_number) {
	#if defined(_WIN32) || defined(_WIN64)
		WORD attribute = (WORD)((bg_color_number << 4) | (color_number & 0x0F));
		SetConsoleTextAttribute(handle, attribute);
	#else
		printf("\033[0m");
		fflush(stdout);
		switch (color_number) {
			case 0: printf("\033[31m");       break;
			case 1: printf("\033[38;5;214m"); break;
			case 2: printf("\033[33m");       break;
			case 3: printf("\033[32m");       break;
			case 4: printf("\033[36m");       break;
			case 5: printf("\033[34m");       break;
			case 6: printf("\033[35m");       break;
			case 7: printf("\033[30m");       break;
			case 8: printf("\033[37m");       break;
		}
		
		switch (bg_color_number) {
			case 0: printf("\033[41m");       break;
			case 1: printf("\033[48;5;214m");      break;
			case 2: printf("\033[43m");       break;
			case 3: printf("\033[42m");       break;
			case 4: printf("\033[46m");       break;
			case 5: printf("\033[44m");       break;
			case 6: printf("\033[45m");       break;
			case 7: printf("\033[40m");       break;
			case 8: printf("\033[47m");       break;
		}
	#endif
	fflush(stdout);
}

void move(int height, int width) {
	#if defined(_WIN32) || defined(_WIN64)
	COORD coordinates = {width, height};
	SetConsoleCursorPosition(handle, coordinates);
	#else
    printf("\033[%d;%dH", height+1, width+1);
	#endif
    fflush(stdout);
    pos.x = width;
    pos.y = height;
    return;
}



/*	Abstraction API
	
	TO ENABLE ABSTRACTION API, DEFINE "_TERM_ABS_API"
*/


#if defined(_TERM_ABS_API)

#endif