#ifndef MODULE_SVGTEXT_H
#define MODULE_SVGTEXT_H

typedef struct text* Text;

Text create_text(char* id, char* coordinates[2], char* string, char* colors[2]);

char* text_get_id(Text text);

char* text_get_x(Text text);
char* text_get_y(Text text);
char* text_get_string(Text text);

char* text_get_border_color(Text text);
char* text_get_fill_color(Text text);

int text_set_x(Text text, char* x);
int text_set_y(Text text, char* y);
int text_set_string(Text text, char* string);

int text_set_border_color(Text text, char* border_color);
int text_set_fill_color(Text text, char* fill_color);

void text_destroy(Text* text);

#endif