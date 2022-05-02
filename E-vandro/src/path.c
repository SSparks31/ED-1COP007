#include "path.h"

#include <string.h>

int get_path(char* result, char* full_path) {
    if (!result) {
        return -1;
    }

    if (!full_path || strlen(full_path) == 0) {
        strcpy(result, "./");
        return 0;
    }

    char* slash = strrchr(full_path, '/');
    if (!slash) {
        strcpy(result, "./");
        return 0;
    }

    int path_length = strlen(full_path) - strlen(slash);
    strncpy(result, full_path, path_length);
    result[path_length] = '\0';

    return 0;
}

int get_file_name(char* result, char* full_path) {
    if (!result || !full_path || strlen(full_path) == 0) {
        return -1;
    }

    char* slash = strrchr(full_path, '/');
    if (!slash) {
        strcpy(result, full_path);
        return 0;
    }

    strcpy(result, slash + 1);
    return 0;
}

int get_suffix(char* result, char* file_name) {
    if (!result || !file_name || strlen(file_name) == 0) {
        return -1;
    }

    char* dot = strrchr(file_name, '.');
    if (!dot) {
        strcpy(result, "");
        return 0;
    }

    strcpy(result, dot + 1);
    return 0;
}

int strip_suffix(char* result, char* file_name) {
    if (!result || !file_name || strlen(file_name) == 0) {
        return -1;
    }

    char* dot = strrchr(file_name, '.');
    if (!dot) {
        strcpy(result, file_name);
        return 0;
    }

    int file_length = strlen(file_name) - strlen(dot);
    strncpy(result, file_name, file_length);
    result[file_length] = '\0';
    return 0;
}

int has_slash(char* path) {
    if (!path || strlen(path) == 0) {
        return -1;
    }

    return path[strlen(path) - 1] == '/';
}

int concat_path_file(char* result, char* path, char* file_name) {
    if (!result || !file_name || strlen(file_name) == 0) {
        return -1;
    }

    if (!path || strlen(path) == 0) {
        strcpy(result, "./");
    } else {
        strcpy(result, path);
    }

    if (!has_slash(result)) {
        strcat(result, "/");
    }

    strcat(result, file_name);
    return 0;
}

int concat_file_suffix(char* result, char* file_name, char* suffix) {
    if (!result || !file_name || strlen(file_name) == 0) {
        return -1;
    }

    strcpy(result, file_name);
    
    if (!suffix || strlen(suffix) == 0) {   
        return 0;
    }

    strcat(result, ".");
    strcat(result, suffix);
    return 0;
}