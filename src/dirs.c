#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

int main()
{
    char *path;
    DIR *dir;
    struct dirent *entry;

    dir = opendir("dir");
}
