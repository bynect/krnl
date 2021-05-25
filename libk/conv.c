#include "conv.h"
#include "string.h"

bool
ui64_to_str(ui64 num, ui8 *str, ui64 len)
{
    if (len == 0)
    {
        return false;
    }

    ui64 i = 0;

    do
    {
        str[i++] = "0123456789"[num % 10];
        num /= 10;
    } while (num > 0 && i < len);

    if (num > 0 && i == (len - 1))
    {
        return false;
    }

    str[i + (i < len)] = '\0';
    strrev(str, i);

    return true;
}

bool
ui64_to_hstr(ui64 num, ui8 *str, ui64 len)
{
    if (len == 0)
    {
        return false;
    }

    ui64 i = 0;

    do
    {
        str[i++] = "0123456789ABCDEF"[num % 16];
        num >>= 4;
    } while (num > 0 && i < len);

    if (num > 0 && i == (len - 1))
    {
        return false;
    }

    str[i + (i < len)] = '\0';
    strrev(str, i);

    return true;
}
