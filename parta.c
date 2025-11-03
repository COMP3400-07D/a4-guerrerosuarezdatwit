#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>

// A simple echo-like program that uppercases all provided arguments and
// prints them separated by commas. If no arguments are provided an error is
// printed and the program exits with status 1.
int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        puts("ERROR: No arguments");
        return 1;
    }

    // Iterate over arguments (skip argv[0])
    for (int i = 1; i < argc; ++i) {
        const char* s = argv[i];
        // Print each character upper-cased
        for (const char* p = s; *p != '\0'; ++p) {
            putchar((int)toupper((unsigned char)*p));
        }
        // Print comma between arguments (no trailing comma at end)
        if (i < argc - 1) putchar(',');
    }

    return 0;
}
