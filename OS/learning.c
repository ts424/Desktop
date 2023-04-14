#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

pid_t foreground_pid;

void sigint_handler(int signum) {
    if (foreground_pid != 0) {
        kill(foreground_pid, SIGINT);
    }
}

int main() {
    // set up the custom signal handler
    struct sigaction sigint_action;
    sigint_action.sa_handler = sigint_handler;
    sigemptyset(&sigint_action.sa_mask);
    sigint_action.sa_flags = 0;
    sigaction(SIGINT, &sigint_action, NULL);

    while (1) {
        // get the user's command
        char command[100];
        printf("$ ");
        fgets(command, 100, stdin);

        // parse the command to determine whether it should run in the foreground or background
        int is_background = 0;
        int i = 0;
        while (command[i] != '\0') {
            if (command[i] == '&') {
                is_background = 1;
                command[i] = '\0';
                break;
            }
            i++;
        }

        // fork a child process to run the command
        pid_t pid = fork();
        if (pid == 0) {
            // in the child process

            // set the process group ID
            if (is_background) {
                setpgid(0, 0);
            } else {
                foreground_pid = getpid();
            }

            // run the command
            char *argv[10];
            argv[0] = strtok(command, " \n");
            int j = 1;
            while (argv[j - 1] != NULL) {
                argv[j] = strtok(NULL, " \n");
                j++;
            }
            execvp(argv[0], argv);
        } else {
            // in the parent process

            // wait for the child process if it is running in the foreground
            if (!is_background) {
                waitpid(pid, NULL, 0);
                foreground_pid = 0;
            }
        }
    }
    return 0;
}
