#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef __HTML

typedef char* HTML;

int __str_appendf(char **str, const char *fmt, ...) {
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

HTML __html(int count, ...)
{
    va_list args;
    va_start(args, count);
    char *result = strdup("");

    for (int i = 0; i < count; i++) {
        const char *str = va_arg(args, char *);
        __str_appendf(&result, "%s", str);
        free((void *)str);
    }

    va_end(args);
    return result;
}

#define __HTML
#endif /* ifndef __HTML */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "da.h"

HTML page_home() {
    return __html(1, strdup("\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x68\x31\x3e\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x57\x65\x6c\x63\x6f\x6d\x65\x20\x74\x6f\x20\x6d\x79\x20\x77\x65\x62\x73\x69\x74\x65\x21\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x61\x20\x68\x72\x65\x66\x3d\x22\x61\x22\x3e\x47\x6f\x20\x74\x6f\x20\x70\x61\x67\x65\x20\x41\x3c\x2f\x61\x3e\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x61\x20\x68\x72\x65\x66\x3d\x22\x62\x22\x3e\x47\x6f\x20\x74\x6f\x20\x70\x61\x67\x65\x20\x42\x3c\x2f\x61\x3e\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x61\x20\x68\x72\x65\x66\x3d\x22\x62\x2f\x63\x22\x3e\x47\x6f\x20\x74\x6f\x20\x70\x61\x67\x65\x20\x43\x3c\x2f\x61\x3e\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x2f\x68\x31\x3e\x0a\x20\x20\x20\x20"));
}

HTML page_a() {
    return __html(1, strdup("\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x68\x31\x3e\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x57\x65\x6c\x63\x6f\x6d\x65\x20\x74\x6f\x20\x50\x61\x67\x65\x20\x41\x21\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x61\x20\x68\x72\x65\x66\x3d\x22\x2f\x22\x3e\x47\x6f\x20\x68\x6f\x6d\x65\x3c\x2f\x61\x3e\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x2f\x68\x31\x3e\x0a\x20\x20\x20\x20"));
}

HTML page_b() {
    return __html(1, strdup("\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x68\x31\x3e\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x57\x65\x6c\x63\x6f\x6d\x65\x20\x74\x6f\x20\x50\x61\x67\x65\x20\x42\x21\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x61\x20\x68\x72\x65\x66\x3d\x22\x2f\x22\x3e\x47\x6f\x20\x68\x6f\x6d\x65\x3c\x2f\x61\x3e\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x61\x20\x68\x72\x65\x66\x3d\x22\x63\x22\x3e\x47\x6f\x20\x74\x6f\x20\x70\x61\x67\x65\x20\x43\x3c\x2f\x61\x3e\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x2f\x68\x31\x3e\x0a\x20\x20\x20\x20"));
}

HTML page_c() {
    return __html(1, strdup("\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x68\x31\x3e\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x57\x65\x6c\x63\x6f\x6d\x65\x20\x74\x6f\x20\x50\x61\x67\x65\x20\x43\x21\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x61\x20\x68\x72\x65\x66\x3d\x22\x2f\x22\x3e\x47\x6f\x20\x68\x6f\x6d\x65\x3c\x2f\x61\x3e\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x3c\x2f\x68\x31\x3e\x0a\x20\x20\x20\x20"));
}

typedef struct {
    char *path;
    HTML (*generator)();
} Page;

typedef da(Page) PageList;

da(PageList) page_lists = {0};
da(char*) current_paths = {0};

void begin_page_list() {
    da_append(page_lists, (PageList){0});
    da_append(current_paths, strdup("/"));
}

void add_index(HTML (*page)()) {
    char index[] = "index.html";
    char *new = malloc(strlen(da_last(current_paths)) + sizeof(index));
    strcpy(new, da_last(current_paths));
    strcat(new, index);
    da_append(da_last(page_lists), ((Page){ .path = new, .generator = page }));
}

void add_children(char *name) {
    da_last(current_paths) = realloc(da_last(current_paths), strlen(da_last(current_paths)) + strlen(name) + 2);
    strcat(da_last(current_paths), name);
    strcat(da_last(current_paths), "/");
}

void end_children() {
    size_t new_len = 1;
    size_t next_new_len = 1;

    for (size_t i = 0; da_last(current_paths)[i]; i++) {
        if (da_last(current_paths)[i] == '/') {
            new_len = next_new_len;
            next_new_len = i + 1;
        }
    }


    da_last(current_paths) = realloc(da_last(current_paths), new_len + 1);
    da_last(current_paths)[new_len] = '\0';
}

void add_child(char *name, HTML (*page)()) {
    add_children(name); {
        add_index(page);
    } end_children();
}

PageList end_page_list() {
    PageList result = da_last(page_lists);
    da_remove(page_lists, da_size(page_lists) - 1);
    free(da_last(current_paths));
    da_remove(current_paths, da_size(current_paths) - 1);
    return result;
}

int main(int argc, char *argv[]) {
    begin_page_list(); {
        add_index(page_home);
        add_child("a", page_a);
        add_children("b"); {
            add_index(page_b);
            add_child("c", page_c);
        } end_children();
    } PageList page_list = end_page_list();

    for (size_t i = 0; i < da_size(page_list); i++) {
        printf("%s\n", page_list[i].path);
        printf("-------------------------\n");
        printf("%s\n", page_list[i].generator());
        printf("-------------------------\n");
    }

    return EXIT_SUCCESS;
}
