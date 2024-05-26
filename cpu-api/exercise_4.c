/*
Write a program that calls fork() and then calls some form of
exec() to run the program /bin/ls. See if you can try all of the
variants of exec(), including (on Linux) execl(), execle(),
execlp(), execv(), execvp(), and execvpe(). Why do
you think there are so many variants of the same basic call?
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Call fork() to create a child process
    pid = fork();

    if (pid == 0) {
        // This is the child process
        // Call exec() to run the /bin/ls program
        execlp("/bin/ls", "ls", NULL);
        perror("exec");
    } else if (pid > 0) {
        // This is the parent process
        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);
        printf("Child process has finished.\n");
    } else {
        // fork() failed
        perror("fork");
        return 1;
    }

    return 0;
}

/*
 * 3 key differences between the exec() function variants:
 *
 * 1. How the arguments are passed:
 *
 *   - execl() and execle() take the program name and arguments as separate parameters.
 *
 *   - execv() and execvp() take the arguments as an array of strings.
 *
 * 2. Whether an environment array is provided:
 *
 *   - execle() and execvpe() take an environment array as a parameter, allowing you to specify the environment for the new process.
 *
 *   - exec(), execl(), execv(), and execvp() do not take an environment array as a parameter.
 *
 * 3. Whether the PATH environment variable is used to search for the executable:
 *
 *   - execvp() and execvpe() search for the executable file in the directories specified by the PATH environment variable.
 *
 *   - exec(), execl(), execv(), and execle() do not use the PATH environment variable to search for the executable.
 */
