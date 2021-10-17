#include "text.h"

#include "../helper/stringHelp.h"

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

Text create_text(char* id, double coordinates[2], char* string, char* colors[2]) {
    if (!id || !coordinates || !colors || isEmpty(string)) {
        return NULL;
    }

    for (int i = 0; i < 2; ++i) {
        if (isEmpty(colors[i])) {
            return NULL;
        }
    }

    Text text = malloc(sizeof(struct text));
    if (!text) {
        return NULL;
    }

    text->id = malloc(strlen(id) + 1);
    
    text_set_x           (text, coordinates[0]);
    text_set_y           (text, coordinates[1]);
    text_set_string      (text, string);
    
    if (!text->id || text_set_border_color(text, colors[0]) || text_set_fill_color  (text, colors[1])) {
        text_destroy(&text);
    }

    strcpy(text->id, id);

    return text;
}

char* text_get_id(Text text) {
    if (!text) {
        return NULL;
    }

    return text->id;
}

char* text_get_x(Text text) {
    if (!text) {
        return NULL;
    }

    return text->x;
}

char* text_get_y(Text text) {
    if (!text) {
        return NULL;
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


int text_set_x(Text text, char* x) {
    if (!text || isEmpty(x)) {
        return 1;
    }

    if (!text->x) {
        text->x = malloc(strlen(x) + 1);
    } else {
        text->x = realloc(text->x, strlen(x) + 1);
    }

    if (!text->x) {
        return 1;
    }

    strcpy(text->x, x);
    return 0;
}

int text_set_y(Text text, char* y) {
    if (!text || isEmpty(y)) {
        return 1;
    }

    if (!text->y) {
        text->y = malloc(strlen(y) + 1);
    } else {
        text->y = realloc(text->y, strlen(y) + 1);
    }

    if (!text->y) {
        return 1;
    }

    strcpy(text->y, y);
    return 0;
}

int text_set_string(Text text, char* string) {
    if (!text || isEmpty(string)) {
        return 1;
    }

    if (!text->string) {
        text->string = malloc(strlen(string) + 1);
    } else {
        text->string = realloc(text->string, strlen(string) + 1);
    }

    if (!text->string) {
        return 1;
    }

    strcpy(text->string, string);
	return 0;
}

int text_set_border_color(Text text, char* border_color) {
    if (!text || isEmpty(border_color)) {
        return 1;
    }

    if (!text->border_color) {
        text->border_color = malloc(strlen(border_color) + 1);
    } else {
        text->border_color = realloc(text->border_color, strlen(border_color) + 1);
    }

    if(!text->border_color) {
        return 1;
    }

    strcpy(text->border_color, border_color);
	return 0;
}

int text_set_fill_color(Text text, char* fill_color) {
    if (!text || isEmpty(fill_color)) {
        return 1;
    }

    if (!text->fill_color) {
        text->fill_color = malloc(strlen(fill_color) + 1);
    } else {
        text->fill_color = realloc(text->fill_color, strlen(fill_color) + 1);
    }

    if(!text->fill_color) {
        return 1;
    }

    strcpy(text->fill_color, fill_color);
	return 0;
}

void text_destroy(Text* text) {
    if (!text || !*text) {
        return;
    }

    if ((*text)->id) free((*text)->id);

    if ((*text)->border_color) free((*text)->border_color);
    if ((*text)->fill_color) free((*text)->fill_color);

    free(*text);
    *text = NULL;
}