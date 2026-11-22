/*  termaker.h
	COPYRIGHT (С) 2026 Endy (endy.justatwink@gmail.com)
    Licensed under GNU GPL v3

    Github - https://github.com/endytw/Termaker
    
    Description:
    Main Termaker's logic file's header file.
*/

#ifndef TERMAKER_H
    #define TERMAKER_H

    // COLORS AND OTHER TEXT ATTRIBUTES
    #if !defined(_WIN32) && !defined(_WIN64)
    typedef enum {
        red = 0,
        orange = 1, 
        yellow = 2, 
        green = 3, 
        cyan = 4,
        blue = 5, 
        purple = 6, 
        black = 7,
        white = 8, 
        reset = 9
    } color;
	
    #else
    typedef enum {
        red = 4,
        orange = 6,
        yellow = 14,
        green = 2,
        cyan = 3,
        blue = 1,
        purple = 5,
        black = 0,
        white = 15,
		reset = 16
    } color;
    #endif

    typedef struct {
        int x;
        int y;
    } position;

    extern int cols;
    extern int rows;
	
	extern position pos;

    int init(void);
    int end(void);

    void move(int, int);
    void set_color(int, int);
    void reload_frame(void);
	
	/*	Abstraction API
	
		TO ENABLE ABSTRACTION API, DEFINE "_TERM_ABS_API"
	*/
	
	#if defined(_TERM_ABS_API)
	
	
	//	Objects
	typedef struct {
		position obj_pos;
		char *sprite;
		
		// Metadata
		signed char is_visible;
	} object;
	
	int object_init(object obj);
	void object_draw(object obj);
	void object_move(object obj, position obj_pos);
	void object_clear(object obj);
	int object_break(object obj);
	#endif
#endif