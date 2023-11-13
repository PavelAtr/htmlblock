#include <stdlib.h>

int maxsize = 1048576;
int maxweight = 100;
int maxlist = 200;
int debug = 0;
const char *html2text = "html2text";

int parseenv()
{
    char *value;
    if ((value = getenv("MAXSIZE")) != NULL) maxsize = atoi(value);
    if ((value = getenv("MAXWEIGHT")) != NULL) maxweight = atoi(value);
    if ((value = getenv("MAXLIST")) != NULL) maxlist = atoi(value);
    if ((value = getenv("DEBUG")) != NULL) debug = atoi(value);
    if ((value = getenv("HTML2TEXT")) != NULL) html2text = value;

    return 0;
}