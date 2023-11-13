#include <stdlib.h>
#include <locale.h>
#include <cstring>
#include <cwctype>

char* normalize(char* buffer, ssize_t length)
{
    setlocale(LC_ALL, "");
    const char* localename = getenv("LANG");
    if (localename == NULL) {
        localename = "";
    }

    setlocale(LC_ALL, localename);

    wchar_t* wchars = new wchar_t[length + 1];
    memset(wchars, 0, length);
    std::mbstowcs(wchars, buffer, length);
    wchars[length] = '\0';

    int i = 0;
    while(wchars[i] != '\0') {
        wchars[i] = std::towlower(wchars[i]);
        if (wchars[i] == ' ') wchars[i] = '_';
        if (wchars[i] == '\n') wchars[i] = '_';
        i++;
    }

    std::wcstombs(buffer, wchars, length);
    buffer[length] = '\0';

    delete[] wchars;

    return buffer;
}
