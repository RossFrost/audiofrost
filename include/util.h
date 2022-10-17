#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <stdlib.h>

#define COMPILED_PATH "\\compiled"

#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED
    #define OUTPUT_DIRECTORY_PATH "\\output"
    #define TEMP_FILE_LENGTH 20

    void full_path(char *file, char destination[]);
    long long get_length_of_int(long long value);

#endif