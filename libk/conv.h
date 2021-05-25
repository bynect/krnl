#ifndef LIBK_CONV_H
#define LIBK_CONV_H

#include <krnl/types.h>

bool ui64_to_str(ui64 num, ui8 *str, ui64 len);

bool ui64_to_hstr(ui64 num, ui8 *str, ui64 len);

ui64 str_to_ui64(ui8 *str, ui64 len);

ui64 hstr_to_ui64(ui8 *str, ui64 len);

#endif
