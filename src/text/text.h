#ifndef TEXT_H
#define TEXT_H

#include "text_p.h"

struct text_t;
struct graphic_t;
struct graphic_t;
typedef int bool_t;

// memory allocator
struct text_t* text_new(void);

// Constructor
int text_ctor(struct text_t*, struct graphic_t*);

// Destructor
void text_dtor(struct text_t*);

// Behavior
void text_reset_buffer(struct text_t*);
int text_get_max_line_length(void);
void text_draw(struct text_t* text, struct graphic_t* graphic, int x, int w, int y, int r, int g, int b, char *format, ...);
void text_draw_line(struct text_t* text, struct graphic_t* graphic, text_line_t* line, bool_t centered);

#endif
