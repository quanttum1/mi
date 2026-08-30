#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include <assert.h>

char *read_entire_file(char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Failed to read file `%s`: %s\n", file_path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    char *buffer = malloc(size + 1);
    rewind(file);

    fread(buffer, size, 1, file);

    buffer[size] = '\0';
    return buffer;
}

typedef enum { C, HTML, INLINE_C } Mode;

bool skip_if_starts_with(char **s, char *prefix) {
    for (size_t i = 0; i < strlen(prefix); i++) {
        if ((*s)[i] != prefix[i]) return false;
    }

    *s += strlen(prefix);
    return true;
}

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

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.cx output.c\n", argv[0]);
    }

    char *input = read_entire_file(argv[1]);
    FILE *output = fopen(argv[2], "w");

    fprintf(output, "#include <stdarg.h>\n");
    fprintf(output, "#include <string.h>\n");
    fprintf(output, "#include <stdlib.h>\n");
    fprintf(output, "#include <stdio.h>\n");
    fprintf(output, "\n");
    fprintf(output, "#ifndef __HTML\n");
    fprintf(output, "\n");
    fprintf(output, "typedef char* HTML;\n");
    fprintf(output, "\n");
    fprintf(output, "int __str_appendf(char **str, const char *fmt, ...) {\n");
    fprintf(output, "    va_list ap;\n");
    fprintf(output, "    va_list ap_copy;\n");
    fprintf(output, "    int needed;\n");
    fprintf(output, "\n");
    fprintf(output, "    if (!str || !*str || !fmt)\n");
    fprintf(output, "        return -1;\n");
    fprintf(output, "\n");
    fprintf(output, "    // Find out how much space the formatted string needs\n");
    fprintf(output, "    va_start(ap, fmt);\n");
    fprintf(output, "    va_copy(ap_copy, ap);\n");
    fprintf(output, "    needed = vsnprintf(NULL, 0, fmt, ap_copy);\n");
    fprintf(output, "    va_end(ap_copy);\n");
    fprintf(output, "\n");
    fprintf(output, "    if (needed < 0) {\n");
    fprintf(output, "        va_end(ap);\n");
    fprintf(output, "        return -1;\n");
    fprintf(output, "    }\n");
    fprintf(output, "\n");
    fprintf(output, "    size_t len = strlen(*str);\n");
    fprintf(output, "    size_t new_size = len + (size_t)needed + 1;\n");
    fprintf(output, "\n");
    fprintf(output, "    char *tmp = realloc(*str, new_size);\n");
    fprintf(output, "    if (!tmp) {\n");
    fprintf(output, "        va_end(ap);\n");
    fprintf(output, "        return -1;\n");
    fprintf(output, "    }\n");
    fprintf(output, "\n");
    fprintf(output, "    *str = tmp;\n");
    fprintf(output, "\n");
    fprintf(output, "    // Append the formatted text at the end\n");
    fprintf(output, "    vsnprintf(*str + len, (size_t)needed + 1, fmt, ap);\n");
    fprintf(output, "\n");
    fprintf(output, "    va_end(ap);\n");
    fprintf(output, "\n");
    fprintf(output, "    return needed;\n");
    fprintf(output, "}\n");
    fprintf(output, "\n");
    fprintf(output, "HTML __html(int count, ...)\n");
    fprintf(output, "{\n");
    fprintf(output, "    va_list args;\n");
    fprintf(output, "    va_start(args, count);\n");
    fprintf(output, "    char *result = strdup(\"\");\n");
    fprintf(output, "\n");
    fprintf(output, "    for (int i = 0; i < count; i++) {\n");
    fprintf(output, "        const char *str = va_arg(args, char *);\n");
    fprintf(output, "        __str_appendf(&result, \"%%s\", str);\n");
    fprintf(output, "        free((void *)str);\n");
    fprintf(output, "    }\n");
    fprintf(output, "\n");
    fprintf(output, "    va_end(args);\n");
    fprintf(output, "    return result;\n");
    fprintf(output, "}\n");
    fprintf(output, "\n");
    fprintf(output, "#define __HTML\n");
    fprintf(output, "#endif /* ifndef __HTML */\n");

    char *html_buffer;
    int arg_count;
    Mode mode = C;
    while (*input) {
        switch (mode) {
            case C:
                if (skip_if_starts_with(&input, "<>")) {
                    html_buffer = strdup("");
                    arg_count = 1;
                    mode = HTML;
                }
                else {
                    fprintf(output, "%c", *(input++));
                }
                break;

            case HTML:
                if (skip_if_starts_with(&input, "</>")) {
                    fprintf(output, "__html(%d, strdup(\"%s\"))", arg_count, html_buffer);
                    free(html_buffer);
                    mode = C;
                }
                else if (skip_if_starts_with(&input, "%(")) {
                    str_appendf(&html_buffer, "\"), ");
                    arg_count++;
                    mode = INLINE_C;
                }
                else {
                    str_appendf(&html_buffer, "\\x%02x", (unsigned char)*(input++));
                }
                break;

            case INLINE_C:
                if (skip_if_starts_with(&input, ")%")) {
                    str_appendf(&html_buffer, ", strdup(\"");
                    arg_count++;
                    mode = HTML;
                }
                else {
                    str_appendf(&html_buffer, "%c", *(input++));
                }
                break;

            default:
                assert(0 && "No way");
        }
    }

    fclose(output);

    return EXIT_SUCCESS;
}
