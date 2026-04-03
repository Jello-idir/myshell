#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

typedef int (*func)(int, char **);

int ft_exit(int, char**);
int echo(int, char**);
int type(int, char**);

char *builtin_s[] = {
    "exit",
    "echo",
    "type"
};

func builtin[] = {
    ft_exit,
    echo,
    type,
};


int ft_exit(int argc, char **argv)
{
    if (argc > 1)
        exit(atoi(argv[1]));
    else
        exit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

int getcid(char *command)
{
    for (int idx = 0; builtin_s[idx]; idx++)
        if (!strcmp(command, builtin_s[idx]))
            return idx;
    return -1;
}

int echo(int argc, char **argv)
{
    for (int idx = 1; idx < argc; idx++) {
        printf("%s ", argv[idx]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}

char *findpath(char *bin)
{
    char            *path;
    DIR             *dir;
    struct  dirent  *entry;

    path = getenv("PATH");
    char *tmp = strtok(path, ":;");
    while (tmp)
    {
        printf("%s\n", tmp);
        tmp = strtok(NULL, ":;");
    }
    return NULL;
}

int type(int argc, char **argv)
{
    int     built;
    int     arg;
    char    *path;

    for (arg = 1; arg < argc; arg++) {
        for (built = 0; builtin_s[built]; built++) {
            if (!strcmp(argv[arg], builtin_s[built])) {
                printf("%s is a shell builtin\n", argv[arg]);
                break;
            }
        }
        if (!builtin_s[built]) {
            path = findpath(argv[arg]);
            if (path)
                printf("%s is %s", argv[arg], path);
            else
                printf("%s: not found\n", argv[arg]);
        }
    }
    return EXIT_FAILURE;
}

int bridge(int argc, char **argv)
{
    int id;

    id = getcid(argv[0]);
    if (id == -1) {
        printf("%s: command not found\n", argv[0]);
        return EXIT_FAILURE;
    }
    builtin[id](argc, argv);
    return EXIT_SUCCESS;
}

int evaluate( char *cmdline, char **argv) {
    int argc;

    cmdline[strcspn(cmdline, "\n")] = 0;
    argc = 0;
    argv[argc++]= strtok(cmdline, " ");
    do {
        argv[argc] = strtok(NULL, " ");
        argc++;
    } while (argv[argc - 1]);
    return argc - 1;
}

int repl() {
    char    cmdline[1024];
    char    *argv[64];
    int     status;
    int     argc;

    while (1) {
        printf("$ ");

        // readingnc
        if (!fgets(cmdline, sizeof(cmdline), stdin))
            return EXIT_FAILURE;
        // evaluating
        argc = evaluate(cmdline, argv);

        // executing
        status = bridge(argc, argv);

    }
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    return repl();
}
