#ifndef STR_APPENDF

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int str_appendf(char **str, const char *fmt, ...) {
    va_list ap;
    va_list ap_copy;
    int needed;

    if (!str || !*str || !fmt)
        return -1;

    // Find out how much space the formatted string needs
    va_start(ap, fmt);
    va_copy(ap_copy, ap);
    needed = vsnprintf(NULL, 0, fmt, ap_copy);
    va_end(ap_copy);

    if (needed < 0) {
        va_end(ap);
        return -1;
    }

    size_t len = strlen(*str);
    size_t new_size = len + (size_t)needed + 1;

    char *tmp = realloc(*str, new_size);
    if (!tmp) {
        va_end(ap);
        return -1;
    }

    *str = tmp;

    // Append the formatted text at the end
    vsnprintf(*str + len, (size_t)needed + 1, fmt, ap);

    va_end(ap);

    return needed;
}

#define STR_APPENDF
#endif /* ifndef STR_APPENDF */

