#include "text.h"

#include <stdlib.h>
#include <string.h>

struct text {
    char* id;

    double x;
    double y;
    char* string;

    char* border_color;
    char* fill_color;
};


Text create_text(char* id, double coordinates[2], char* string, char colors[2][999]) {
    if (!id || !coordinates || !colors) {
        return NULL;
    }

    Text text = malloc(sizeof(struct text));
    if (!text) {
        return NULL;
    }

    text->id = malloc(strlen(id) + 1);
    strcpy(text->id, id);

    text_set_x(text, coordinates[0]);
    text_set_y(text, coordinates[1]);
    text_set_string(text, string);

    text_set_border_color(text, colors[0]);
    text_set_fill_color(text, colors[1]);

    return text;
}

char* text_get_id(Text text) {
    if (!text) {
        return NULL;
    }

    return text->id;
}

double text_get_x(Text text) {
    if (!text) {
        return -1;
    }

    return text->x;
}

double text_get_y(Text text) {
    if (!text) {
        return -1;
    }

    return text->y;
}
char* text_get_string(Text text) {
    if (!text) {
        return NULL;
    }

    return text->string;
}

char* text_get_border_color(Text text) {
    if (!text) {
        return NULL;
    }

    return text->border_color;
}

char* text_get_fill_color(Text text) {
    if (!text) {
        return NULL;
    }

    return text->fill_color;
}

void text_set_x(Text text, double x) {
    if (!text || x < 0) {
        return;
    }

    text->x = x;
}

void text_set_y(Text text, double y){
    if (!text || y < 0) {
        return;
    }

    text->y = y;
}

void text_set_string(Text text, char* string) {
    if (!text || !string) {
        return;
    }

    if (!text->string) {
        text->string = malloc(strlen(string) + 1);
    } else {
        text->string = realloc(text->string, strlen(string) + 1);
    }
    
    strcpy(text->string, string);
}

void text_set_border_color(Text text, char* border_color) {
    if (!text || !border_color) {
        return;
    }

    if (!text->border_color) {
        text->border_color = malloc(strlen(border_color) + 1);
    } else {
        text->border_color = realloc(text->border_color, strlen(border_color) + 1);
    }
    
    strcpy(text->border_color, border_color);
}

void text_set_fill_color(Text text, char* fill_color) {
    if (!text || !fill_color) {
        return;
    }

    if (!text->fill_color) {
        text->fill_color = malloc(strlen(fill_color) + 1);
    } else {
        text->fill_color = realloc(text->fill_color, strlen(fill_color) + 1);
    }
    
    strcpy(text->fill_color, fill_color);
}

void text_destroy(Text* text) {
    if (!text || !*text) {
        return;
    }

    if ((*text)->id) free((*text)->id); 
    
    if ((*text)->string) free((*text)->string);

    if ((*text)->border_color) free((*text)->border_color); 
    if ((*text)->fill_color) free((*text)->fill_color); 

    free(*text);
    *text = NULL;
}

void text_write_to_SVG(FILE* svg_file, Text text) {
    if (!svg_file || !text) {
        return;
    }

    const char* format = "<text x=\"%.6lf\" y=\"%.6lf\" stroke=\"%s\" fill=\"%s\" font-size=\"[TROCA O TAMANHO]\">%s</text>";

    double x = text_get_x(text);
    double y = text_get_y(text);

    char* string = text_get_string(text);

    char* border_color = text_get_border_color(text);
    char* fill_color = text_get_fill_color(text);

    fprintf(svg_file, format, x, y, string, border_color, fill_color);
}