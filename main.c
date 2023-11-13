#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>

#include "env.h"
#include "filter.h"

int main(int argc, char** argv)
{

    if (argc < 2) error(ENOTSUP, ENOTSUP, "Usage: %s <file_list>", argv[0]);

    parseenv();

    FILE *list = fopen(argv[1], "r");
    if (list == NULL) error(2, errno, "Error open list %s\n", argv[1]);

    int pid;
    int cmdpipe[2];

    if (pipe(cmdpipe) == -1) error (3, EPIPE, "Error pipe\n");

    if ((pid = fork()) == -1) error(4, ECHILD, "Error fork %s\n", html2text);
    else if (pid == 0)
    {
        dup2(cmdpipe[1], 1);
        dup2(cmdpipe[1], 2);
        execlp(html2text, html2text, NULL);
        error(4, ECHILD, "Error execlp %s\n",  html2text);
    }

    dup2(cmdpipe[0], 0);
    char* document = (char*) malloc(maxsize);
    ssize_t size = read(0, document, maxsize);

    int weight = filter(list, document, size);
    printf("%d\n", weight);
    if (weight >= maxweight)
        exit(1);

    return 0;
}
