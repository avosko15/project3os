#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    const char delimiter[] = " \n\t\r";
    int forkCheck;
    int chdirValue;

    while (1) {
        //Get the command
        char userString[2048] = {};
        printf("MUSH $ ");
        fgets(userString, 2048, stdin);

        //Tokenize user input
        char *token = strtok(userString, delimiter);
        char *tokenStorage[128] = {};
        int count = 0;

        while (token != NULL) {
            tokenStorage[count] = token;
            count++;
            token = strtok(NULL, delimiter);
        }
        tokenStorage[count] = NULL;

        // Check entered the "cd" command
        if (strcmp(tokenStorage[0], "cd") == 0) {
            chdirValue = chdir(tokenStorage[1]);
            if (chdirValue == -1) {
                printf("Error changing directory\n");
            }
            continue;
        }

        // Check entered the "exit" command
        if (strcmp(tokenStorage[0], "exit") == 0) {
            exit(0);
        }

        forkCheck = fork();
        if (forkCheck == 0) {
            execvp(tokenStorage[0], tokenStorage);
            printf("Error executing command\n");
            exit(1);
        }
        wait(NULL);
    }
    return 0;
}
