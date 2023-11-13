#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "filter.h"
#include "normalize.h"
#include "env.h"
#include <string.h>

struct word *words;
int wordnum = 0;

int initfilter(FILE* list, int count)
{
    char string[1024];
    int weight;
    words = (struct word*) malloc(count * sizeof(struct word));
    while(fscanf(list, "%s :: %d", string, &weight) != EOF)
    {
        words[wordnum].string = strdup(string);
        words[wordnum].weight = weight;
        wordnum++;
        if (wordnum == maxlist) break;
    }

    if (debug)
        for (int i = 0; i < wordnum; i++) printf("%s::%d\n", words[i].string, words[i].weight);

    return 0;
}

int filter(char* buffer, ssize_t length)
{
    int weight = 0;

    buffer = normalize(buffer, length);
    if (debug)
    {
        write(1, buffer, length);
        write(1, "\n", 1);
    }

    for (int i = 0; i < wordnum; i++)
    {
        char *found = buffer;
        while ((found = strstr(found, words[i].string)) != NULL)
        {
            if (buffer - found < length)
                found = found + 1;

            if (debug)
                printf("%s::%d matched\n", words[i].string, words[i].weight);

            weight += words[i].weight;
        }
    }

    return weight;
}
