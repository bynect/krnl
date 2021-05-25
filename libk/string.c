#include "string.h"

ui64
strlen(const ui8 *str)
{
    ui64 len = 0;
    while (*str++)
    {
        len++;
    }
    return len;
}

void
strrev(ui8 *str, ui64 len)
{
    for (ui64 i = 0, j = len - 1; i < j; i++, j--)
    {
        ui8 t = str[i];
        str[i] = str[j];
        str[j] = t;
    }
}
