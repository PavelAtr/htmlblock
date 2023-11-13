#include <stdio.h>

struct word
{
    char* string;
    int weight;
};

int initfilter(FILE* list, int count);
int filter(char* buffer, ssize_t length);
