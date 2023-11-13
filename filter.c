#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "filter.h"
#include "normalize.h"
#include "env.h"
#include <string.h>

int filter(FILE* list, char* buffer, ssize_t length)
{
    int weight = 0;

    buffer = normalize(buffer, length);
    if (debug)
    {
        write(1, buffer, length);
        write(1, "\n", 1);
    }

    char string[MAXWORDLENGTH];
    int strweight;
    while(fscanf(list, "%s :: %d", string, &strweight) != EOF)
    {
        char *found = buffer;
        while ((found = strstr(found, string)) != NULL)
        {
            if (buffer - found < length)
                found = found + 1;

            if (debug)
                printf("%s::%d matched\n", string, strweight);

            weight += strweight;
        }
    }

    return weight;
}
