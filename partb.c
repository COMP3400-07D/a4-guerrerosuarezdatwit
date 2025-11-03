//Daniel Guerrero
//W00427795

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// This program identifies the middle argument(s) and uses execv to run
// /bin/echo to print them. If no arguments are provided it prints an error
// and exits with status 1.
int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        puts("ERROR: No arguments");
        return 1;
    }

    int n = argc - 1; // number of user arguments
    int start_index = 1 + (n - 1) / 2; // 1-based in argv
    int count = (n % 2 == 1) ? 1 : 2;
    if (n % 2 == 0) start_index = 1 + (n / 2) - 1; // for even, pick indices n/2 and n/2+1

    // prepare args for execv: { "echo", arg1, arg2?, NULL }
    char* eargs[4];
    eargs[0] = "echo";
    // copy pointers from argv
    eargs[1] = (char*)argv[start_index];
    if (count == 2) {
        eargs[2] = (char*)argv[start_index + 1];
        eargs[3] = NULL;
    } else {
        eargs[2] = NULL;
    }

    // execv replaces this process; if it returns there was an error
    execv("/bin/echo", eargs);
    perror("exec");
    return 1;
}
