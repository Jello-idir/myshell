#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void echo(char *input)
{
    printf("%s\n", input + 5);
}

int bridge(char *cmdline)
{
    if (!strcmp(cmdline, "exit"))
        return 1;
    if (!strncmp(cmdline, "echo ", 5))
        echo(cmdline);
    else
        printf("%s: command not found\n", cmdline);
    return 0;
}

void repl()
{
    char cmdline[1024];

    while(1)
    {
        printf("$ ");
        if (!fgets(cmdline, sizeof(cmdline), stdin))
            return;
        cmdline[strcspn(cmdline, "\n")] = 0;
        if (bridge(cmdline))
            return ;
    }
}

int main(int argc, char *argv[]) {

    setbuf(stdout, NULL);
    repl();
    return 0;
}
