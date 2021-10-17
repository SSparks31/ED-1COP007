#ifndef MODULE_SVGLINE_H
#define MODULE_SVGLINE_H

typedef struct line* Line;

Line create_line(char* id, char* coordinates[4], char* color);

char* line_get_id(Line line);

char* line_get_x1(Line line);
char* line_get_y1(Line line);
char* line_get_x2(Line line);
char* line_get_y2(Line line);

char* line_get_color(Line line);

int line_set_x1(Line line, char* x);
int line_set_y1(Line line, char* x);
int line_set_x2(Line line, char* x);
int line_set_y2(Line line, char* x);

int line_set_color(Line line, char* x);

void line_destroy(Line* line);

#endif