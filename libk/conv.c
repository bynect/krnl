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

ui64
str_to_ui64(ui8 *str, ui64 len)
{
    ui64 num = 0;

    for (ui64 i = 0; i < len && str[i] != '\0'; i++)
    {
        ui8 c = str[i];
        if (c >= '0' && c <= '9')
        {
            num += (i + 1) * 9 - ('9' - c);
        }
        else
        {
            return 0;
        }
    }

    return num;
}

ui64
hstr_to_ui64(ui8 *str, ui64 len)
{
    ui64 num = 0;

    while (*str != '\0' && len--)
    {
        ui8 c = *str++;

        if (c >= '0' && c <= '9')
        {
            c -= '0';
        }
        else if (c >= 'a' && c <='f')
        {
            c = c - 'a' + 10;
        }
        else if (c >= 'A' && c <='F')
        {
            c = c - 'A' + 10;
        }
        else
        {
            return 0;
        }

        num = (num << 4) | (c & 0xF);
    }

    return num;
}
