//Daniel Guerrero
//W00427795

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Fork a child that execs /usr/bin/grep -s -q <word> <file>. Parent waits and
// interprets grep's exit status:
// 0 -> FOUND: <word>
// 1 -> NOT FOUND: <word>  (parent prints this and exits 0)
// 2 -> ERROR: <file> doesn't exist (parent prints and exits 2)
// If incorrect number of args, print error and return 1.
int main(int argc, const char* argv[]) {
    if (argc != 3) {
        puts("ERROR: No arguments");
        return 1;
    }

    const char* word = argv[1];
    const char* filename = argv[2];

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // child
        char* gargs[] = { "grep", "-s", "-q", (char*)word, (char*)filename, NULL };
        execv("/usr/bin/grep", gargs);
        // if exec fails
        perror("exec");
        _exit(1);
    }

    // parent
    int status = 0;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        if (code == 0) {
            printf("FOUND: %s", word);
            return 0;
        } else if (code == 1) {
            printf("NOT FOUND: %s", word);
            return 0;
        } else if (code == 2) {
            printf("ERROR: %s doesn't exist", filename);
            return 2;
        } else {
            // other grep exit codes
            printf("ERROR: grep exited with %d", code);
            return 2;
        }
    } else {
        // child did not exit normally
        printf("ERROR: child did not exit normally");
        return 2;
    }
}
